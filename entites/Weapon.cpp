#include "Weapon.h"

Weapon::Weapon(int damage, int attack_radius, AttackMod mode)
	: damage_(damage > 0 ? damage : 50),
	  attack_radius_(attack_radius > 0 ? attack_radius : 2),
	  initial_damage_(damage > 0 ? damage : 50),
	  initial_attack_radius_(attack_radius > 0 ? attack_radius : 2),
	  attack_mode_(mode) {}

void Weapon::ChangeAttackMod() {
	if (attack_mode_ == AttackMod::RangeCombat) {
		damage_ = initial_damage_ * 2;
		attack_radius_ = initial_attack_radius_ / 2;
		if (attack_radius_ < 1) attack_radius_ = 1;
		attack_mode_ = AttackMod::CloseCombat;
	} else {
		damage_ = initial_damage_;
		attack_radius_ = initial_attack_radius_;
		attack_mode_ = AttackMod::RangeCombat;
	}
}

int Weapon::GetDamage() const {
	return damage_;
}

int Weapon::GetAttackRadius() const {
	return attack_radius_;
}

AttackMod Weapon::GetAttackMode() const {
	return attack_mode_;
}