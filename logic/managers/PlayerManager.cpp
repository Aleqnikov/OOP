#include "PlayerManager.h"
#include "EnemyBuildingManager.h"
#include "EnemyManager.h"
#include "../World.h"
#include <iostream>
#include <sstream>

void PlayerManager::SpawnPlayer(Field& field, std::shared_ptr<Player> player) {
    field.SetEntity(player, 0, 0);
}

bool PlayerManager::PlayerTurn(std::shared_ptr<Player> player, PlayerEvents event) {
    if (player->NotMoveNext())
        return true;

    if (event != PlayerEvents::ChangeMod)
        return false;

    player->ChangeAttackMod();
    return true;
}

bool PlayerManager::PlayerTurn(std::shared_ptr<Player> player, PlayerEvents event, int x, int y, Field& field, World& world) {
    if (player->NotMoveNext())
        return true;

    if (event != PlayerEvents::Attack)
        return false;

    int x_player, y_player;
    if (!field.GetPosEntity(player, x_player, y_player))
        return false;

    int rad_attack = player->GetAttackRadius();
    if (std::pow(y - y_player, 2) + std::pow(x - x_player, 2) > std::pow(rad_attack, 2))
        return false;

    std::shared_ptr<Entity> target = nullptr;
    int x_e, y_e;
    for (const auto& enemy_weak : world.Enemies().GetEnemies()) {
        if (auto enemy = enemy_weak.lock()) {
            if (field.GetPosEntity(enemy, x_e, y_e) && x_e == x && y_e == y) {
                target = enemy;
                break;
            }
        }
    }

    for (const auto& building_weak : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto building = building_weak.lock()) {
            if (field.GetPosEntity(building, x_e, y_e) && x_e == x && y_e == y) {
                target = building;
                break;
            }
        }
    }

    if (!target)
        return false;

    target->CauseDamage(player->GetDamage());
    return true;
}

bool PlayerManager::PlayerTurn(std::shared_ptr<Player> player, PlayerEvents event, MoveType move_type, Field& field) {
    if (player->NotMoveNext())
        return true;

    if (event != PlayerEvents::Move)
        return false;

    return field.MoveEntity(move_type, player) == MoveResult::Moved;
}

void PlayerManager::ManagePlayerTurn(std::shared_ptr<Player> player, Field& field, World& world) {
    std::string input;
    std::getline(std::cin, input);

    if (input.empty()) return;

    char command = input[0];
    switch (command) {
        case 'w':
            PlayerTurn(player, PlayerEvents::Move, MoveType::Forward, field);
            break;
        case 's':
            PlayerTurn(player, PlayerEvents::Move, MoveType::Back, field);
            break;
        case 'a':
            PlayerTurn(player, PlayerEvents::Move, MoveType::Left, field);
            break;
        case 'd':
            PlayerTurn(player, PlayerEvents::Move, MoveType::Right, field);
            break;
        case 'r':
            PlayerTurn(player, PlayerEvents::ChangeMod);
            break;
        case 'e': {
            int x, y;
            std::stringstream ss(input.substr(1));
            if (ss >> x >> y) {
                std::cout << PlayerTurn(player, PlayerEvents::Attack, x, y, field, world) << std::endl;
            }
            break;
        }
        default:
            break;
    }
}