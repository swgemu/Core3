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

void PlayerZoneComponent::notifyInsert(SceneObject* sceneObject, QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) entry;

	if (scno == NULL || scno == sceneObject)
		return;

	if (scno->isPlayerCreature()) {
		CreatureObject* player = (CreatureObject*) scno;

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost->isInvisible())
			return;

	}

	//TODO: fix cell movement for this to not happen
	/*SceneObject* grandParent = getRootParent();

	if (parent != NULL) {
		if (grandParent == scno) { // we already should have sent our grandParent to owner

			if (grandParent->isBuildingObject())
				((BuildingObject*)grandParent)->addNotifiedSentObject(sceneObject);

			return;
		}
	}

	if (scno->getParent() != NULL) {
		//check the parent if its building
		//check if the building has me as notified
		//if it has me than send the object without the buio
		//if it hasnt me than dont send me and wait for the building to be sent
		//TODO: check if we need this for every object or only for buildings
		SceneObject* scnoGrandParent = scno->getRootParent();

		if (scnoGrandParent->isBuildingObject()) {
			BuildingObject* building = (BuildingObject*)scnoGrandParent;

			if (!building->hasNotifiedSentObject(sceneObject))
				return;
		} else // we wait for the Objects parent to get sent
			return;
	}

	if (scno->isBuildingObject())
		((BuildingObject*)scno)->addNotifiedSentObject(sceneObject);*/

	SceneObject* rootParent = scno->getRootParent();

	if (rootParent != NULL && rootParent->isInQuadTree()) {
		if (sceneObject->hasNotifiedSentObject(rootParent) && sceneObject->addNotifiedSentObject(scno) != -1)
			scno->sendTo(sceneObject, true);
		else {
			if (sceneObject->addNotifiedSentObject(rootParent) != -1)
				rootParent->sendTo(sceneObject, true);
		}
	} else if (sceneObject->addNotifiedSentObject(scno) != -1)
		scno->sendTo(sceneObject, true);
}

void PlayerZoneComponent::notifyDissapear(SceneObject* sceneObject, QuadTreeEntry* entry) {
	SceneObject* scno = (SceneObject*) entry;

	if (scno == NULL || scno == sceneObject)
		return;

	scno->sendDestroyTo(sceneObject);

	sceneObject->removeNotifiedSentObject(scno);
}


void PlayerZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) {
	//sceneObject->setTeleporting(true);

	ZoneComponent::teleport(sceneObject, newPositionX, newPositionZ, newPositionY, parentID);

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = (CreatureObject*) sceneObject;
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
		CreatureObject* player = (CreatureObject*) sceneObject;
		PlayerObject* ghost = player->getPlayerObject();

		ghost->setSavedParentID(0);
	}
}

void PlayerZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) {
	ZoneComponent::updateZoneWithParent(sceneObject, newParent, lightUpdate, sendPackets);

	if (sceneObject->getParent() != NULL && sceneObject->isPlayerCreature()) {
		CreatureObject* player = (CreatureObject*) sceneObject;
		PlayerObject* ghost = player->getPlayerObject();

		ghost->setSavedParentID(sceneObject->getParentID());
	}
}

void PlayerZoneComponent::insertToBuilding(SceneObject* sceneObject, BuildingObject* building) {
	ZoneComponent::insertToBuilding(sceneObject, building);

	building->onEnter(dynamic_cast<CreatureObject*>(sceneObject));
}

void PlayerZoneComponent::removeFromBuilding(SceneObject* sceneObject, BuildingObject* building) {
	ZoneComponent::removeFromBuilding(sceneObject, building);

	building->onExit(dynamic_cast<CreatureObject*>(sceneObject));
}

void PlayerZoneComponent::notifySelfPositionUpdate(SceneObject* sceneObject) {
	ZoneComponent::notifySelfPositionUpdate(sceneObject);

	if (sceneObject->getZone() == NULL)
		return;

	/*if (activeAreas.size() != 0) {
		info(String::valueOf(activeAreas.size()) + " areas", true);
	}*/

	SceneObject* parent = sceneObject->getParent();

	if (sceneObject->getActiveAreas()->size() == 0 && sceneObject->inRangeObjectCount() < 20) {
		if ((parent != NULL && !parent->isCellObject()) || parent == NULL) {
			sceneObject->getZone()->getCreatureManager()->spawnRandomCreaturesAround(sceneObject);
		}
	}
}

