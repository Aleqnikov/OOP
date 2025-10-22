#ifndef CELL_H
#define CELL_H

#include <memory>
#include <string>

#include "../../entites/Entity.h"
#include "../../entites/Player.h"
#include "Events/IEvent.h"

enum class MoveResult {
	BlockedByWall,
	Moved,
	HitEntity,
	Blocked,
	Unreal
};


class Cell {
public:
	Cell(std::shared_ptr<Entity> entity) : entity_(entity) {};

	Cell() : entity_(nullptr) {};

	bool IsEmpty() const;

	virtual MoveResult EnterEntity(std::shared_ptr<Entity>);

	bool RemoveEntity(std::shared_ptr<Entity>);

	bool SpawnEntity(std::shared_ptr<Entity>);

	bool EqualEntites(std::shared_ptr<Entity>);

	// For correct deep copy.
	virtual std::shared_ptr<Cell> clone() const {
		auto c = std::make_shared<Cell>();
		if (entity_) c->SpawnEntity(entity_->clone());
		return c;
	}

	bool SetEvent(std::shared_ptr<IEvent>);
	std::shared_ptr<IEvent> GetEvent();

	std::shared_ptr<Entity> GetEntity() const { return entity_; }

	virtual std::string GetName() const { return "Cell"; }

protected:
	std::shared_ptr<Entity> entity_;
	std::shared_ptr<IEvent> event_;
};

#endif //CELL_H
