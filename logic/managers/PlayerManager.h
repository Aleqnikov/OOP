#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include "../../entites/Player.h"
#include "../../map/Field.h"

class World;

enum class PlayerEvents {
	ChangeMod,
	Attack,
	Move
};

class PlayerManager {
public:
	void SpawnPlayer(Field& field, std::shared_ptr<Player> player);
	bool PlayerTurn(std::shared_ptr<Player>, PlayerEvents);
	bool PlayerTurn(std::shared_ptr<Player>, PlayerEvents, int, int, Field&, World&);
	bool PlayerTurn(std::shared_ptr<Player>, PlayerEvents, MoveType, Field&);
	void ManagePlayerTurn(std::shared_ptr<Player>, Field&, World&);
};

#endif // PLAYERMANAGER_H