#ifndef SLOWINGCELL_H
#define SLOWINGCELL_H

#include "Cell.h"

class SlowingCell : public Cell {
public:
    MoveResult EnterEntity(std::shared_ptr<Entity>) override;

    std::shared_ptr<Cell> clone() const override {
        auto c = std::make_shared<SlowingCell>();
        if (entity_) c->SpawnEntity(entity_->clone());
        return c;
    }

    std::string GetName() const override { return "Slowing"; };
};

#endif //SLOWINGCELL_H