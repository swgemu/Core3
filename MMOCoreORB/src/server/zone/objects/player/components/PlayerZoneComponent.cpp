/*
 * PlayerZoneComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerZoneComponent.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"

void PlayerZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* newZone) {
	SceneObject* parent = sceneObject->getParent();

	/*if (parent == NULL && !sceneObject->isInQuadTree() && sceneObject->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( sceneObject);
		PlayerObject* ghost = player->getPlayerObject();

		uint64 savedParentID = 0;

		if (ghost != NULL && (savedParentID = ghost->getSavedParentID()) != 0) {
			sceneObject->setParent(sceneObject->getZoneServer()->getObject(savedParentID));
		}


	}*/

	if (sceneObject->isPlayerCreature()) {
		PlayerObject* ghost = cast<CreatureObject*>(sceneObject)->getPlayerObject();

		ghost->setSavedTerrainName(newZone->getZoneName());
	}

	ZoneComponent::notifyInsertToZone(sceneObject, newZone);

	//sceneObject->info("blia", true);
}

void PlayerZoneComponent::notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == NULL || scno == sceneObject)
		return;

	if (scno->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( scno);

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost->isInvisible())
			return;
	}

	SceneObject* parent = scno->getParent();

	if (parent != NULL /*&& parent->isCellObject()*/) {
		return;
	}

	scno->sendTo(sceneObject, true);
}

void PlayerZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == NULL || scno == sceneObject)
		return;

	scno->sendDestroyTo(sceneObject);

	//sceneObject->removeNotifiedSentObject(scno);
}

void PlayerZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID) {
	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( sceneObject);
		PlayerObject* ghost = player->getPlayerObject();

		SceneObject* par = sceneObject->getParent();

		if (par->isVehicleObject()) {
			player->executeObjectControllerAction(String("dismount").hashCode());
		}

		ghost->setSavedParentID(0);
	}

	ZoneComponent::switchZone(sceneObject, newTerrainName, newPostionX, newPositionZ, newPositionY, parentID);
}

void PlayerZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	//sceneObject->setTeleporting(true);
	CreatureObject* player = NULL;

	if (sceneObject->isPlayerCreature()) {
		player = cast<CreatureObject*>( sceneObject);
	}

	if (player != NULL && sceneObject->getParent() != NULL) {
		SceneObject* par = sceneObject->getParent();

		if (par->isVehicleObject()) {
			player->executeObjectControllerAction(String("dismount").hashCode());
		}
	}

	ZoneComponent::teleport(sceneObject, newPositionX, newPositionZ, newPositionY, parentID);

	if (player != NULL) {
		PlayerObject* ghost = player->getPlayerObject();

		ghost->setTeleporting(true);
		ghost->updateLastValidatedPosition();
		player->setMovementCounter(0);
		ghost->setClientLastMovementStamp(0);
	}
}

/**
 * Updates position of this object to the rest of in range objects
 * @pre { this object is locked}
 * @post { this object is locked, in range objects are updated with the new position }
 * @param lightUpdate if true a standalone message is sent to the in range objects
 */
void PlayerZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) {
	ZoneComponent::updateZone(sceneObject, lightUpdate, sendPackets);

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( sceneObject);
		PlayerObject* ghost = player->getPlayerObject();

		ghost->setSavedParentID(0);
	}
}

void PlayerZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	ZoneComponent::updateZoneWithParent(sceneObject, newParent, lightUpdate, sendPackets);

	if (sceneObject->getParent() != NULL && sceneObject->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( sceneObject);
		PlayerObject* ghost = player->getPlayerObject();

		ghost->setSavedParentID(sceneObject->getParentID());
	}
}
/*
void PlayerZoneComponent::insertToBuilding(SceneObject* sceneObject, BuildingObject* building) {
	ZoneComponent::insertToBuilding(sceneObject, building);

	building->onEnter(dynamic_cast<CreatureObject*>(sceneObject));
}

void PlayerZoneComponent::removeFromBuilding(SceneObject* sceneObject, BuildingObject* building) {
	ZoneComponent::removeFromBuilding(sceneObject, building);

	building->onExit(dynamic_cast<CreatureObject*>(sceneObject));

}*/

void PlayerZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) {
	ZoneComponent::notifySelfPositionUpdate(sceneObject);

	if (sceneObject->getZone() == NULL)
		return;

	/*if (activeAreas.size() != 0) {
		info(String::valueOf(activeAreas.size()) + " areas", true);
	}*/

	/*SceneObject* parent = sceneObject->getParent();

	if (sceneObject->getActiveAreas()->size() == 0 && sceneObject->inRangeObjectCount() < 20) {
		if ((parent != NULL && !parent->isCellObject()) || parent == NULL) {
			sceneObject->getZone()->getCreatureManager()->spawnRandomCreaturesAround(sceneObject);
		}
	}*/
}

