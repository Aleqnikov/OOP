#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"

class Enemy : public Entity {
public:
	Enemy();
	bool IsFriendly() const override;
	std::shared_ptr<Entity> clone() const override;
};

#endif // ENEMY_H