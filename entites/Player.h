#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"
#include <memory>

class Player : public Entity {
public:
	Player();
	Player(int hp, int damage, int attack_radius);
	void ChangeAttackMod();
	bool IsFriendly() const override;
	int GetAttackRadius() const;
	int GetHealth() const;
	int GetDamage() const;
	std::shared_ptr<Entity> clone() const override;

private:
	int score_;
	std::shared_ptr<Weapon> weapon_;
};

#endif // PLAYER_H