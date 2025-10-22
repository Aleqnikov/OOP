#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../../entites/Player.h"
#include "../../entites/Spells/DirDamageSpell.h"
#include "../../entites/Spells/TrapSpell.h"
#include "../../entites/Spells/AreaDmgSpell.h"
#include "../../entites/Spells/EnhacementSpell.h"
#include "../../entites/Spells/SummSpell.h"


#include "../../map/Field.h"

class World;

class PlayerManager {
public:
	void SpawnPlayer(Field& field, std::shared_ptr<Player> player);

	// Новые методы с понятными именами
	bool ChangeAttackMode(std::shared_ptr<Player> player);
	bool Attack(std::shared_ptr<Player> player, int x, int y, Field& field, World& world);
	bool Move(std::shared_ptr<Player> player, MoveType move_type, Field& field);
	bool BuySpell(std::shared_ptr<Player> player);
	bool CastSpell(std::shared_ptr<Player> player, size_t spell_index, int x, int y, Field& field, World& world);

	void ManagePlayerTurn(std::shared_ptr<Player> player, Field& field, World& world);

private:
	std::shared_ptr<Entity> findTargetAt(int x, int y, Field& field, World& world);
	bool isInAttackRange(std::shared_ptr<Player> player, int target_x, int target_y, Field& field);
};

#endif // PLAYERMANAGER_H