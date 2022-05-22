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
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/sui/callbacks/CloningStoreSuiCallback.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/ZoneServer.h"

void CloningTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int CloningTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (!sceneObject->isTangibleObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	ManagedReference<CityRegion* > region = sceneObject->getCityRegion().get();

	if (region != nullptr) {
		if (region->isBanned(player->getObjectID())) {
				player->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
				return 0;
		}
	}

	if(selectedID == 20) {

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
		ManagedReference<BuildingObject*> cloner = cast<BuildingObject*>(sceneObject->getRootParent());

		if (cloner != nullptr && (ghost->getCloningFacility() == cloner->getObjectID())) {
			player->sendSystemMessage("Your clone data is already stored here.");
			return 0;
		}

		ZoneServer* server = player->getZoneServer();

		ManagedReference<SuiMessageBox*> cloneConfirm = new SuiMessageBox(player, SuiWindowType::CLONE_CONFIRM);
		cloneConfirm->setUsingObject(sceneObject);

		bool hasCoupon = hasCloningCoupon(player);

		if (hasCoupon) {
			cloneConfirm->setPromptTitle("@base_player:clone_confirm_coupon_title");
			cloneConfirm->setPromptText("@base_player:clone_confirm_coupon_prompt");
		} else {
			cloneConfirm->setPromptTitle("@base_player:clone_confirm_title");
			cloneConfirm->setPromptText("@base_player:clone_confirm_prompt");
		}

		cloneConfirm->setCancelButton(true, "");
		cloneConfirm->setForceCloseDistance(32.f);

		cloneConfirm->setCallback(new CloningStoreSuiCallback(server, hasCoupon));

		ghost->addSuiBox(cloneConfirm);
		player->sendMessage(cloneConfirm->generateMessage());
	}

	return 0;
}

bool CloningTerminalMenuComponent::hasCloningCoupon(CreatureObject* player) const {
	if (player == nullptr)
		return false;

	Locker lock(player);

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return false;

	uint32 couponCRC = STRING_HASHCODE("object/tangible/item/new_player/new_player_cloning_coupon.iff");

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		SceneObject* sceneO = inventory->getContainerObject(i);

		if (sceneO == nullptr)
			continue;

		if (sceneO->getServerObjectCRC() == couponCRC)
			return true;
	}

	return false;
}