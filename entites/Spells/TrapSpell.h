#ifndef TRAPSPELL_H
#define TRAPSPELL_H

#include "ITrapSpell.h"
#include "../../map/cells/Events/TrapEvent.h"


class TrapSpell : public ITrapSpell {
public:
	TrapSpell();
	TrapSpell(int damage);

	void upgrade() override;
	bool use(const SpellContext& context) override;

	SpellType getSpellType() const override;

	int getTrapDamage() const ;
	void placeTrap(std::shared_ptr<Cell> cell);

private:
	int damage_;
};



#endif //TRAPSPELL_H
