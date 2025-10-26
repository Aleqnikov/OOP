#ifndef WEAPON_H
#define WEAPON_H

enum class AttackMod {
	RangeCombat,
	CloseCombat
};

class Weapon {
public:
	Weapon(int = 50, int s = 2, AttackMod  = AttackMod::RangeCombat);
	void ChangeAttackMod();
	int GetDamage() const;
	int GetAttackRadius() const;
	AttackMod GetAttackMode() const;

private:
	int damage_;
	int attack_radius_;
	int initial_damage_;
	int initial_attack_radius_;
	AttackMod attack_mode_;
};

#endif // WEAPON_H