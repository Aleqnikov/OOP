#ifndef AREADMGSPELL_H
#define AREADMGSPELL_H

#include "IAreaDmgSpell.h"


class AreaDmgSpell : public IAreaDmgSpell {
public:
	AreaDmgSpell();
	AreaDmgSpell(int area, int damage);

	void upgrade() override;
	bool use(const SpellContext& context) override;

	int getArea() const override;
	int getDamage() const override;

	SpellType getSpellType() const override;

private:
	int damage_;
	int area_;
};


#endif //AREADMGSPELL_H
