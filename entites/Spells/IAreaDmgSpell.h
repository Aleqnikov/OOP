#ifndef IAREADMGSPELL_H
#define IAREADMGSPELL_H

#include "ISpell.h"

class IAreaDmgSpell : public ISpell {
public:
	virtual ~IAreaDmgSpell() = default;



	virtual int getArea() const = 0;
	virtual int getDamage() const = 0;
};

#endif //IAREADMGSPELL_H