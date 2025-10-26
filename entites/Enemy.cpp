#include "Enemy.h"

Enemy::Enemy() : Entity() {
	can_hit_on_walking_ = true;
}

bool Enemy::IsFriendly() const {
	return false;
}

