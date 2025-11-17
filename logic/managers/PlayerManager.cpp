#include "PlayerManager.h"
#include "../World.h"
#include "../GameSaver.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <map>

void PlayerManager::SpawnPlayer(Field& field, std::shared_ptr<Player> player) {
    field.SetEntity(player, 0, 0);
}

bool PlayerManager::ChangeAttackMode(std::shared_ptr<Player> player) {
    if (!player || player->NotMoveNext())
        return false;

    player->ChangeAttackMod();
    return true;
}

bool PlayerManager::Attack(std::shared_ptr<Player> player, int x, int y,
                           Field& field, World& world) {
    if (!player || player->NotMoveNext())
        return false;

    if (!isInAttackRange(player, x, y, field))
        return false;

    std::shared_ptr<Entity> target = findTargetAt(x, y, field, world);
    if (!target)
        return false;

    target->CauseDamage(player->GetDamage());
    player->addScore(10);

    if (target->IsDead()) {
        player->addScore(20);
    }

    return true;
}

bool PlayerManager::Move(std::shared_ptr<Player> player, MoveType move_type, Field& field) {
    if (!player || player->NotMoveNext())
        return false;

    return field.MoveEntity(move_type, player) == MoveResult::Moved;
}

bool PlayerManager::BuySpell(std::shared_ptr<Player> player) {
	if (!player || player->NotMoveNext())
		return false;

	auto hand = player->GetHand();
	if (hand->isFull()) {
		std::cout << "Your hand is full!\n";
		return false;
	}

	std::map<int, std::pair<std::shared_ptr<ISpell>, int>> shop = {
		{1, {std::make_shared<DirDamageSpell>(2, 10), 10}},
		{2, {std::make_shared<TrapSpell>(50), 50}},
		{3, {std::make_shared<AreaDmgSpell>(4, 20), 40}},
		{4, {std::make_shared<EnhacementSpell>(2), 100}},
		{5, {std::make_shared<SummSpell>(1), 2}}
	};

	std::cout << "Available spells:\n";
	for (auto& [key, val] : shop) {
		if (player->GetScore() >= val.second) {
			std::cout << key << ": ";
			switch (val.first->getSpellType()) {
				case SpellType::DirDmg: std::cout << "DirDamage"; break;
				case SpellType::AreaDmg: std::cout << "AreaDamage"; break;
				case SpellType::Enhancement: std::cout << "Enhancement"; break;
				case SpellType::Summon: std::cout << "Summon"; break;
				case SpellType::Trap: std::cout << "Trap"; break;
				default: std::cout << "Unknown"; break;
			}
			std::cout << " (Price: " << val.second << ")\n";
		}
	}

	std::string line;
	std::cout << "Enter spell number to buy: ";
	std::getline(std::cin, line);

	int choice;
	std::stringstream(line) >> choice;

	auto it = shop.find(choice);
	if (it == shop.end() || player->GetScore() < it->second.second) {
		std::cout << "Invalid choice or not enough score!\n";
		return false;
	}

	player->minusScore(it->second.second);
	hand->addSpell(it->second.first);

	std::cout << "Spell purchased!\n";
	return true;
}



bool PlayerManager::CastSpell(std::shared_ptr<Player> player, size_t spell_index,
							  int x, int y, Field& field, World& world) {
	if (!player || player->NotMoveNext())
		return false;

	auto spell = player->GetHand()->getSpell(spell_index);
	if (!spell) return false;

	SpellContext context;
	context.caster = player;
	context.field = &field;
	context.cell = field.GetCell(x, y);
	context.target = context.cell ? context.cell->GetEntity() : nullptr;
	context.base_x = x, context.base_y = y;
	context.hand = player->GetHand();

	bool result = spell->use(context);

	return result;
}


