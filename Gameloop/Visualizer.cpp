#include "Visualizer.h"
#include <iostream>
#include <iomanip>
#include "../map/cells/Events/TrapEvent.h"

void Visualizer::PrintFrame(const std::vector<std::vector<std::string>>& frame,
                            int width, int height, int player_score)
{
    std::cout << "\nPlayer Score: " << player_score << "\n";
    std::cout << std::string(width * 10 + 1, '-') << "\n";

    for (int i = 0; i < height; ++i) {
        std::cout << "|";
        for (int j = 0; j < width; ++j) {
            const std::string& full = frame[i][j];
            size_t p = full.find(':');
            std::string type = (p == std::string::npos ? full : full.substr(0, p));
            std::cout << std::setw(9) << std::left << type << "|";
        }
        std::cout << "\n|";

        for (int j = 0; j < width; ++j) {
            const std::string& full = frame[i][j];
            size_t p = full.find(':');
            std::string event = (p == std::string::npos ? "None" : full.substr(p + 1));
            std::cout << std::setw(9) << std::left << event << "|";
        }
        std::cout << "\n" << std::string(width * 10 + 1, '_') << "\n";
    }
}


void Visualizer::Draw(Field& field, World& world, const std::shared_ptr<Player>& player) {
    int width, height;
    field.GetSize(width, height);

    std::vector<std::vector<std::string>> frame(height, std::vector<std::string>(width));

    // Клетки и ивенты
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::string type_full = field.GetCellType(x, y);
            std::string type = type_full.empty() ? "?" : type_full.substr(0, 1);

            std::string event = "None";
            auto cell = field.GetCell(x, y);
            if (cell->GetEvent()) {
                if (dynamic_cast<TrapEvent*>(cell->GetEvent().get())) event = "Trap";
                else event = "Event";
            }

            frame[y][x] = type + "(" + std::to_string(x) + "," + std::to_string(y) + "):" + event;
        }
    }

    // Враги
    for (auto& e : world.Enemies().GetEntities()) {
        if (auto enemy = e.lock()) {
            int x, y;
            if (field.GetPosEntity(enemy, x, y))
                frame[y][x] = "E" + std::to_string(enemy->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):";
        }
    }

    // Здания
    for (auto& e : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto b = e.lock()) {
            int x, y;
            if (field.GetPosEntity(b, x, y))
                frame[y][x] = "B" + std::to_string(b->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):";
        }
    }

    // Башни
    for (auto& e : world.EnemiesTowers().GetEnemiesTowers()) {
        if (auto t = e.lock()) {
            int x, y;
            if (field.GetPosEntity(t, x, y))
                frame[y][x] = "T" + std::to_string(t->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):";
        }
    }

    // Союзники
    for (auto& e : world.Allyes().GetEntities()) {
        if (auto a = e.lock()) {
            int x, y;
            if (field.GetPosEntity(a, x, y))
                frame[y][x] = "A" + std::to_string(a->GetHP()) + "(" + std::to_string(x) + "," + std::to_string(y) + "):";
        }
    }

    // Игрок
    int px, py;
    if (field.GetPosEntity(player, px, py)) {
        frame[py][px] = "P" + std::to_string(player->GetHP()) + "(" + std::to_string(px) + "," + std::to_string(py) + "):";
    }

    PrintFrame(frame, width, height, player->GetScore());
}
