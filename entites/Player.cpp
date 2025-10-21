#include "Player.h"

Player::Player()
	: Entity(),
	  score_(0),
	  weapon_(std::make_shared<Weapon>()) {}

Player::Player(int hp, int damage, int attack_radius)
	: Entity(),
	  score_(0),
	  weapon_(std::make_shared<Weapon>(damage, attack_radius)) {
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

std::shared_ptr<Entity> Player::clone() const {
	return std::make_shared<Player>(*this);
}