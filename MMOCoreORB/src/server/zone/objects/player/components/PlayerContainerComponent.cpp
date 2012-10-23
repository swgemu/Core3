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
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/packets/creature/CreatureObjectMessage6.h"
#include "server/zone/managers/visibility/VisibilityManager.h"

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

	if (object->isWeaponObject() && containmentType == 4) {
		ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>( object);
		int bladeColor = weapon->getBladeColor();

		if (weapon->isJediWeapon() && bladeColor == 31){
			errorDescription = "@jedi_spam:lightsaber_no_color";

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
	}

	if (object->isWearableObject()) {
		WearableObject* clothing = cast<WearableObject*>( object);
		clothing->setAttachmentMods(creo);
	}

	PlayerObject* ghost = creo->getPlayerObject();

	if (ghost && ghost->isJedi()) {
		if ((object->isRobeObject() && cast<RobeObject*>( object)->getSkillRequired() != "") || (object->isWeaponObject() && cast<WeaponObject*>(object)->isJediWeapon()))
			VisibilityManager::instance()->increaseVisibility(creo);
	}

	if (object->isInstrument() && creo->isEntertaining())
		creo->stopEntertaining();

	//this it to update the equipment list
	//we need a DeltaVector with all the slotted objects it seems
	/*CreatureObjectMessage6* msg6 = new CreatureObjectMessage6(creo);
	creo->broadcastMessage(msg6, true, true);*/

	if (object->isTangibleObject() && object->getArrangementDescriptorSize() != 0) {
		String arrangement = object->getArrangementDescriptor(0);

		if (arrangement != "mission_bag" && arrangement != "ghost" && arrangement != "bank") {
			creo->addWearableObject(cast<TangibleObject*>(object), true);
		}
	}

	if (creo != NULL && object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);
		tano->addTemplateSkillMods(creo);
	}

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
	}

	if (object->isWearableObject()) {
		WearableObject* clothing = cast<WearableObject*>( object);
		clothing->setAttachmentMods(creo, true);
	}

	if (object->isInstrument()) {
		if (creo->isPlayingMusic())
			creo->stopEntertaining();
	}

	if (creo->getPlayerObject()->isJedi())
	{
		if ((object->isRobeObject() && cast<RobeObject*>( object)->getSkillRequired() != "") || (object->isWeaponObject() && cast<WeaponObject*>(object)->isJediWeapon()))
			VisibilityManager::instance()->increaseVisibility(creo);
	}

	//this it to update the equipment list
	//we need a DeltaVector with all the slotted objects it seems
	/*CreatureObjectMessage6* msg6 = new CreatureObjectMessage6(creo);
	creo->broadcastMessage(msg6, true, true);*/

	if (object->isTangibleObject() && object->getArrangementDescriptorSize() != 0) {
		String arrangement = object->getArrangementDescriptor(0);

		if (arrangement != "mission_bag" && arrangement != "ghost" && arrangement != "bank") {
			creo->removeWearableObject(cast<TangibleObject*>(object), true);
		}
	}

	if (creo != NULL && object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object);
		tano->removeTemplateSkillMods(creo);
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
