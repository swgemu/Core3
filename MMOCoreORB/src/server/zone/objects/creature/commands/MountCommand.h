/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOUNTCOMMAND_H_
#define MOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class MountCommand : public QueueCommand {
	Vector<uint32> restrictedBuffCRCs;
	uint32 gallopCRC;
public:

	MountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		gallopCRC = STRING_HASHCODE("gallop");

		restrictedBuffCRCs.add(STRING_HASHCODE("burstrun"));
		restrictedBuffCRCs.add(STRING_HASHCODE("retreat"));
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_1);
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_2);
		restrictedBuffCRCs.add(BuffCRC::JEDI_FORCE_RUN_3);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == NULL || !creature->checkCooldownRecovery("mount_dismount"))
			return GENERALERROR;

		if (creature->isRidingMount()) {
			ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();
			objectController->activateCommand(creature, STRING_HASHCODE("dismount"), 0, 0, "");

			return GENERALERROR;
		}

		if (target == 0)
			return GENERALERROR;

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == NULL) {
			return INVALIDTARGET;
		}

		if (!object->isVehicleObject() && !object->isMount())
			return INVALIDTARGET;

		CreatureObject* vehicle = cast<CreatureObject*>( object.get());

		Locker clocker(vehicle, creature);

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (vehicle->getCreatureLinkID() != creature->getObjectID())
			return GENERALERROR;

		if (!vehicle->isInRange(creature, 5))
			return GENERALERROR;

		if (creature->getParent() != NULL || vehicle->getParent() != NULL)
			return GENERALERROR;

		if (vehicle->isDisabled()) {
			creature->sendSystemMessage("@pet/pet_menu:cant_mount_veh_disabled");
			return GENERALERROR;
		}

		if (vehicle->isIncapacitated())
			return GENERALERROR;

		if (vehicle->isDead())
			return GENERALERROR;

		if (vehicle->getPosture() == CreaturePosture::LYINGDOWN || vehicle->getPosture() == CreaturePosture::SITTING) {
			vehicle->setPosture(CreaturePosture::UPRIGHT);
		}

		vehicle->setState(CreatureState::MOUNTEDCREATURE);

		if (!vehicle->transferObject(creature, 4, true)) {
			vehicle->error("could not add creature");
			vehicle->clearState(CreatureState::MOUNTEDCREATURE);

			return GENERALERROR;
		}
		creature->setState(CreatureState::RIDINGMOUNT);
		creature->clearState(CreatureState::SWIMMING);

		creature->updateCooldownTimer("mount_dismount", 2000);

		//We need to crosslock buff and creature below
		clocker.release();

		for(int i=0; i<restrictedBuffCRCs.size(); i++) {

			uint32 buffCRC = restrictedBuffCRCs.get(i);

			if(creature->hasBuff(buffCRC)) {
				ManagedReference<Buff*> buff = creature->getBuff(buffCRC);

				Locker lock(buff, creature);

				buff->removeAllModifiers();
			}
		}

		if(creature->hasBuff(gallopCRC)) {
			creature->removeBuff(gallopCRC); // This should "fix" any players that have the old gallop buff
		}

		//We released this crosslock before to remove player buffs
		Locker vehicleLocker(vehicle, creature);

		if (vehicle->hasBuff(gallopCRC)) {
			Core::getTaskManager()->executeTask([=] () {
				uint32 gallopCRC = STRING_HASHCODE("gallop");
				Locker lock(vehicle);

				ManagedReference<Buff*> gallop = vehicle->getBuff(gallopCRC);
				Locker blocker(gallop, vehicle);

				if (gallop != NULL) {
					gallop->applyAllModifiers();
				}
			}, "AddGallopModsLambda");
		}

		// Speed hack buffer
		SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
		const int bufferSize = changeBuffer->size();

		// Drop old change off the buffer
		if (bufferSize > 5) {
			changeBuffer->remove(0);
		}

		// get vehicle speed
		float newSpeed = vehicle->getRunSpeed();
		float newAccel = vehicle->getAccelerationMultiplierMod();
		float newTurn = vehicle->getTurnScale();

		// get animal mount speeds
		if (vehicle->isMount()) {
			PetManager* petManager = server->getZoneServer()->getPetManager();

			if (petManager != NULL) {
				newSpeed = petManager->getMountedRunSpeed(vehicle);
			}
		}

		// add speed multiplier mod for existing buffs
		if(vehicle->getSpeedMultiplierMod() != 0)
			newSpeed *= vehicle->getSpeedMultiplierMod();

		// Add our change to the buffer history
		changeBuffer->add(SpeedModChange(newSpeed / creature->getRunSpeed()));

		creature->updateToDatabase();

		// Force Sensitive SkillMods
		if (vehicle->isVehicleObject()) {
			newAccel += creature->getSkillMod("force_vehicle_speed");
			newTurn += creature->getSkillMod("force_vehicle_control");
		}

		creature->setRunSpeed(newSpeed);
		creature->setTurnScale(newTurn, true);
		creature->setAccelerationMultiplierMod(newAccel, true);
		creature->addMountedCombatSlow();

		return SUCCESS;
	}

};

#endif //MOUNTCOMMAND_H_
