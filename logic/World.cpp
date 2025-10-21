#include "World.h"

void World::Init(Field& field, std::shared_ptr<Player> player, int count_enemies, int count_buildings) {
	playerManager_.SpawnPlayer(field, player);
	enemyManager_.SpawnEnemies(field, count_enemies);
	buildingManager_.SpawnEnemiesBuildings(field, count_buildings);
}

void World::Update(Field& field, std::shared_ptr<Player> player) {
	playerManager_.ManagePlayerTurn(player, field, *this);
	enemyManager_.EnemiesTurn(player, field);
	buildingManager_.EnemiesBuildingTurn(field, *this);
}

void World::DeleteDeadEntites(Field& field) {
	enemyManager_.DeleteDeadEnemies(field);
	buildingManager_.DeleteDeadEnemiesBuildings(field);
}

PlayerManager& World::PlayerMan() {
	return playerManager_;
}

EnemyManager& World::Enemies() {
	return enemyManager_;
}

EnemyBuildingManager& World::EnemiesBuildings() {
	return buildingManager_;
}