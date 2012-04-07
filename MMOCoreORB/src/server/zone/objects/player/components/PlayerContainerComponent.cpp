/*
 * PlayerContainerComponent.cpp
 *
 *  Created on: 26/05/2011
 *      Author: victor
 */

#include "PlayerContainerComponent.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/wearables/RobeObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"

int PlayerContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	CreatureObject* creo = dynamic_cast<CreatureObject*>(sceneObject);

	if (object->isTangibleObject() && containmentType == 4) {
		TangibleObject* wearable = cast<TangibleObject*>( object);

		SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(wearable->getObjectTemplate());
		Vector<uint32>* races = tanoData->getPlayerRaces();
		String race = creo->getObjectTemplate()->getFullTemplateString();

		if (!races->contains(race.hashCode())) {
			errorDescription = "You lack the necessary requirements to wear this object";

			return TransferErrorCode::PLAYERUSEMASKERROR;
		}

		if (creo->isPlayerCreature()) {
			if (!wearable->isNeutral()) {
				ManagedReference<PlayerObject*> playerObject = creo->getPlayerObject();

				if (wearable->isImperial() && (playerObject->getFactionStatus() == FactionStatus::ONLEAVE || !creo->isImperial())) {
					errorDescription = "You lack the necessary requirements to wear this object";

					return TransferErrorCode::PLAYERUSEMASKERROR;
				}

				if (wearable->isRebel() && (playerObject->getFactionStatus() == FactionStatus::ONLEAVE || !creo->isRebel())) {
					errorDescription = "You lack the necessary requirements to wear this object";

					return TransferErrorCode::PLAYERUSEMASKERROR;
				}
			}
		}
	}

	if (object->isArmorObject() && containmentType == 4) {
		PlayerManager* playerManager = sceneObject->getZoneServer()->getPlayerManager();

		if (!playerManager->checkEncumbrancies(dynamic_cast<CreatureObject*>(sceneObject), cast<ArmorObject*>( object))) {
			errorDescription = "You lack the necessary secondary stats to equip this item";

			return TransferErrorCode::NOTENOUGHENCUMBRANCE;
		}
	}

	if (object->isRobeObject() && containmentType == 4) {
		ManagedReference<RobeObject*> robe = cast<RobeObject*>( object);
		String skillRequired = robe->getSkillRequired();

		if (!creo->hasSkill(skillRequired) && skillRequired != ""){
			errorDescription = "You are not eligible to wear this robe.";

			return TransferErrorCode::PLAYERUSEMASKERROR;
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

	if (object->isRobeObject()) {
		PlayerObject* ghost = creo->getPlayerObject();
		if (ghost != NULL && ghost->getForcePowerMax() > 0){
				creo->addSkillMod("jedi_force_power_max", 250, true);
				creo->addSkillMod("jedi_force_power_regen", 10, true);
				ghost->setForcePowerMax(ghost->getForcePowerMax() + 250, true);
		}
	}

	if (object->isInstrument() && creo->isEntertaining())
		creo->stopEntertaining();

	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int PlayerContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
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


	if (object->isRobeObject()) {
		PlayerObject* ghost = creo->getPlayerObject();
		if (ghost != NULL && ghost->getForcePowerMax() > 0){
				creo->addSkillMod("jedi_force_power_max", -250, true);
				creo->addSkillMod("jedi_force_power_regen", -10, true);
				ghost->setForcePowerMax(ghost->getForcePowerMax() - 250, true);
		}
	}

	if (object->isInstrument()) {
		if (creo->isPlayingMusic())
			creo->stopEntertaining();
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
