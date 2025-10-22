#ifndef IDIRDMGSPELL_H
#define IDIRDMGSPELL_H

#include "ISpell.h"

class IDirDmgSpell : public ISpell {
public:
	virtual ~IDirDmgSpell() = default;

	SpellType getSpellType() const override { return SpellType::DirDmg; }

	virtual int getDamage() const = 0;
	virtual int getRange() const = 0;
};

#endif //IDIRDMGSPELL_H