#include "World.h"

void World::Init(Field& field, std::shared_ptr<Player> player, int count_enemies, int count_buildings, int count_towers, int count_allies) {
	playerManager_.SpawnPlayer(field, player);
	enemyManager_.SpawnEnemies(field, count_enemies);
	buildingManager_.SpawnEnemiesBuildings(field, count_buildings);
	towerManager_.SpawnEnemiesTowers(field, count_towers);
	allyManager_.SpawnAllys(field, count_allies);
}

void World::Update(Field& field, std::shared_ptr<Player> player) {
	playerManager_.ManagePlayerTurn(player, field, *this);
	enemyManager_.EnemiesTurn(player, field);
	buildingManager_.EnemiesBuildingTurn(field, *this);
	towerManager_.EnemiesTowersTurn(field);
	allyManager_.findAllyes(field);
	allyManager_.AllyTurn(field);
}

void World::DeleteDeadEntites(Field& field) {
	enemyManager_.DeleteDeadEnemies(field);
	buildingManager_.DeleteDeadEnemiesBuildings(field);
	towerManager_.DeleteDeadEnemiesTowers(field);
	allyManager_.DeleteDeadAllys(field);
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

EnemyTowerManager& World::EnemiesTowers() {
	return towerManager_;
}

AllyManager& World::Allyes() {
	return allyManager_;
}