#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>
#include <random>

#include "Spells/ISpell.h"
#include "Spells/TrapSpell.h"
#include "Spells/SummSpell.h"
#include "Spells/EnhacementSpell.h"
#include "Spells/DirDamageSpell.h"
#include "Spells/AreaDmgSpell.h"


class Hand {
public:
	Hand();
	explicit Hand(int limit);

	bool addSpell(std::shared_ptr<ISpell> spell);
	std::shared_ptr<ISpell> getSpell(size_t index);
	bool removeSpell(size_t index);

	void setUpgradeCoef(int);
	int isUpgradeEnabled() const;

	size_t size() const;
	size_t capacity() const;
	bool isFull() const;

	void setRandomSpell();

private:
	std::vector<std::shared_ptr<ISpell>> spells_;
	int limit_;
	int upgrade_coef_;
};

#endif // HAND_H