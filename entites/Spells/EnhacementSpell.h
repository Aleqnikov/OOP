#ifndef ENHACEMENTSPELL_H
#define ENHACEMENTSPELL_H

#include "IEnhacementSpell.h"


class EnhacementSpell : public IEnhancementSpell {
public:
	bool use(const SpellContext& context) override;
	SpellType getSpellType() const override;
	void applyEnhancement(std::shared_ptr<Hand>) override;
	void upgrade() override;
};


#endif //ENHACEMENTSPELL_H
