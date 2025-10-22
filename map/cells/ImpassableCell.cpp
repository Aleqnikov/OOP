#include "ImpassableCell.h"

MoveResult ImpassableCell::EnterEntity(std::shared_ptr<Entity>){
    return MoveResult::Unreal;
}

bool ImpassableCell::SetEvent(std::shared_ptr<IEvent> event) {

	return false;

}