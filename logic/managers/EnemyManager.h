#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <array>
#include <memory>
#include <vector>
#include "../../entites/Enemy.h"
#include "../../map/Field.h"

class EnemyManager {
public:
	bool SpawnEnemies(Field&, int);
	bool EnemiesTurn(std::shared_ptr<Player>, Field&);
	bool GetMoveForEnemy(Field&, std::array<MoveType, 4>&, std::shared_ptr<Entity>, std::weak_ptr<Entity>);
	void DeleteDeadEnemies(Field&);
	void AddEnemy(std::weak_ptr<Enemy> enemy);
	const std::vector<std::weak_ptr<Enemy>>& GetEnemies() const;

private:
	std::vector<std::weak_ptr<Enemy>> enemies_;
};

#endif // ENEMYMANAGER_H