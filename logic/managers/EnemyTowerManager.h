#ifndef ENEMYTOWERMANAGER_H
#define ENEMYTOWERMANAGER_H

#include <vector>
#include <memory>
#include "../../entites/EnemyTower.h"
#include "../../map/Field.h"
#include "../../entites/Spells/IDirDmgSpell.h"

class EnemyTowerManager {
public:
	bool SpawnEnemiesTowers(Field&, int);
	bool EnemiesTowersTurn(Field&);
	const std::vector<std::weak_ptr<EnemyTower>>& GetEnemiesTowers() const;
	void DeleteDeadEnemiesTowers(Field&);

private:
	std::shared_ptr<Entity> findTarget(int, int, Field&);
	std::vector<std::weak_ptr<EnemyTower>> enemies_towers_;
};

#endif //ENEMYTOWERMANAGER_H