// EnemyTower.cpp
#include "EnemyTower.h"
#include "Spells/DirDamageSpell.h"



EnemyTower::EnemyTower(int radius, int damage)
	: Entity() {
	can_hit_on_walking_ = false;
	can_move_on_cell_ = false;
	spell_ = std::make_shared<DirDamageSpell>(radius, damage);
}

EnemyTower::EnemyTower() : EnemyTower(2, 5) {};

bool EnemyTower::IsFriendly() const {
	return false;
}



std::shared_ptr<IDirDmgSpell> EnemyTower::canAttack() {
	if (current_tick_ != 0) {
		current_tick_--;
		return nullptr;
	}
	current_tick_ = base_tick_;
	return spell_;
}