#ifndef ISPELL_H
#define ISPELL_H

class ISpell{
private:
public:
	virtual ~ISpell() = default;
	virtual ISpell getSpellType() const = 0;
	int useSpell();

};


#endif //ISPELL_H
