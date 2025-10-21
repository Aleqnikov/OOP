#include "ImpassableCell.h"

MoveResult ImpassableCell::EnterEntity(std::shared_ptr<Entity>){
    return MoveResult::Unreal;
}