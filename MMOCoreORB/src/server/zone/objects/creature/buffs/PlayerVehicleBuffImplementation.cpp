#include <stddef.h>
#include <algorithm>

#include "engine/core/Core.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/core/TaskManager.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/SpeedMultiplierModChanges.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/PlayerVehicleBuff.h"
#include "system/lang/ref/Reference.h"
#include "system/thread/Locker.h"



void PlayerVehicleBuffImplementation::applyAllModifiers() {

	if (!modsApplied) {
		applyAttributeModifiers();
		applySkillModifiers();
		applyStates();
		modsApplied = true;

		updateRiderSpeeds();
	}
}

void PlayerVehicleBuffImplementation::removeAllModifiers() {

	if (modsApplied) {
		removeAttributeModifiers();
		removeSkillModifiers();
		removeStates();
		modsApplied = false;

		updateRiderSpeeds();
	}
}

void PlayerVehicleBuffImplementation::activate(bool applyModifiers) {
		BuffImplementation::activate(applyModifiers);
		//Send start message to mount rider
		if (!startMessage.isEmpty()) {

			ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();

			if(rider != NULL) {
				rider->sendSystemMessage(startMessage);
			}
		}

}

void PlayerVehicleBuffImplementation::deactivate(bool removeModifiers) {
		BuffImplementation::deactivate(removeModifiers);
		//Send end message to mount rider
		if (!endMessage.isEmpty()) {

			ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();

			if(rider != NULL) {
				rider->sendSystemMessage(endMessage);
			}
		}

}

void PlayerVehicleBuffImplementation::updateRiderSpeeds() {

	ManagedReference<CreatureObject*> vehicle = creature.get();
	ManagedReference<CreatureObject*> rider = vehicle->getSlottedObject("rider").castTo<CreatureObject*>();

	if (rider == NULL) // Our rider is gone
		return;

	Core::getTaskManager()->executeTask([=] () {
		Locker riderLock(rider);
		Locker crossLock(vehicle, rider);

		if (!rider->isRidingMount()) // dismount will reset the player's speed for us, do nothing
			return;

		// Speed hack buffer
		SpeedMultiplierModChanges* changeBuffer = rider->getSpeedMultiplierModChanges();
		const int bufferSize = changeBuffer->size();

		// Drop old change off the buffer
		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		// get vehicle speed
		float newSpeed = vehicle->getRunSpeed();

		// get animal mount speeds
		if (vehicle->isMount()) {
			PetManager* petManager = vehicle->getZoneServer()->getPetManager();

			if (petManager != NULL) {
				newSpeed = petManager->getMountedRunSpeed(vehicle);
			}
		}

		// add speed multiplier mod
		newSpeed *= vehicle->getSpeedMultiplierMod();

		// Add a fake "skillmod" change
		changeBuffer->add(SpeedModChange(newSpeed / rider->getRunSpeed()));

		// Commit changebuffer ?
		rider->updateToDatabase();

		// Update riders speed to match mount speed
		rider->setRunSpeed(newSpeed);
	}, "UpdateRiderSpeedsLambda");
}
