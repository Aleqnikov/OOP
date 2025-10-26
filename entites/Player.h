#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"
#include <memory>
#include "Hand.h"

class Hand;

class Player : public Entity {
public:
	Player();
	Player(int, int, int);
	void ChangeAttackMod();
	bool IsFriendly() const override;
	int GetAttackRadius() const;
	int GetHealth() const;
	int GetDamage() const;

	std::shared_ptr<Hand> GetHand();

	int GetScore();
	void minusScore(int);
	void addScore(int);

private:
	int score_;
	std::shared_ptr<Weapon> weapon_;
	std::shared_ptr<Hand> hand_;
};

#endif // PLAYER_H