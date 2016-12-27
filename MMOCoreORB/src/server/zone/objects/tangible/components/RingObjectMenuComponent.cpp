/*
 * RingObjectMenuComponent.cpp
 *
 *  Created on: 5/2/2014
 *      Author: Klivian
 */

#include "RingObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/wearables/WearableObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void RingObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isTangibleObject())
		return;

	WearableObject* wearable = cast<WearableObject*>(sceneObject);
	if (wearable == NULL)
		return;

	ZoneServer* server = player->getZoneServer();
	PlayerObject* ghost = player->getPlayerObject();

	if (server == NULL || ghost == NULL)
		return;

	if (!wearable->isEquipped() && !wearable->isNoTrade()) {
		if (ghost->isMarried()) {
			menuResponse->addRadialMenuItem(234, 3, "@unity:mnu_divorce"); // Divorce
		} else {
			uint64 targetID = player->getTargetID();
			ManagedReference<CreatureObject*> target = server->getObject(targetID, true).castTo<CreatureObject*>();

			if (target != NULL && target->isPlayerCreature())
				menuResponse->addRadialMenuItem(22, 3, "@unity:mnu_propose"); // Propose Unity
		}
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

}

int RingObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (selectedID == 22) { // Propose Unity
		if (!sceneObject->isASubChildOf(player))
			return 0;

		ManagedReference<SceneObject*> target = player->getZoneServer()->getObject(player->getTargetID());

		if (target != NULL && target->isPlayerCreature()) {
			PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

			if (playerManager != NULL)
				playerManager->proposeUnity(player, cast<CreatureObject*>(target.get()), sceneObject);

			return 0;
		} else {
			player->sendSystemMessage("@unity:bad_target"); // "You must have a valid player target to Propose Unity."
			return 0;
		}

	} else if (selectedID == 234) { // Divorce
		if (!sceneObject->isASubChildOf(player))
			return 0;

		PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager != NULL)
			playerManager->promptDivorce(player);

		return 0;
	}

	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
