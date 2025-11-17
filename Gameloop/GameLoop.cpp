#include "GameLoop.h"

#include "../logic/GameSaver.h"    // <- добавить include
#include <limits>

GameLoop::GameLoop() {

	// Базовое создание поля игрока.
    std::shared_ptr<Player> player = std::make_shared<Player>(200, 100, 10);
    Field field(10, 10);
    World world;

	getLevelMod(world, field, player);

    std::cout << "Game started! Commands: w/a/s/d (move), r (change mode), b (buy spell), e X Y (attack), q I X Y (cast spell), S (save)\n";

    while (!player->IsDead()) {

    	Visualizer::Draw(field, world, player);

    	globalCommandParser(world, field, player);

        world.Update(field, player);
        world.DeleteDeadEntites(field);

    	if (CheckLevelComplete(field)) {
    		StartLevel(world, field, player);
    	}
    }

    std::cout << "Game Over! Player is dead. Final Score: " << player->GetScore() << "\n";
}

void GameLoop::getLevelMod(World& world, Field& field, std::shared_ptr<Player>& player) {
	while (true) {
        std::cout << "=== GAME MENU ===\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            // Первый уроверь.
            world.Init(field, player, 1,  1, 1, 1, 0);
        	currentLevel = 1;
            break;
        } else if (choice == "2") {
            auto saves = GameSaver::listSaves();
            std::vector<std::string> valid;
            for (size_t i = 0; i < saves.size(); ++i) {
                const auto& f = saves[i];
                try {
                    GameSaver g(f);
                    TokenGameState st = g.load();
                    valid.push_back(f);
                } catch (...) {
                }
            }

            if (valid.empty()) {
                std::cout << "No valid saves found.\n";
                continue;
            }

            std::cout << "Available saves:\n";
            for (size_t i = 0; i < valid.size(); ++i) {
                std::cout << i+1 << ". " << valid[i] << "\n";
            }
            std::cout << "Choose number or 0 to cancel: ";

            std::string sel;
            std::getline(std::cin, sel);
            int idx = -1;
            try { idx = std::stoi(sel); } catch(...) { idx = -1; }
            if (idx <= 0 || idx > static_cast<int>(valid.size())) {
                std::cout << "Cancelled.\n";
                continue;
            }

            const std::string chosen = valid[idx-1];
            try {
                GameSaver g(chosen);
                TokenGameState st = g.load();
            	currentLevel = st.level;
                world.LoadState(field, player, st);
                std::cout << "Loaded: " << chosen << "\n";
                break;
            } catch (const LoadException& e) {
                std::cout << "Cannot load selected save: " << e.what() << "\n";
            } catch (const std::exception& e) {
                std::cout << "Cannot load selected save: " << e.what() << "\n";
            }
        } else if (choice == "3") {
            std::cout << "Exiting.\n";
            std::exit(0);
        } else {
            std::cout << "Unknown choice.\n";
        }
    }

}

void GameLoop::globalCommandParser(World& world, Field& field, std::shared_ptr<Player> player) {
	std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return;

    char command = input[0];

    switch (command) {
    	case 'S': {
        	// Сохранение игры
        	std::cout << "Enter save filename (e.g. save1.json): ";
        	std::string fname;
        	std::getline(std::cin, fname);
        	if (fname.empty()) {
        		std::cout << "Save cancelled.\n";
        		break;
        	}

        	try {
        		// Получим состояние через World (используем world.SerializeState)
        		TokenGameState state = world.SerializeState(field, player);
        		state.level = currentLevel;
        		GameSaver saver(fname);
        		saver.save(state);
        		GameSaver::addSaveToIndex(fname);
        		std::cout << "Game saved to: " << fname << std::endl;
        	} catch (const SaveException& e) {
        		std::cout << "Save failed: " << e.what() << std::endl;
        	} catch (const std::exception& e) {
        		std::cout << "Save failed: " << e.what() << std::endl;
        	}
        	break;
    	}
        default:
            break;
    }
}


void GameLoop::StartLevel(World& world, Field& field, std::shared_ptr<Player> player) {
	std::cout << "You have successfully completed the level!!\n";
	std::cout << "Starting level ->  \n" + std::to_string(currentLevel++) + "\n\n\n";

	field = Field(10 + 15 * (currentLevel)/50, 10 + 15 * (currentLevel)/50);

	player->setHp(200);
	player->GetHand()->removeRandomHalf();

	int enemies_c, build_c, tower_c;

	GenerateLevel(enemies_c, build_c, tower_c);

	world.Init(field, player, currentLevel,  enemies_c, build_c, tower_c, 0);

}

bool GameLoop::CheckLevelComplete(Field& field) {
	int res = field.getNotFriendlyCount();
	return res == 0;
}

void GameLoop::GenerateLevel(int& enemy, int& buildings, int& towers) {
	enemy = currentLevel/4 + 3;
	buildings = currentLevel/6 + 1;
	towers = currentLevel/6 + 1;
}