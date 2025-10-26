#ifndef IDIRDMGSPELL_H
#define IDIRDMGSPELL_H

#include "ISpell.h"

class IDirDmgSpell : public ISpell {
public:
	virtual ~IDirDmgSpell() = default;

	virtual int getDamage() const = 0;
	virtual int getRange() const = 0;
};

#endif //IDIRDMGSPELL_H