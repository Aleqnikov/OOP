#ifndef IMPASSABLECELL_H
#define IMPASSABLECELL_H

#include "Cell.h"

class ImpassableCell : public Cell {
public:
    ImpassableCell() : Cell(nullptr) {};
    MoveResult EnterEntity(std::shared_ptr<Entity>) override;
    bool SpawnEntity(std::shared_ptr<Entity>){return false;}
    std::string GetName() const override { return "Impassable"; }

    std::shared_ptr<Cell> clone() const override {
        auto c = std::make_shared<ImpassableCell>();
        if (entity_) c->SpawnEntity(entity_->clone()); // клонируем сущность внутри
        return c;
    }


	bool SetEvent(std::shared_ptr<IEvent>);

private:
    // For Impasseble cell always not have entity.
    ImpassableCell(std::shared_ptr<Entity>) = delete;

};

#endif //IMPASSABLECELL_H