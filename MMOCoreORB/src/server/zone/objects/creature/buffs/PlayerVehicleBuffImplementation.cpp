#include "engine/engine.h"

#include "server/zone/objects/creature/buffs/PlayerVehicleBuff.h"

#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/ZoneServer.h"



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

	if(rider == NULL) // Our rider is gone
		return;


	EXECUTE_TASK_2(vehicle, rider, {

		Locker riderLock(rider_p);
		Locker crossLock(vehicle_p, rider_p);

		if(!rider_p->isRidingMount()) // dismount will reset the player's speed for us, do nothing
			return;

		// Speed hack buffer
		SpeedMultiplierModChanges* changeBuffer = rider_p->getSpeedMultiplierModChanges();
		const int bufferSize = changeBuffer->size();

		// Drop old change off the buffer
		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		// get vehicle speed
		float newSpeed = vehicle_p->getRunSpeed();

		// get animal mount speeds
		if (vehicle_p->isMount()) {
			PetManager* petManager = vehicle_p->getZoneServer()->getPetManager();

			if (petManager != NULL) {
				newSpeed = petManager->getMountedRunSpeed(vehicle_p);
			}
		}

		// add speed multiplier mod
		newSpeed *= vehicle_p->getSpeedMultiplierMod();

		// Add a fake "skillmod" change
		changeBuffer->add(SpeedModChange(newSpeed / rider_p->getRunSpeed()));

		// Commit changebuffer ?
		rider_p->updateToDatabase();

		// Update riders speed to match mount speed
		rider_p->setRunSpeed(newSpeed);
	});
}

