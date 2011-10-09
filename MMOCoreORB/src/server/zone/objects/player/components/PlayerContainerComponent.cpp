/*
 * PlayerContainerComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerContainerComponent.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

int PlayerContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->isTangibleObject() && containmentType == 4) {
		TangibleObject* wearable = cast<TangibleObject*>( object);

		uint16 charMask = creo->getWearableMask();
		uint16 objMask = wearable->getPlayerUseMask();

		uint16 maskRes = ~objMask & charMask;

		if (maskRes != 0) {
			/*StringBuffer maskResol;
						maskResol << "returned maskRes :" << maskRes;
						info(maskResol.toString(), true);*/
			errorDescription = "You lack the necessary requirements to wear this object";

			return TransferErrorCode::PLAYERUSEMASKERROR;
		}
	}

	if (object->isArmorObject() && containmentType == 4) {
		PlayerManager* playerManager = sceneObject->getZoneServer()->getPlayerManager();

		if (!playerManager->checkEncumbrancies(dynamic_cast<CreatureObject*>(sceneObject), cast<ArmorObject*>( object))) {
			errorDescription = "You lack the necessary secondary stats to equip this item";

			return TransferErrorCode::NOTENOUGHENCUMBRANCE;
		}
	}

	return ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int PlayerContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->isArmorObject()) {
		PlayerManager* playerManager = sceneObject->getZoneServer()->getPlayerManager();

		playerManager->applyEncumbrancies(creo, cast<ArmorObject*>(object));

		WearableObject* armor = cast<WearableObject*>( object);
		armor->setAttachmentMods(creo);

	} else if (object->isWearableObject()) {
		WearableObject* clothing = cast<WearableObject*>( object);
		clothing->setAttachmentMods(creo);
	}

	if (object->isInstrument() && creo->isEntertaining())
		creo->stopEntertaining();

	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int PlayerContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->isArmorObject()) {
		PlayerManager* playerManager = creo->getZoneServer()->getPlayerManager();

		playerManager->removeEncumbrancies(creo, cast<ArmorObject*>(object));

		WearableObject* armor = cast<WearableObject*>( object);
		armor->setAttachmentMods(creo, true);

	} else if (object->isWearableObject()) {
		WearableObject* clothing = cast<WearableObject*>( object);
		clothing->setAttachmentMods(creo, true);
	}

	if (object->isInstrument()) {
		if (creo->isPlayingMusic())
			creo->stopEntertaining();
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object);
}
