/*
 * TangibleObjectMenuComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "TangibleObjectMenuComponent.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void TangibleObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	ObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	uint32 gameObjectType = sceneObject->getGameObjectType();

	if (!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);

	// Figure out what the object is and if its able to be Sliced.
	if(!tano->isSliceable())
		return;
	else { // Check to see if the player has the correct skill level
		if ((gameObjectType == SceneObject::PLAYERLOOTCRATE || sceneObject->isContainerObject()) && !player->hasSkill("combat_smuggler_novice"))
			return;
		else if (sceneObject->isMissionTerminal() && !player->hasSkill("combat_smuggler_slicing_01"))
			return;
		else if (sceneObject->isWeaponObject() && !player->hasSkill("combat_smuggler_slicing_02"))
			return;
		else if (sceneObject->isArmorObject() && !player->hasSkill("combat_smuggler_slicing_03"))
			return;

		menuResponse->addRadialMenuItem(69, 3, "@slicing/slicing:slice"); // Slice

	}
}

int TangibleObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	TangibleObject* tano = cast<TangibleObject*>( sceneObject);


	if (selectedID == 69) { // Slice [PlayerLootCrate]
		if (player->containsActiveSession(SessionFacadeType::SLICING)) {
			player->sendSystemMessage("@slicing/slicing:already_slicing");
			return 0;
		}

		//Create Session
		ManagedReference<SlicingSession*> session = new SlicingSession(player);
		session->initalizeSlicingMenu(player, tano);

		return 0;
	} else
		return ObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);

}

