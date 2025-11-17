#include "GameLoop.h"

#include "../logic/GameSaver.h"    // <- добавить include
#include <limits>

GameLoop::GameLoop() {
    std::shared_ptr<Player> player = std::make_shared<Player>(200, 100, 10);
    Field field(10, 10);
    World world;

    while (true) {
        std::cout << "=== GAME MENU ===\n";
        std::cout << "1. New Game\n";
        std::cout << "2. Load Game\n";
        std::cout << "3. Exit\n";
        std::cout << "Choice: ";

        std::string choice;
        std::getline(std::cin, choice);

        if (choice == "1") {
            // new game
            world.Init(field, player, 1, 1, 1, 1);
            break;
        } else if (choice == "2") {
            // list saves
            auto saves = GameSaver::listSaves();
            std::vector<std::string> valid;
            for (size_t i = 0; i < saves.size(); ++i) {
                const auto& f = saves[i];
                try {
                    GameSaver g(f);
                    TokenGameState st = g.load(); // проверка корректности
                    valid.push_back(f);
                } catch (...) {
                    // пропускаем битые/недоступные
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

    // после выбора: запускаем цикл игры как у тебя было в main()
    std::cout << "Game started! Commands: w/a/s/d (move), r (change mode), b (buy spell), e X Y (attack), q I X Y (cast spell), S (save)\n";

    while (!player->IsDead()) {
        // отрисовка и игровой цикл как в main()
        // drawField(field, world, player);   // если у тебя функция доступна
    	Visualizer::Draw(field, world, player);
        world.Update(field, player);
        world.DeleteDeadEntites(field);
    }

    std::cout << "Game Over! Player is dead. Final Score: " << player->GetScore() << "\n";
}
