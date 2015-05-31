/*
 * SignObjectImplementation.cpp
 *
 *  Created on: Nov 20, 2010
 *      Author: crush
 */


#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/building/BuildingObject.h"

int SignObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	switch (selectedID) {
	case 20: //Read Sign
		sendSignNameTo(player);
		break;
	default:
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

void SignObjectImplementation::sendSignNameTo(CreatureObject* player) {
	ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, SuiWindowType::NONE);
	suiBox->setPromptTitle("@sui:swg"); //Star Wars Galaxies
	suiBox->setPromptText(getDisplayedName());

	player->sendMessage(suiBox->generateMessage());
}

void SignObjectImplementation::initializeChildObject(SceneObject* controllerObject) {
	if (controllerObject == NULL)
		return;

	attachedObject = controllerObject;

	if (controllerObject->isBuildingObject())
		(cast<BuildingObject*>(controllerObject))->setSignObject(_this.getReferenceUnsafeStaticCast());
}
