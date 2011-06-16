/*
 * SignObjectImplementation.cpp
 *
 *  Created on: Nov 20, 2010
 *      Author: crush
 */


#include "SignObject.h"
#include "SignObserver.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

int SignObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	case 20: //Read Sign
		sendSignNameTo(player);
		break;
	default:
		TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

void SignObjectImplementation::insertToZone(Zone* zone) {
	TangibleObjectImplementation::insertToZone(zone);

	signObserver = new SignObserver(_this);
}


void SignObjectImplementation::sendSignNameTo(PlayerCreature* player) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::NONE);
	suiBox->setPromptTitle("@sui:swg"); //Star Wars Galaxies
	suiBox->setPromptText(objectName.getDisplayedName());

	player->sendMessage(suiBox->generateMessage());
}
