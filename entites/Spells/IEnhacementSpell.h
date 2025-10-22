#ifndef IENHANCEMENTSPELL_H
#define IENHANCEMENTSPELL_H

#include "ISpell.h"

class IEnhancementSpell : public ISpell {
public:
	virtual ~IEnhancementSpell() = default;

	virtual void applyEnhancement(std::shared_ptr<Hand>) = 0;
};

#endif //IENHANCEMENTSPELL_H

