#include "TrapSpell.h"
#include "../../map/Field.h"

TrapSpell::TrapSpell() : TrapSpell(10) {};

TrapSpell::TrapSpell(int damage) : damage_(std::max(1, damage)) {};


void TrapSpell::upgrade(){
	damage_ *= 2;
}


bool TrapSpell::use(const SpellContext& context) {
	if (!context.cell || !context.field) {
		return false;
	}

	placeTrap(context.cell);

	std::cout << damage_ << "!!!!!!!!!!!!!___________!!!!!!!!!!" << std::endl;
	return true;
}

SpellType TrapSpell::getSpellType() const {
	return SpellType::Trap;
}

int TrapSpell::getTrapDamage() const{
	return damage_;
}

void TrapSpell::placeTrap(std::shared_ptr<Cell> cell){
	std::shared_ptr<TrapEvent> trap = std::make_shared<TrapEvent>(damage_);

	cell->SetEvent(trap);
}