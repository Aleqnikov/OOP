// Hand.cpp
#include "Hand.h"

Hand::Hand(int limit)
	: limit_(std::max(limit, 5)), next_upgrade_enabled_(false) {}

Hand::Hand()
	: Hand(5) {}

bool Hand::addSpell(std::shared_ptr<ISpell> spell) {
	if (!spell || spells_.size() >= static_cast<size_t>(limit_))
		return false;

	spells_.push_back(spell);
	return true;
}

bool Hand::removeSpell(size_t index) {
	if (index >= spells_.size())
		return false;

	spells_.erase(spells_.begin() + index);
	return true;
};


std::shared_ptr<ISpell> Hand::getSpell(size_t index) {
	if (index >= spells_.size())
		return nullptr;

	if (next_upgrade_enabled_) {
		next_upgrade_enabled_ = false;
		spells_[index]->upgrade();
	}

	return spells_[index];
}

bool Hand::enableNextUpgrade() {
	if (next_upgrade_enabled_)
		return false;

	next_upgrade_enabled_ = true;
	return true;
}

bool Hand::isUpgradeEnabled() const {
	return next_upgrade_enabled_;
}

size_t Hand::size() const {
	return spells_.size();
}

size_t Hand::capacity() const {
	return limit_;
}

bool Hand::isFull() const {
	return spells_.size() >= static_cast<size_t>(limit_);
}