#include "Ally.h"


Ally::Ally() : Entity() {
	can_hit_on_walking_ = true;
}

bool Ally::IsFriendly() const {
	return true;
}