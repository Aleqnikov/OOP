#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include "map/Field.h"
#include "entites/Player.h"
#include "logic/World.h"
#include "map/cells/Cell.h"
#include "map/cells/Events/TrapEvent.h"

void visualizeField(const std::vector<std::vector<std::string>>& frame, int width, int height, int player_score) {
    // Вывод счета игрока
    std::cout << "Player Score: " << player_score << std::endl;

    // Вывод верхней границы поля
    std::cout << std::string(width * 10 + 1, '-') << std::endl;

    // Для каждой строки поля
    for (int i = 0; i < height; ++i) {
        // Первая строка клетки (тип + координаты)
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            std::string cell_content = frame[i][j].substr(0, frame[i][j].find(':')); // Тип и координаты
            std::cout << std::setw(9) << std::left << cell_content << "|";
        }
        std::cout << std::endl;

        // Вторая строка клетки (событие)
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            std::string event = frame[i][j].substr(frame[i][j].find(':') + 1); // Событие
            std::cout << std::setw(9) << std::left << event << "|";
        }
        std::cout << std::endl;

        // Нижняя граница клетки
        std::cout << std::string(width * 10 + 1, '_') << std::endl;
    }
}

void drawField(Field& field, World& world, std::shared_ptr<Player> player) {
    int width, height;
    field.GetSize(width, height);

    // Инициализация пустого поля
    std::vector<std::vector<std::string>> frame(height, std::vector<std::string>(width, ""));
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            // Получаем тип клетки и событие
            std::string cell_type = field.GetCellType(j, i).substr(0, 1); // P, I, S
            std::string event = "";
            auto cell = field.GetCell(j, i);
            if (cell->GetEvent()) {
                if (dynamic_cast<TrapEvent*>(cell->GetEvent().get())) {
                    event = "Trap";
                } else {
                    event = "Event";
                }
            } else {
                event = "    ";
            }
            // Формируем строку: тип клетки + координаты + событие
            frame[i][j] = cell_type + " (" + std::to_string(j) + "," + std::to_string(i) + "):" + event;
        }
    }

    // Отображение врагов
    for (const auto& enemy_weak : world.Enemies().GetEnemies()) {
        if (auto enemy = enemy_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(enemy, x, y)) {
                frame[y][x] = "E " + std::to_string(enemy->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):    ";
            }
        }
    }

    // Отображение вражеских зданий
    for (const auto& building_weak : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto building = building_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(building, x, y)) {
                frame[y][x] = "B " + std::to_string(building->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):    ";
            }
        }
    }

    // Отображение башен
    for (const auto& tower_weak : world.EnemiesTowers().GetEnemiesTowers()) {
        if (auto tower = tower_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(tower, x, y)) {
                frame[y][x] = "T " + std::to_string(tower->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):    ";
            }
        }
    }

    // Отображение союзников
    for (const auto& ally_weak : world.Allyes().GetAllyes()) {
        if (auto ally = ally_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(ally, x, y)) {
                frame[y][x] = "A " + std::to_string(ally->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):    ";
            }
        }
    }

    // Отображение игрока
    int x, y;
    if (field.GetPosEntity(player, x, y)) {
        frame[y][x] = "P" + std::to_string(player->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):    ";
    }

    // Вывод поля с передачей счета игрока
    visualizeField(frame, width, height, player->GetScore());
}

int main() {
    // Создание игрока
    std::shared_ptr<Player> player = std::make_shared<Player>(200, 100, 10);
    Field field(10, 10, 5, 10); // Поле 3x3, 1 непроходимая, 1 замедляющая клетка
    World world;

    // Инициализация мира с врагами, зданиями, башнями и союзниками
    world.Init(field, player, 0, 0, 20, 0); // 1 враг, 1 здание, 1 башня, 1 союзник

    std::cout << "Game started! Commands: w/a/s/d (move), r (change mode), b (buy spell), e X Y (attack), q I X Y (cast spell)\n";

    while (!player->IsDead()) {
        drawField(field, world, player);
        world.Update(field, player);
        world.DeleteDeadEntites(field);
    }

    std::cout << "Game Over! Player is dead. Final Score: " << player->GetScore() << "\n";
    return 0;
}