// EnemyTowerManager.h
#ifndef ENEMYTOWERMANAGER_H
#define ENEMYTOWERMANAGER_H

#include <vector>
#include <memory>
#include "../../entites/EnemyTower.h"
#include "../../map/Field.h"
#include "../../entites/Spells/IDirDmgSpell.h"

class EnemyTowerManager {
public:
	bool SpawnEnemiesTowers(Field& field, int count);
	bool EnemiesTowersTurn(Field& field);
	const std::vector<std::weak_ptr<EnemyTower>>& GetEnemiesTowers() const;
	void DeleteDeadEnemiesTowers(Field& field);

private:
	std::shared_ptr<Entity> findTarget(int x, int y, Field& field);
	std::vector<std::weak_ptr<EnemyTower>> enemies_towers_;
};

#endif //ENEMYTOWERMANAGER_H