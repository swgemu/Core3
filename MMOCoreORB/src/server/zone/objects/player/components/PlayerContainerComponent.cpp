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

	if (object->isWearableObject() && containmentType == 4) {
		ManagedReference<WearableObject*> wearable = cast<WearableObject*>( object);
		SharedTangibleObjectTemplate* wearableData = dynamic_cast<SharedTangibleObjectTemplate*>(wearable->getObjectTemplate());

		Vector<String> skillsRequired = wearableData->getCertificationsRequired();

		if (skillsRequired.size() > 0) {
			bool hasSkill = false;
			for (int i = 0; i < skillsRequired.size(); i++) {
				String skill = skillsRequired.get(i);
				if (!skill.isEmpty() && creo->hasSkill(skill)) {
					hasSkill = true;
					break;
				}
			}

			if (!hasSkill) {
				errorDescription = "@error_message:insufficient_skill"; // You lack the skill to use this item.

				return TransferErrorCode::PLAYERUSEMASKERROR;
			}
		}
	}

	if (object->isWeaponObject() && containmentType == 4) {
		ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>( object);
		int bladeColor = weapon->getBladeColor();

		if (weapon->isJediWeapon()){
			if (bladeColor == 31) {
				errorDescription = "@jedi_spam:lightsaber_no_color";
				return TransferErrorCode::PLAYERUSEMASKERROR;
			}
			if (weapon->getCraftersName() != creo->getFirstName()) {
				errorDescription = "@jedi_spam:not_your_lightsaber";
				return TransferErrorCode::PLAYERUSEMASKERROR;
			}
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

	if (object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);
		tano->applySkillModsTo(creo);
	}

	// Jedi stuff below.
	PlayerObject* ghost = creo->getPlayerObject();

	if (ghost && ghost->isJedi()) {
		if (object->isRobeObject()) {
			RobeObject* robeObject = cast<RobeObject*>(object);
			if (robeObject->getSkillRequired() != "") {
				ghost->setForcePowerMax(creo->getSkillMod("jedi_force_power_max"));
				VisibilityManager::instance()->increaseVisibility(creo);
				if (creo->getWeapon()->isJediWeapon()) {
					ghost->setForcePowerRegen(creo->getSkillMod("jedi_force_power_regen"));
				}
			}
		} else if (object->isWeaponObject()) {
			WeaponObject* weaponObject = cast<WeaponObject*>(object);
			if (weaponObject->isJediWeapon()) {
				SceneObject* item = creo->getSlottedObject("chest1");
				if (item != NULL && item->isRobeObject()) {
					RobeObject* robeObject = cast<RobeObject*>(item);
					if (robeObject->getSkillRequired() != "") {
						ghost->setForcePowerRegen(creo->getSkillMod("jedi_force_power_regen"));
					}
				}
				VisibilityManager::instance()->increaseVisibility(creo);
			}
		}
	}

	if (object->isInstrument() && creo->isEntertaining())
		creo->stopEntertaining();

	//this it to update the equipment list
	//we need a DeltaVector with all the slotted objects it seems
	/*CreatureObjectMessage6* msg6 = new CreatureObjectMessage6(creo);
	creo->broadcastMessage(msg6, true, true);*/

	if (object->isTangibleObject() && object->getArrangementDescriptorSize() != 0 && object->getArrangementDescriptor(0)->size() != 0) {
		const String& arrangement = object->getArrangementDescriptor(0)->get(0);

		if (arrangement != "mission_bag" && arrangement != "ghost" && arrangement != "bank") {
			creo->addWearableObject(object->asTangibleObject(), true);
		}
	}

	if (object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = object->asTangibleObject();
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

	if (object->isTangibleObject()) {
		TangibleObject* tano = cast<TangibleObject*>(object);
		tano->removeSkillModsFrom(creo);
	}

	if (object->isInstrument()) {
		if (creo->isPlayingMusic())
			creo->stopEntertaining();
	}

	// Jedi stuff below.
	PlayerObject* ghost = creo->getPlayerObject();

	if (ghost && ghost->isJedi()) {
		if (object->isRobeObject()) {
			RobeObject* robeObject = cast<RobeObject*>(object);
			if (robeObject->getSkillRequired() != "") {
				ghost->setForcePowerMax(creo->getSkillMod("jedi_force_power_max"));
				VisibilityManager::instance()->increaseVisibility(creo);
				if (creo->getWeapon()->isJediWeapon()) {
					ghost->setForcePowerRegen(creo->getSkillMod("jedi_force_power_regen"));
				}
			}
		} else if (object->isWeaponObject()) {
			WeaponObject* weaponObject = cast<WeaponObject*>(object);
			if (weaponObject->isJediWeapon()) {
				SceneObject* item = creo->getSlottedObject("chest1");
				if (item != NULL && item->isRobeObject()) {
					RobeObject* robeObject = cast<RobeObject*>(item);
					if (robeObject->getSkillRequired() != "") {
						ghost->setForcePowerRegen(creo->getSkillMod("jedi_force_power_regen") - robeObject->getTemplateSkillMods()->get("jedi_force_power_regen"));
					}
				}
				VisibilityManager::instance()->increaseVisibility(creo);
			}
		}
	}

	//this it to update the equipment list
	//we need a DeltaVector with all the slotted objects it seems
	/*CreatureObjectMessage6* msg6 = new CreatureObjectMessage6(creo);
	creo->broadcastMessage(msg6, true, true);*/

	if (object->isTangibleObject() && object->getArrangementDescriptorSize() != 0 && object->getArrangementDescriptor(0)->size() != 0) {
		const String& arrangement = object->getArrangementDescriptor(0)->get(0); //CHK

		if (arrangement != "mission_bag" && arrangement != "ghost" && arrangement != "bank") {
			creo->removeWearableObject(object->asTangibleObject(), true);
		}
	}

	if (object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = object->asTangibleObject();
		tano->removeTemplateSkillMods(creo);
	}

	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
