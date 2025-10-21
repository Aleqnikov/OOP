#ifndef ENEMYBUILDING_H
#define ENEMYBUILDING_H

#include "Entity.h"

enum class SpawnInterval { kDefault = 4 };

class EnemyBuilding : public Entity {
public:
	EnemyBuilding();
	EnemyBuilding(int steps_to_spawn);
	bool CanSpawn();
	bool IsFriendly() const override;
	std::shared_ptr<Entity> clone() const override;

private:
	int steps_to_spawn_;
};

#endif // ENEMYBUILDING_H