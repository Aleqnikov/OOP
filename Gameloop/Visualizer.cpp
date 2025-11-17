#include "Visualizer.h"
#include <iostream>
#include <iomanip>
#include "../map/cells/Events/TrapEvent.h"

void Visualizer::PrintFrame(const std::vector<std::vector<std::string>>& frame,
                            int width, int height, int player_score)
{
    std::cout << "\n=== Player Score: " << player_score << " ===\n\n";

    // Верхняя граница
    std::cout << "+";
    for (int j = 0; j < width; ++j) {
        std::cout << "----------+";
    }
    std::cout << "\n";

    for (int i = 0; i < height; ++i) {
        // Строка с типом клетки и сущностью
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            const std::string& full = frame[i][j];
            size_t p = full.find(':');
            std::string type = (p == std::string::npos ? full : full.substr(0, p));

            // Ограничиваем длину до 10 символов
            if (type.length() > 10) {
                type = type.substr(0, 9) + ".";
            }

            std::cout << std::setw(10) << std::left << type << "|";
        }
        std::cout << "\n";

        // Строка с событиями (если есть)
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            const std::string& full = frame[i][j];
            size_t p = full.find(':');
            std::string event = (p == std::string::npos ? "" : full.substr(p + 1));

            if (event.empty()) {
                std::cout << "          |";
            } else {
                if (event.length() > 10) {
                    event = event.substr(0, 9) + ".";
                }
                std::cout << std::setw(10) << std::left << event << "|";
            }
        }
        std::cout << "\n";

        // Разделитель между строками
        std::cout << "+";
        for (int j = 0; j < width; ++j) {
            std::cout << "----------+";
        }
        std::cout << "\n";
    }

    // Легенда
    std::cout << "\nLegend: P=Player, E=Enemy, B=Building, T=Tower, A=Ally\n";
    std::cout << "Cells: C=Cell, S=Slowing, I=Impassable\n";
}


void Visualizer::Draw(Field& field, World& world, const std::shared_ptr<Player>& player) {
    int width, height;
    field.GetSize(width, height);

    std::vector<std::vector<std::string>> frame(height, std::vector<std::string>(width));

    // Заполняем клетки и события
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::string type_full = field.GetCellType(x, y);
            std::string type;

            // Определяем тип клетки с цветным префиксом
            if (type_full == "Cell") {
                type = "C";
            } else if (type_full == "Slowing") {
                type = "S";
            } else if (type_full == "Impassable") {
                type = "I";
            } else {
                type = "?";
            }

            type += "(" + std::to_string(x) + "," + std::to_string(y) + ")";

            // Проверяем события
            std::string event = "";
            auto cell = field.GetCell(x, y);
            if (cell && cell->GetEvent()) {
                if (dynamic_cast<TrapEvent*>(cell->GetEvent().get())) {
                    event = "Trap";
                } else {
                    event = "Event";
                }
            }

            frame[y][x] = type + ":" + event;
        }
    }

    // Отображаем врагов
    for (const auto& e : world.Enemies().GetEntities()) {
        if (auto enemy = e.lock()) {
            int x, y;
            if (field.GetPosEntity(enemy, x, y) && y < height && x < width) {
                frame[y][x] = "E" + std::to_string(enemy->GetHP()) +
                              "(" + std::to_string(x) + "," + std::to_string(y) + "):";
            }
        }
    }

    // Отображаем здания
    for (const auto& e : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto building = e.lock()) {
            int x, y;
            if (field.GetPosEntity(building, x, y) && y < height && x < width) {
                frame[y][x] = "B" + std::to_string(building->GetHP()) +
                              "(" + std::to_string(x) + "," + std::to_string(y) + "):";
            }
        }
    }

    // Отображаем башни
    for (const auto& e : world.EnemiesTowers().GetEnemiesTowers()) {
        if (auto tower = e.lock()) {
            int x, y;
            if (field.GetPosEntity(tower, x, y) && y < height && x < width) {
                frame[y][x] = "T" + std::to_string(tower->GetHP()) +
                              "(" + std::to_string(x) + "," + std::to_string(y) + "):";
            }
        }
    }

    // Отображаем союзников
    for (const auto& e : world.Allyes().GetEntities()) {
        if (auto ally = e.lock()) {
            int x, y;
            if (field.GetPosEntity(ally, x, y) && y < height && x < width) {
                frame[y][x] = "A" + std::to_string(ally->GetHP()) +
                              "(" + std::to_string(x) + "," + std::to_string(y) + "):";
            }
        }
    }

    // Отображаем игрока (поверх всего)
    int px, py;
    if (field.GetPosEntity(player, px, py) && py < height && px < width) {
        frame[py][px] = "P" + std::to_string(player->GetHP()) +
                        "(" + std::to_string(px) + "," + std::to_string(py) + "):";
    }

    PrintFrame(frame, width, height, player->GetScore());
}