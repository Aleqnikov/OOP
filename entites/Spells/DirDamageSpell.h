#ifndef DIRDAMAGESPELL_H
#define DIRDAMAGESPELL_H

#include "IDirDmgSpell.h"

class DirDamageSpell : public IDirDmgSpell {
public:
	DirDamageSpell();
	DirDamageSpell(int, int);

	void upgrade(int) override;
	bool use(const SpellContext&) override;

	int getDamage() const override;
	int getRange() const override;

	SpellType getSpellType() const override;

private:
	int damage_;
	int range_;
};

#endif //DIRDAMAGESPELL_H