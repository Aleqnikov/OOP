#include "Weapon.h"
#include <algorithm>

Weapon::Weapon(int damage, int attack_radius, AttackMod mode)
	: base_damage_(damage > 0 ? damage : 50),
	  base_attack_radius_(attack_radius > 0 ? attack_radius : 2),
	  attack_mode_(mode) {}

void Weapon::ChangeAttackMod() {
	if (attack_mode_ == AttackMod::RangeCombat) {
		attack_mode_ = AttackMod::CloseCombat;
	} else {
		attack_mode_ = AttackMod::RangeCombat;
	}
}

int Weapon::GetDamage() const {
	if (attack_mode_ == AttackMod::CloseCombat) {
		return base_damage_ * 2;
	}
	return base_damage_;
}

int Weapon::GetAttackRadius() const {
	if (attack_mode_ == AttackMod::CloseCombat) {
		int reduced_radius = base_attack_radius_ / 2;
		return std::max(reduced_radius, 1);
	}
	return base_attack_radius_;
}

AttackMod Weapon::GetAttackMode() const {
	return attack_mode_;
}