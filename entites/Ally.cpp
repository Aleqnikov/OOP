#include "Ally.h"


Ally::Ally() : Entity() {
	can_hit_on_walking_ = true;
}

bool Ally::IsFriendly() const {
	return true;
}

std::shared_ptr<Entity> Ally::clone() const {
	return std::make_shared<Ally>(*this);
}
