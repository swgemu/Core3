#include "engine/engine.h"

#include "server/zone/objects/creature/buffs/PlayerVehicleBuff.h"
#include "BuffDurationEvent.h"
#include "BuffList.h"

#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/Buffs.h"
#include "server/zone/packets/object/ShowFlyText.h"
#include "server/zone/managers/skill/SkillModManager.h"




void PlayerVehicleBuffImplementation::applyAllModifiers() {

	Locker locker(&mutex);

	if (!modsApplied) {
		applyRiderAttributeModifiers();
		applyRiderSkillModifiers();
		applyRiderStates();

		applyAttributeModifiers();
		applySkillModifiers();
		applyStates();
		modsApplied = true;
	}
}

void PlayerVehicleBuffImplementation::removeAllModifiers() {

	Locker locker(&mutex);
	if (modsApplied) {
		removeRiderAttributeModifiers();
		removeRiderSkillModifiers();
		removeRiderStates();

		removeAttributeModifiers();
		removeSkillModifiers();
		removeStates();
		modsApplied = false;
	}
}

void PlayerVehicleBuffImplementation::activate(bool applyModifiers) {
	ManagedReference<CreatureObject*> strongRef = creature.get().get();
	try {

		if(applyModifiers)
			applyAllModifiers();

		scheduleBuffEvent();

		if (creature.get()->isPlayerCreature())
			sendTo((cast<CreatureObject*>(creature.get().get())));

		//Send start message to mount rider
		if (!startMessage.isEmpty()) {
			ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
			if(rider != NULL) {
				rider->sendSystemMessage(startMessage);
			}
		}

		if (!startFlyFile.isEmpty())
			creature.get()->showFlyText(startFlyFile, startFlyAux, startFlyRed, startFlyGreen, startFlyBlue);

		if (!startSpam.isEmpty()) {
			creature.get()->sendStateCombatSpam(startSpam.getFile(), startSpam.getStringID(), spamColor, 0, broadcastSpam);
		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void PlayerVehicleBuffImplementation::deactivate(bool removeModifiers) {
	ManagedReference<CreatureObject*> strongRef = creature.get().get();

	if (strongRef == NULL)
		return;

	try {
		if(removeModifiers)
			removeAllModifiers();

		if (creature.get()->isPlayerCreature())
			sendDestroyTo(cast<CreatureObject*>(creature.get().get()));

		//Send end message to mount rider
		if (!endMessage.isEmpty()) {
			ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
			if(rider != NULL)
				rider->sendSystemMessage(endMessage);
		}

		if (!endFlyFile.isEmpty())
			creature.get()->showFlyText(endFlyFile, endFlyAux, endFlyRed, endFlyGreen, endFlyBlue);

		if (!endSpam.isEmpty()) {
			creature.get()->sendStateCombatSpam(endSpam.getFile(), endSpam.getStringID(), spamColor, 0, broadcastSpam);
		}

		clearBuffEvent();

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}
}

void PlayerVehicleBuffImplementation::applyRiderAttributeModifiers() {
	if (creature.get() == NULL) {
		return;
	}

	ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL) {
		return;
	}

	Locker locker(rider);

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		try {
			int currentMaxHAM = rider.get()->getMaxHAM(attribute);

			int newMaxHAM = currentMaxHAM + value;
			if (newMaxHAM < 1)
					newMaxHAM = 1;

			int buffAmount = newMaxHAM - currentMaxHAM;
			attributeModifiers.drop(attribute);
			attributeModifiers.put(attribute, buffAmount);

			rider.get()->setMaxHAM(attribute, newMaxHAM);

			if (rider.get()->getHAM(attribute) > newMaxHAM - rider.get()->getWounds(attribute))
				rider.get()->setHAM(attribute, newMaxHAM - rider.get()->getWounds(attribute));

			if (!rider.get()->isDead() && !rider.get()->isIncapacitated()) {
				if (fillAttributesOnBuff) {
					int attributeval = MAX(newMaxHAM, rider.get()->getHAM(attribute) + value);
					rider.get()->healDamage(rider.get(), attribute, attributeval, true);
				} else if (value >= 0)
					rider.get()->healDamage(rider.get(), attribute, value);
			}

		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}
	}

}

void PlayerVehicleBuffImplementation::applyRiderSkillModifiers() {
	if (creature.get() == NULL)
		return;

	ManagedReference<CreatureObject*> rider = creature.get().get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL) {
		return;
	}

	Locker locker(rider);

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		rider.get()->addSkillMod(SkillModManager::BUFF, key, value, true);
	}

	// if there was a speed or acceleration mod change, this will take care of immediately setting them.
	// the checks for if they haven't changed are in these methods
	rider.get()->updateSpeedAndAccelerationMods();
	rider.get()->updateTerrainNegotiation();
}

void PlayerVehicleBuffImplementation::applyRiderStates() {
	if (creature.get() == NULL)
		return;

	ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL)
		return;

	Locker locker(rider);

	int size = states.size();

	for (int i = 0; i < size; ++i) {

		rider.get()->setState(states.get(i), true);
	}
}

void PlayerVehicleBuffImplementation::removeRiderAttributeModifiers() {
	if (creature.get() == NULL)
		return;

	ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL) {
		return;
	}

	Locker locker(rider);

	int size = attributeModifiers.size();

	if (size <= 0)
		return;

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<uint8, int>* entry = &attributeModifiers.elementAt(i);

		uint8 attribute = entry->getKey();
		int value = entry->getValue();

		if (value == 0)
			continue;

		try {

			int attributemax = rider.get()->getMaxHAM(attribute) - value;

			int currentVal = rider.get()->getHAM(attribute);

			rider.get()->setMaxHAM(attribute, attributemax);

			if (currentVal >= attributemax) {
				//rider.get()->inflictDamage(rider.get(), attribute, currentVal - attributemax, isSpiceBuff());

				if (attribute % 3 == 0) {
					rider.get()->inflictDamage(rider.get(), attribute, currentVal - attributemax, false);
				} // else setMaxHam sets secondaries to max
			}

		} catch (Exception& e) {
			error(e.getMessage());
			e.printStackTrace();
		}


		/*int attributeval = MIN(attributemax, rider.get()->getHAM(attribute) - value);

		rider.get()->setHAM(attribute, attributeval);*/
	}

}

void PlayerVehicleBuffImplementation::removeRiderSkillModifiers() {
	if (creature.get() == NULL)
		return;

	ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL)
		return;
	Locker locker(rider);

	int size = skillModifiers.size();

	for (int i = 0; i < size; ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers.elementAt(i);

		String key = entry->getKey();
		int value = entry->getValue();

		rider.get()->addSkillMod(SkillModManager::BUFF, key, -value, true);

	}

	// if there was a speed or acceleration mod change, this will take care of immediately setting them.
	// the checks for if they haven't changed are in these methods
	rider.get()->updateSpeedAndAccelerationMods();
	rider.get()->updateTerrainNegotiation();
}

void PlayerVehicleBuffImplementation::removeRiderStates() {
	if (creature.get() == NULL)
		return;

	ManagedReference<CreatureObject*> rider = creature.get()->getSlottedObject("rider").castTo<CreatureObject*>();
	if(rider == NULL)
		return;

	Locker locker(rider);

	int size = states.size();

	for (int i = 0; i < size; ++i) {
		rider.get()->clearState(states.get(i), true);
	}
}

