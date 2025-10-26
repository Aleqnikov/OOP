#ifndef ENHACEMENTSPELL_H
#define ENHACEMENTSPELL_H

#include "IEnhacementSpell.h"


class EnhacementSpell : public IEnhancementSpell {
public:
	EnhacementSpell();
	EnhacementSpell(int);

	bool use(const SpellContext&) override;
	SpellType getSpellType() const override;
	void applyEnhancement(std::shared_ptr<Hand>) override;
	void upgrade(int) override;
	int getEnhancement() override;

private:
	int enhancement_;
};


#endif //ENHACEMENTSPELL_H
