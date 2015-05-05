/*
 * CloningTerminalMenuComponent.cpp
 *
 *  Created on: 01/13/2012
 *      Author: Elvaron
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "CloningTerminalMenuComponent.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/CloningStoreSuiCallback.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

void CloningTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int CloningTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	ManagedReference<CityRegion* > region = sceneObject->getCityRegion().get();

	if (region != NULL) {
		if (region->isBanned(player->getObjectID())) {
				player->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
				return 0;
		}
	}

	if(selectedID == 20) {

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ManagedReference<BuildingObject*> cloner = sceneObject->getRootParent().get().castTo<BuildingObject*>();

		if (cloner != NULL && (ghost->getCloningFacility() == cloner->getObjectID())) {
			player->sendSystemMessage("Your clone data is already stored here.");
			return 0;
		}

		ZoneServer* server = player->getZoneServer();

		ManagedReference<SuiMessageBox*> cloneConfirm = new SuiMessageBox(player, SuiWindowType::CLONE_CONFIRM);
		cloneConfirm->setUsingObject(sceneObject);
		cloneConfirm->setPromptTitle("@base_player:clone_confirm_title");
		cloneConfirm->setPromptText("@base_player:clone_confirm_prompt");
		cloneConfirm->setCancelButton(true, "");
		cloneConfirm->setForceCloseDistance(32.f);

		cloneConfirm->setCallback(new CloningStoreSuiCallback(server));

		ghost->addSuiBox(cloneConfirm);
		player->sendMessage(cloneConfirm->generateMessage());
	}

	return 0;
}

