#ifndef ITRAPSPELL_H
#define ITRAPSPELL_H

#include "ISpell.h"
#include "../../map/cells/Cell.h"

class ITrapSpell : public ISpell {
public:
	virtual ~ITrapSpell() = default;



	virtual int getTrapDamage() const = 0;
	virtual void placeTrap(std::shared_ptr<Cell> cell) = 0;
};

#endif //ITRAPSPELL_H