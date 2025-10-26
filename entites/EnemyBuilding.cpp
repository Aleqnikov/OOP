#include "EnemyBuilding.h"

EnemyBuilding::EnemyBuilding()
	: Entity(),
	  steps_to_spawn_(static_cast<int>(SpawnInterval::kDefault)) {
	can_hit_on_walking_ = false;
	can_move_on_cell_ = false;
}

EnemyBuilding::EnemyBuilding(int steps_to_spawn)
	: EnemyBuilding() {
	steps_to_spawn_ = steps_to_spawn >= 0 ? steps_to_spawn : static_cast<int>(SpawnInterval::kDefault);
}

bool EnemyBuilding::CanSpawn() {
	if (steps_to_spawn_ == 0) {
		steps_to_spawn_ = static_cast<int>(SpawnInterval::kDefault);
		return true;
	}
	steps_to_spawn_--;
	return false;
}

bool EnemyBuilding::IsFriendly() const {
	return false;
}
