/*
 * LightsaberObjectMenuComponent.cpp
 *
 *  Created on: 3/11/2012
 *      Author: kyle
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "LightsaberObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void LightsaberObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isTangibleObject())
		return;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);

	if(weapon == NULL)
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	String text = "@jedi_spam:open_saber";
	menuResponse->addRadialMenuItem(89, 3, text);

}

int LightsaberObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {

	if (!sceneObject->isTangibleObject())
		return 0;

	Reference<PlayerObject*> playObject = player->getPlayerObject();

	// Admins should be able to open.
	if (!sceneObject->isASubChildOf(player) && !playObject->isPrivileged())
		return 0;

	ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(sceneObject);

	if (weapon == NULL)
		return 1;

	// Handle opening sabers
	if (selectedID == 89) {

		ManagedReference<SceneObject*> parent = weapon->getParent().get();
		if (parent != NULL && parent->isPlayerCreature()){
			player->sendSystemMessage("@jedi_spam:saber_not_while_equpped");
			return 0;
		}

		weapon->sendContainerTo(player);
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
