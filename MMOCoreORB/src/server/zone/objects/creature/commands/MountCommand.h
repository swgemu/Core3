/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOUNTCOMMAND_H_
#define MOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class MountCommand : public QueueCommand {
public:

	MountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (creature->isRidingMount()) {
			ZoneServer* zoneServer = server->getZoneServer();

			ManagedReference<ObjectController*> objectController = zoneServer->getObjectController();
			objectController->activateCommand(creature, STRING_HASHCODE("dismount"), 0, 0, "");

			return GENERALERROR;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		ManagedReference<SceneObject*> object = zoneServer->getObject(target);

		if (object == NULL)
			return INVALIDTARGET;

		if (!object->isVehicleObject() && !object->isMount())
			return GENERALERROR;

		CreatureObject* vehicle = cast<CreatureObject*>( object.get());

		if (vehicle->getCreatureLinkID() != creature->getObjectID())
			return GENERALERROR;

		if (!vehicle->isInRange(creature, 5))
			return GENERALERROR;

		if (creature->getParent() != NULL || vehicle->getParent() != NULL)
			return GENERALERROR;

		if (vehicle->isDestroyed()) {
			creature->sendSystemMessage("@pet/pet_menu:cant_mount_veh_disabled");
			return GENERALERROR;
		}

		if (!creature->checkCooldownRecovery("mount_dismount")) {
			return GENERALERROR;
		}

		try {
			Locker clocker(vehicle, creature);

			vehicle->setState(CreatureState::MOUNTEDCREATURE);

			if (!vehicle->transferObject(creature, 4, true))
				vehicle->error("could not add creature");

			uint32 crc = STRING_HASHCODE("gallop");
			if (creature->hasBuff(crc) && vehicle->hasBuff(crc)) {
				//Clear the active negation of the gallop buff.
				creature->setSpeedMultiplierMod(1.f);
				creature->setAccelerationMultiplierMod(1.f);
				vehicle->setSpeedMultiplierMod(1.f);
				vehicle->setAccelerationMultiplierMod(1.f);
			}

			if (creature->hasBuff(STRING_HASHCODE("burstrun"))
					|| creature->hasBuff(STRING_HASHCODE("retreat"))) {
				//Negate effect of the active burst run or retreat buff. The negation will be cleared automatically when the buff is deactivated.
				creature->setSpeedMultiplierMod(1.f / 1.822f);
				creature->setAccelerationMultiplierMod(1.f / 1.822f);
			}

			creature->setState(CreatureState::RIDINGMOUNT);
			creature->clearState(CreatureState::SWIMMING);

			SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
			int bufferSize = changeBuffer->size();

			if (bufferSize > 5) {
				changeBuffer->remove(0);
			}

			float newSpeed = vehicle->getRunSpeed();

			if (vehicle->isMount()) {
				PetManager* petManager = server->getZoneServer()->getPetManager();

				if (petManager != NULL) {
					newSpeed = petManager->getMountedRunSpeed(vehicle);
				}
			}

			changeBuffer->add(SpeedModChange(newSpeed / creature->getRunSpeed()));

			creature->updateToDatabase();

			creature->setRunSpeed(newSpeed);
			creature->addMountedCombatSlow();

		} catch (Exception& e) {

		}

		creature->updateCooldownTimer("mount_dismount", 2000);

		return SUCCESS;
	}

};

#endif //MOUNTCOMMAND_H_
