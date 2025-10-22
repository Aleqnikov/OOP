#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>
#include "Spells/ISpell.h" // Явное включение ISpell.h

class Hand {
public:
	Hand();
	explicit Hand(int limit);

	bool addSpell(std::shared_ptr<ISpell> spell);
	std::shared_ptr<ISpell> getSpell(size_t index);
	bool removeSpell(size_t index);

	bool enableNextUpgrade();
	bool isUpgradeEnabled() const;

	size_t size() const;
	size_t capacity() const;
	bool isFull() const;

private:
	std::vector<std::shared_ptr<ISpell>> spells_;
	int limit_;
	bool next_upgrade_enabled_;
};

#endif // HAND_H