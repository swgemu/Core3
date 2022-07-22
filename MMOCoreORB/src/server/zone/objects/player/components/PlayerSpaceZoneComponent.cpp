/*
 * PlayerSpaceZoneComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerSpaceZoneComponent.h"

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/components/PlayerZoneComponent.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/TreeEntry.h"

void PlayerSpaceZoneComponent::notifyInsertToZone(SceneObject* sceneObject, SceneObject* newZone) const {

	bool isSpaceZone = false;
	String zoneName = "";
	SceneObject* zone = nullptr;
	//Logger::console.info("notify insert to player space zone");
	if (newZone->isSpaceZone()) {
		SpaceZone* zone = cast<SpaceZone*>(newZone);
		isSpaceZone = true;
		zoneName = zone->getZoneName();
		//Logger::console.info("New zone is space zone", true);
	} else {
		Zone* zone = cast<Zone*>(newZone);
		zoneName = zone->getZoneName();
	}

	//Logger::console.info("New zone name: " + zoneName);

	if (sceneObject->isPlayerCreature() && zone != nullptr) {
		PlayerObject* ghost = sceneObject->asCreatureObject()->getPlayerObject();

		if (ghost != nullptr)
			ghost->setSavedTerrainName(zoneName);

		//Logger::console.info("saved terrain name: " + ghost->getSavedTerrainName());
	}

	if (isSpaceZone)
		SpaceZoneComponent::notifyInsertToZone(sceneObject, cast<SpaceZone*>(newZone));
	//else {
	//	ZoneComponent::notifyInsertToZone(sceneObject, cast<Zone*>(newZone));
	//}
}

void PlayerSpaceZoneComponent::notifyInsert(SceneObject* sceneObject, TreeEntry* entry) const {
	//Logger::console.info("notifyInsert", true);
	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == sceneObject)
		return;

	if (scno->isTangibleObject()) {
		TangibleObject* tano = scno->asTangibleObject();

		if (tano->isInvisible())
			return;
	}

	ManagedReference<SceneObject*> parent = scno->getParent().get();

	if (parent != nullptr /*&& parent->isCellObject()*/) {
		return;
	}

	scno->sendTo(sceneObject, true, false);
}

void PlayerSpaceZoneComponent::notifyDissapear(SceneObject* sceneObject, TreeEntry* entry) const {
	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == sceneObject)
		return;

	scno->sendDestroyTo(sceneObject);
}

void PlayerSpaceZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility) const {
	//Logger::console.info("switch zone");
	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<SceneObject*> par = sceneObject->getParent().get();

		if (par != nullptr && (par->isVehicleObject() || par->isMount())) {
			player->executeObjectControllerAction(STRING_HASHCODE("dismount"));
		}

		if (ghost != nullptr) {
			ghost->setSavedParentID(0);

			ghost->setTeleporting(true);
			ghost->setOnLoadScreen(true);
			ghost->updateLastValidatedPosition();
			ghost->setClientLastMovementStamp(0);

			ghost->unloadSpawnedChildren();
		}

		player->setMovementCounter(0);

		player->notifyObservers(ObserverEventType::ZONESWITCHED);
	}
	if (newTerrainName.contains("space"))
		SpaceZoneComponent::switchZone(sceneObject, newTerrainName, newPostionX, newPositionZ, newPositionY, parentID, toggleInvisibility);
}

void PlayerSpaceZoneComponent::teleport(SceneObject* sceneObject, float newPositionX, float newPositionZ, float newPositionY, uint64 parentID) const {
	CreatureObject* player = nullptr;

	if (sceneObject->isPlayerCreature()) {
		player = sceneObject->asCreatureObject();
	}

	ManagedReference<SceneObject*> par = sceneObject->getParent().get();

	if (player != nullptr && par != nullptr && parentID != 0) {

		if (par->isVehicleObject() || par->isMount()) {
			player->executeObjectControllerAction(STRING_HASHCODE("dismount"));
		}
	}

	if (sceneObject->getSpaceZone() != nullptr)
		SpaceZoneComponent::teleport(sceneObject, newPositionX, newPositionZ, newPositionY, parentID);

	if (player != nullptr) {
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			ghost->setTeleporting(true);
			ghost->updateLastValidatedPosition();
			ghost->setClientLastMovementStamp(0);
		}

		player->setMovementCounter(0);
	}
}

/**
 * Updates position of this object to the rest of in range objects
 * @pre { this object is locked}
 * @post { this object is locked, in range objects are updated with the new position }
 * @param lightUpdate if true a standalone message is sent to the in range objects
 */
void PlayerSpaceZoneComponent::updateZone(SceneObject* sceneObject, bool lightUpdate, bool sendPackets) const {
	if (sceneObject->getSpaceZone() != nullptr)
		SpaceZoneComponent::updateZone(sceneObject, lightUpdate, sendPackets);

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr)
			ghost->setSavedParentID(0);
	}
}

void PlayerSpaceZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	Logger::console.info("updateZoneWithParent", true);
	if (newParent->isSpaceZone())
		SpaceZoneComponent::updateZoneWithParent(sceneObject, newParent, lightUpdate, sendPackets);

	if (sceneObject->getParent() != nullptr && sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr)
			ghost->setSavedParentID(sceneObject->getParentID());
	}
}
