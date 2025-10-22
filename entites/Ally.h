#ifndef ALLY_H
#define ALLY_H

#include "Entity.h"

class Ally : public Entity{
public:
	Ally();
	bool IsFriendly() const override;
	std::shared_ptr<Entity> clone() const override;
};



#endif //ALLY_H
