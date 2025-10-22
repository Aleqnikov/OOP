#include "EnhacementSpell.h"
#include "./Hand.h"

SpellType EnhacementSpell::getSpellType() const  {
	return SpellType::Enhancement;
}

bool EnhacementSpell::use(const SpellContext& context){
	if (context.hand) {
		applyEnhancement(context.hand);
		return true;
	}

	return false;
}


void EnhacementSpell::applyEnhancement(std::shared_ptr<Hand> hand) {
	hand->enableNextUpgrade();
}

void EnhacementSpell::upgrade() {
	return;
}