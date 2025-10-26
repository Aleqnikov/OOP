#include "Player.h"

Player::Player()
	: Entity(),
	  score_(0),
	  weapon_(std::make_shared<Weapon>()) {}

Player::Player(int hp, int damage, int attack_radius)
	: Entity(),
	  score_(1000),
	  weapon_(std::make_shared<Weapon>(damage, attack_radius))
{
	hand_ = std::make_shared<Hand>(5);
	hp_ = hp > 0 ? hp : 100;
}

void Player::ChangeAttackMod() {
	weapon_->ChangeAttackMod();
}

bool Player::IsFriendly() const {
	return true;
}

int Player::GetAttackRadius() const {
	return weapon_->GetAttackRadius();
}

int Player::GetHealth() const {
	return hp_;
}

int Player::GetDamage() const {
	return weapon_->GetDamage();
}

int Player::GetScore() {
	return score_;
}
void Player::minusScore(int sum) {
	if (score_ > sum) {
		score_ -= sum;
	}
}
void Player::addScore(int add) {
	if (add > 0)
		score_ += add;
}

std::shared_ptr<Hand> Player::GetHand() {
	return hand_;
}
