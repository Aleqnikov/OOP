#include "Enemy.h"

Enemy::Enemy() : Entity() {
	can_hit_on_walking_ = true;
}

bool Enemy::IsFriendly() const {
	return false;
}

std::shared_ptr<Entity> Enemy::clone() const {
	return std::make_shared<Enemy>(*this);
}