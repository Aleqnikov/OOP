#include "EnemyManager.h"
#include <random>

bool EnemyManager::EnemiesTurn(std::shared_ptr<Player> player, Field& field) {
    bool flag = true;
    for (auto enemy_weak : enemies_) {
        if (auto enemy = enemy_weak.lock()) {
            if (enemy->NotMoveNext())
                continue;

            int x_enemy, y_enemy;
            if (!field.GetPosEntity(enemy, x_enemy, y_enemy)) {
                flag = false;
                continue;
            }

            std::array<MoveType, 4> moving;
            if (!GetMoveForEnemy(field, moving, player, enemy_weak)) {
                flag = false;
                continue;
            }

            for (auto move : moving) {
                MoveResult result = field.MoveEntity(move, enemy);
                if (result == MoveResult::Moved || result == MoveResult::HitEntity) {
                    break;
                }
            }
        }
    }
    return flag;
}

bool EnemyManager::GetMoveForEnemy(Field& field, std::array<MoveType, 4>& moves, std::shared_ptr<Entity> target, std::weak_ptr<Entity> current) {
    int x_target, y_target;
    if (!field.GetPosEntity(target, x_target, y_target))
        return false;

    auto current_shared = current.lock();
    if (!current_shared)
        return false;

    int x_current, y_current;
    if (!field.GetPosEntity(current_shared, x_current, y_current))
        return false;

    int x_maj = x_target - x_current;
    int y_maj = y_target - y_current;

    if (std::abs(x_maj) > std::abs(y_maj)) {
        moves[0] = x_maj > 0 ? MoveType::Right : MoveType::Left;
        moves[2] = x_maj > 0 ? MoveType::Left : MoveType::Right;
        moves[1] = y_maj > 0 ? MoveType::Forward : MoveType::Back;
        moves[3] = y_maj > 0 ? MoveType::Back : MoveType::Forward;
    } else {
        moves[0] = y_maj > 0 ? MoveType::Forward : MoveType::Back;
        moves[2] = y_maj > 0 ? MoveType::Back : MoveType::Forward;
        moves[1] = x_maj > 0 ? MoveType::Right : MoveType::Left;
        moves[3] = x_maj > 0 ? MoveType::Left : MoveType::Right;
    }
    return true;
}

bool EnemyManager::SpawnEnemies(Field& field, int count_enemies) {
    int w, h;
    field.GetSize(w, h);
    int count_spawn_cells = field.GetCountSpawnCells();

    if (count_enemies >= (count_spawn_cells - 1) / 2)
        return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> x_dist(0, w - 1);
    std::uniform_int_distribution<> y_dist(0, h - 1);

    for (int i = 0; i < count_enemies; i++) {
        int x = x_dist(gen);
        int y = y_dist(gen);
        auto enemy = std::make_shared<Enemy>();
        enemies_.push_back(enemy);
        while ((x == 0 && y == 0) || !field.SetEntity(enemy, x, y)) {
            x = x_dist(gen);
            y = y_dist(gen);
        }
    }
    return true;
}

void EnemyManager::DeleteDeadEnemies(Field& field) {
    for (auto it = enemies_.begin(); it != enemies_.end();) {
        if (auto enemy = it->lock()) {
            if (enemy->IsDead()) {
                field.RemoteEntity(enemy);
                it = enemies_.erase(it);
            } else {
                ++it;
            }
        } else {
            it = enemies_.erase(it);
        }
    }
}

void EnemyManager::AddEnemy(std::weak_ptr<Enemy> enemy) {
    enemies_.push_back(enemy);
}

const std::vector<std::weak_ptr<Enemy>>& EnemyManager::GetEnemies() const {
    return enemies_;
}