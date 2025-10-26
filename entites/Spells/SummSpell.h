#ifndef SUMMSPELL_H
#define SUMMSPELL_H

#include "ISummSpell.h"

class SummSpell : public ISummonSpell {
public:
	SummSpell();
	SummSpell(int);

	int getAllyCount() const override;
	void upgrade(int) override;
	bool use(const SpellContext&) override;
	SpellType getSpellType() const override;

private:
	int count_allies_;
};

#endif // SUMMSPELL_H