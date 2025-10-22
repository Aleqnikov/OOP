#include "AllyManager.h"

#include <random>
#include <memory>
#include <cmath>
#include <limits>


bool AllyManager::AllyTurn(Field& field) {
    bool flag = true;

    for (auto ally_weak : allyes_) {
        if (auto ally = ally_weak.lock()) {
            if (ally->NotMoveNext())
                continue;

            int x_ally, y_ally;
            if (!field.GetPosEntity(ally, x_ally, y_ally)) {
                flag = false;
                continue;
            }

            auto target = findTarget(x_ally, y_ally, field);
            if (!target) {
                flag = false;
                continue;
            }

            std::array<MoveType, 4> moving{};
            if (!GetMoveForAlly(field, moving, target, ally_weak)) {
                flag = false;
                continue;
            }

            for (auto move : moving) {
                MoveResult result = field.MoveEntity(move, ally);
                if (result == MoveResult::Moved || result == MoveResult::HitEntity)
                    break;
            }
        }
    }

    return flag;
}

bool AllyManager::GetMoveForAlly(Field& field, std::array<MoveType, 4>& moves,
                                 std::shared_ptr<Entity> target, std::weak_ptr<Entity> current) {
    if (!target) return false;

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


bool AllyManager::SpawnAllys(Field& field, int count_enemies) {
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
        auto ally = std::make_shared<Ally>();
        allyes_.push_back(ally);
        while ((x == 0 && y == 0) || !field.SetEntity(ally, x, y)) {
            x = x_dist(gen);
            y = y_dist(gen);
        }
    }
    return true;
}

void AllyManager::DeleteDeadAllys(Field& field) {
    for (auto it = allyes_.begin(); it != allyes_.end();) {
        if (auto ally = it->lock()) {
            if (ally->IsDead()) {
                field.RemoteEntity(ally);
                it = allyes_.erase(it);
            } else {
                ++it;
            }
        } else {
            it = allyes_.erase(it);
        }
    }
}

void AllyManager::AddAlly(std::weak_ptr<Ally> ally) {
    allyes_.push_back(ally);
}

const std::vector<std::weak_ptr<Ally>>& AllyManager::GetAllyes() const {
    return allyes_;
}


std::shared_ptr<Entity> AllyManager::findTarget(int x, int y, Field& field) {
	int width, height;
	field.GetSize(width, height);

	std::shared_ptr<Entity> nearest = nullptr;
	double min_dist = std::numeric_limits<double>::max();

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			auto entity = field.GetEntity(j, i);
			if (!entity) continue;

			if (entity->IsFriendly()) continue;

			double dist = std::hypot(x - j, y - i);

			if (dist < min_dist) {
				min_dist = dist;
				nearest = entity;
			}
		}
	}

	return nearest;
}


void AllyManager::findAllyes(Field& field) {
	allyes_.clear(); // Очищаем старый список союзников

	int width, height;
	field.GetSize(width, height);


	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			auto entity = field.GetEntity(x, y); // Получаем сущность в клетке
			if (entity && dynamic_cast<Ally*>(entity.get())) { // Проверяем, является ли сущность Ally
				allyes_.push_back(std::weak_ptr<Ally>(std::dynamic_pointer_cast<Ally>(entity)));
			}
		}
	}
}