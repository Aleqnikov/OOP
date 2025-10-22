#ifndef ISUMMONSPELL_H
#define ISUMMONSPELL_H

#include "ISpell.h"

class ISummonSpell : public ISpell {
public:
	virtual ~ISummonSpell() = default;
	virtual int getAllyCount() const = 0;
};

#endif //ISUMMONSPELL_H