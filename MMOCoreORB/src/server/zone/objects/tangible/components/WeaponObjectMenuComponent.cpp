/*
 * WeaponObjectMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/powerup/PowerupObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "WeaponObjectMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void WeaponObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if (!sceneObject->isTangibleObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if(weapon == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	if(weapon->hasPowerup()) {
		menuResponse->addRadialMenuItem(71, 3, "@powerup:mnu_remove_powerup"); // Remove Powerup
	}

	if(weapon->canRepair(player)) {
		menuResponse->addRadialMenuItem(70, 3, "@sui:repair"); // Slice
	}

}

int WeaponObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);
	if(weapon == NULL)
		return 1;

	if (selectedID == 69) {
		if (weapon->isSliced()) {
			player->sendSystemMessage("@slicing/slicing:already_sliced");
			return 0;
		}

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::SLICING);
		ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

		if (session != NULL) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, weapon);

		return 0;

	}

	if(selectedID == 70) {

		weapon->repair(player);

		return 1;
	}

	if(selectedID == 71) {

		ManagedReference<PowerupObject*> pup = weapon->removePowerup();
		if(pup == NULL)
			return 1;

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
		if(inventory == NULL)
			return 1;

		inventory->transferObject(pup, -1, false);
		pup->sendTo(player, true);

		StringIdChatParameter message("powerup", "prose_remove_powerup"); //You detach your powerup from %TT.
		message.setTT(weapon->getDisplayedName());

		player->sendSystemMessage(message);

		return 1;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
