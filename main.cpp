#include <iostream>
#include "./map/Field.h"
#include "./entites/Player.h"
#include "./logic/World.h"

void visualizeField(std::vector<std::vector<std::string>> frame, int width, int height) {
    for (int i = 0; i < height; i++) {
        std::cout << "|";
        for (int j = 0; j < width; j++) {
            int fix = 5 - frame[i][j].size();
            for (int k = 0; k < fix; k++) std::cout << " ";
            std::cout << frame[i][j] << "|";
        }
        std::cout << std::endl;
    }
}

void drawField(Field& field, World& world, std::shared_ptr<Player> player) {
    std::vector<std::vector<std::string>> pre_frame;
    int h, w;
    field.GetSize(w, h);
    pre_frame.resize(h);
    for (int i = 0; i < h; i++) {
        pre_frame[i].resize(w);
        for (int j = 0; j < w; j++) {
            std::string str = field.GetCellType(j, i);
            pre_frame[i][j].push_back(str[0]);
        }
    }

    for (const auto& enemy_weak : world.Enemies().GetEnemies()) {
        if (auto enemy = enemy_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(enemy, x, y)) {
                pre_frame[y][x] += "E ";
                pre_frame[y][x] += std::to_string(enemy->GetHP());
            }
        }
    }

    for (const auto& building_weak : world.EnemiesBuildings().GetEnemiesBuildings()) {
        if (auto building = building_weak.lock()) {
            int x, y;
            if (field.GetPosEntity(building, x, y)) {
                pre_frame[y][x] += "B ";
                pre_frame[y][x] += std::to_string(building->GetHP());
            }
        }
    }

    int x, y;
    if (field.GetPosEntity(player, x, y)) {
        pre_frame[y][x] += "P ";
        pre_frame[y][x] += std::to_string(player->GetHP());
    }

    visualizeField(pre_frame, w, h);
}

int main() {
    std::shared_ptr<Player> player = std::make_shared<Player>(200, 100, 10);
    Field field(10, 10, 5, 32);
    World world;
    world.Init(field, player, 1, 1);
    drawField(field, world, player);

    while (!player->IsDead()) {
        world.Update(field, player);
        drawField(field, world, player);
        world.DeleteDeadEntites(field);
    }
    return 0;
}