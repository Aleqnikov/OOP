#ifndef WORLD_H
#define WORLD_H

#include "./managers/EnemyManager.h"
#include "./managers/EnemyBuildingManager.h"
#include "./managers/PlayerManager.h"
#include "../map/Field.h"

class World {
public:
	void Init(Field& field, std::shared_ptr<Player> player, int count_enemies, int count_buildings);
	void Update(Field& field, std::shared_ptr<Player> player);
	void DeleteDeadEntites(Field& field);
	PlayerManager& PlayerMan();
	EnemyManager& Enemies();
	EnemyBuildingManager& EnemiesBuildings();

private:
	EnemyManager enemyManager_;
	PlayerManager playerManager_;
	EnemyBuildingManager buildingManager_;
};

#endif // WORLD_H