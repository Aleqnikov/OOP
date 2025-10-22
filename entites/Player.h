#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"
#include <memory>
#include "Hand.h"

// Forward declaration для Hand
class Hand;

class Player : public Entity {
public:
	Player();
	Player(int hp, int damage, int attack_radius);
	void ChangeAttackMod();
	bool IsFriendly() const override;
	int GetAttackRadius() const;
	int GetHealth() const;
	int GetDamage() const;

	std::shared_ptr<Hand> GetHand();

	int GetScore();
	void minusScore(int);
	void addScore(int);
	std::shared_ptr<Entity> clone() const override;

private:
	int score_;
	std::shared_ptr<Weapon> weapon_;
	std::shared_ptr<Hand> hand_;
};

#endif // PLAYER_H