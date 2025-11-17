#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	bool IsFriendly() const override;
	TokenEntity serialise() const;
};

#endif // ENEMY_H