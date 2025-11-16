#ifndef WEAPON_H
#define WEAPON_H

enum class AttackMod {
	RangeCombat,
	CloseCombat
};

class Weapon {
public:
	Weapon(int = 50, int = 2, AttackMod = AttackMod::RangeCombat);
	void ChangeAttackMod();
	int GetDamage() const;
	int GetAttackRadius() const;
	AttackMod GetAttackMode() const;

private:
	int base_damage_;
	int base_attack_radius_;
	AttackMod attack_mode_;
};

#endif // WEAPON_H