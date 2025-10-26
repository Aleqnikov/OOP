#ifndef TRAPSPELL_H
#define TRAPSPELL_H

#include "ITrapSpell.h"
#include "../../map/cells/Events/TrapEvent.h"


class TrapSpell : public ITrapSpell {
public:
	TrapSpell();
	TrapSpell(int damage);

	void upgrade(int) override;
	bool use(const SpellContext&) override;

	SpellType getSpellType() const override;

	int getTrapDamage() const override;
	void placeTrap(std::shared_ptr<Cell>) override;

private:
	int damage_;
};



#endif //TRAPSPELL_H
