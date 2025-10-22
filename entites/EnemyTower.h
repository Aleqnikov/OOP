#ifndef ENEMYTOWER_H
#define ENEMYTOWER_H

#include "Entity.h"
#include "Spells/IDirDmgSpell.h"

class EnemyTower : public Entity{
public:
	EnemyTower();
	EnemyTower(int, int);
	bool IsFriendly() const override;
	std::shared_ptr<Entity> clone() const override;

	std::shared_ptr<IDirDmgSpell> canAttack();

private:
	std::shared_ptr<IDirDmgSpell> spell_;

	int current_tick_ = 0;
	int base_tick_ = 2;
};

#endif //ENEMYTOWER_H
