#include "SlowingCell.h"

MoveResult SlowingCell::EnterEntity(std::shared_ptr<Entity> entity) {
    if (entity->IsStatic())
        return MoveResult::Blocked;

    if (this->entity_ == nullptr) {
        this->entity_ = entity;
        entity->SetNotMoveNext(true);
        return MoveResult::Moved;
    }

    if (!entity->CanHit())
        return MoveResult::Blocked;

    if (entity->IsFriendly() != this->entity_->IsFriendly()) {
        this->entity_->CauseDamage(entity->GetDamage());
        return MoveResult::HitEntity;
    }

    return MoveResult::Blocked;
}