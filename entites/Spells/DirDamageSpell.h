#ifndef DIRDAMAGESPELL_H
#define DIRDAMAGESPELL_H

#include "IDirDmgSpell.h"

class DirDamageSpell : public IDirDmgSpell {
public:
	DirDamageSpell();
	DirDamageSpell(int range, int damage);

	void upgrade() override;
	bool use(const SpellContext& context) override;

	int getDamage() const override;
	int getRange() const override;

private:
	int damage_;
	int range_;
};

#endif //DIRDAMAGESPELL_H