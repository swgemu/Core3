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
#include "server/zone/SpaceZone.h"
#include "server/zone/TreeEntry.h"

void PlayerSpaceZoneComponent::notifyInsertToZone(SceneObject* sceneObject, SpaceZone* newSpaceZone) const {
	String zoneName = newSpaceZone->getZoneName();

	if (sceneObject->isPlayerCreature() && newSpaceZone != nullptr) {
		CreatureObject* player = sceneObject->asCreatureObject();

		if (player != nullptr) {
			PlayerObject* ghost = player->getPlayerObject();

			if (ghost != nullptr) {
				ghost->setSavedTerrainName(zoneName);
			}
		}
	}

	SpaceZoneComponent::notifyInsertToZone(sceneObject, newSpaceZone);
}

void PlayerSpaceZoneComponent::notifyInsert(SceneObject* sceneObject, TreeEntry* entry) const {
	SceneObject* scno = static_cast<SceneObject*>(entry);

	if (scno == sceneObject)
		return;

	// info(true) << "PlayerSpaceZoneComponent::notifyInsert -- " << scno->getDisplayedName();

	if (scno->isTangibleObject()) {
		TangibleObject* tano = scno->asTangibleObject();

		if (tano->isInvisible())
			return;
	}

	ManagedReference<SceneObject*> parent = scno->getParent().get();

	if (parent != nullptr) {
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

void PlayerSpaceZoneComponent::switchZone(SceneObject* sceneObject, const String& newTerrainName, float newPostionX, float newPositionZ, float newPositionY, uint64 parentID, bool toggleInvisibility, int playerArrangement) const {
	// info(true) << "PlayerSpaceZoneComponent::switchZone called for: " << sceneObject->getDisplayedName();

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

			ghost->unloadSpawnedChildren(true);
		}

		player->notifyObservers(ObserverEventType::ZONESWITCHED, nullptr, newTerrainName.hashCode());
	}

	SpaceZoneComponent::switchZone(sceneObject, newTerrainName, newPostionX, newPositionZ, newPositionY, parentID, toggleInvisibility, playerArrangement);
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
	SpaceZoneComponent::updateZone(sceneObject, lightUpdate, sendPackets);

	if (sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();

		if (player != nullptr) {
			PlayerObject* ghost = player->getPlayerObject();

			if (ghost != nullptr)
				ghost->setSavedParentID(0);
		}
	}
}

void PlayerSpaceZoneComponent::updateZoneWithParent(SceneObject* sceneObject, SceneObject* newParent, bool lightUpdate, bool sendPackets) const {
	SpaceZoneComponent::updateZoneWithParent(sceneObject, newParent, lightUpdate, sendPackets);

	if (sceneObject->getParent() != nullptr && sceneObject->isPlayerCreature()) {
		CreatureObject* player = sceneObject->asCreatureObject();

		if (player != nullptr) {
			PlayerObject* ghost = player->getPlayerObject();

			if (ghost != nullptr)
				ghost->setSavedParentID(sceneObject->getParentID());
		}
	}
}