void PlayerManager::ManagePlayerTurn(std::shared_ptr<Player> player, Field& field, World& world) {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty())
        return;

    char command = input[0];

    switch (command) {
        case 'w':
            Move(player, MoveType::Forward, field);
            break;

        case 's':
            Move(player, MoveType::Back, field);
            break;

        case 'a':
            Move(player, MoveType::Left, field);
            break;

        case 'd':
            Move(player, MoveType::Right, field);
            break;

        case 'r':
            ChangeAttackMode(player);
            break;

        case 'b':
            BuySpell(player);
            break;

        case 'e': {
            int x, y;
            std::stringstream ss(input.substr(1));
            if (ss >> x >> y) {
                bool result = Attack(player, x, y, field, world);
                std::cout << (result ? "Attack successful!" : "Attack failed!") << std::endl;
            } else {
                std::cout << "Invalid attack coordinates. Use: e X Y" << std::endl;
            }
            break;
        }

    	case 'q': {
        	auto hand = player->GetHand();

        	std::cout << "Your spells:\n";
        	for (size_t i = 0; i < hand->size(); ++i) {
        		auto spell = hand->getSpell(i);
        		std::cout << i << ": ";
        		switch (spell->getSpellType()) {
        			case SpellType::DirDmg: std::cout << "DirDamage"; break;
        			case SpellType::AreaDmg: std::cout << "AreaDamage"; break;
        			case SpellType::Enhancement: std::cout << "Enhancement"; break;
        			case SpellType::Summon: std::cout << "Summon"; break;
        			case SpellType::Trap: std::cout << "Trap"; break;
        			default: std::cout << "Unknown"; break;
        		}
        		std::cout << "\n";
        	}

        	std::string line;
        	int spell_idx;
        	std::cout << "Enter spell index: ";
        	std::getline(std::cin, line);
        	std::stringstream(line) >> spell_idx;

        	if (spell_idx < 0 || spell_idx >= static_cast<int>(hand->size())) {
        		std::cout << "Invalid index!\n";
        		break;
        	}

        	int x, y;
        	std::cout << "Enter target X Y: ";
        	std::getline(std::cin, line);
        	std::stringstream(line) >> x >> y;

        	bool result = CastSpell(player, spell_idx, x, y, field, world);
        	std::cout << (result ? "Spell cast!" : "Spell failed!") << std::endl;

        	hand->removeSpell(spell_idx);
        	break;
    	}

        default:
            std::cout << "Unknown command: " << command << std::endl;
            std::cout << "Available commands: w/a/s/d (move), r (change mode), b (buy), e X Y (attack), q I X Y (cast spell)" << std::endl;
            break;
    }
}
std::shared_ptr<Entity> PlayerManager::findTargetAt(int x, int y, Field& field, World& world) {
    int x_e, y_e;

    for (const auto& enemy_weak : world.Enemies().GetEntities()) {
        if (auto enemy = enemy_weak.lock()) {
            if (field.GetPosEntity(enemy, x_e, y_e) && x_e == x && y_e == y) {
                return enemy;
            }
        }
    }

    for (const auto& building_weak : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto building = building_weak.lock()) {
            if (field.GetPosEntity(building, x_e, y_e) && x_e == x && y_e == y) {
                return building;
            }
        }
    }

	for (const auto& tower_weak : world.EnemiesTowers().GetEnemiesTowers()) {
		if (auto tower = tower_weak.lock()) {
			if (field.GetPosEntity(tower, x_e, y_e) && x_e == x && y_e == y) {
				return tower;
			}
		}
	}

    return nullptr;
}

bool PlayerManager::isInAttackRange(std::shared_ptr<Player> player, int target_x, int target_y, Field& field) {
    int player_x, player_y;
    if (!field.GetPosEntity(player, player_x, player_y))
        return false;

    int attack_radius = player->GetAttackRadius();
    int dx = target_x - player_x;
    int dy = target_y - player_y;
    int distance_squared = dx * dx + dy * dy;

    return distance_squared <= attack_radius * attack_radius;
}