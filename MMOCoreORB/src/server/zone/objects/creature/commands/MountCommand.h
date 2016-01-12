/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOUNTCOMMAND_H_
#define MOUNTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

class MountCommand : public QueueCommand {
	Vector<uint32> restrictedBuffCRCs;
public:

	MountCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		restrictedBuffCRCs.add(STRING_HASHCODE("gallop"));
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

		if (vehicle->isDestroyed()) {
			creature->sendSystemMessage("@pet/pet_menu:cant_mount_veh_disabled");
			return GENERALERROR;
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

		uint32 buffCRC = 0;
		for(int i=0; i<restrictedBuffCRCs.size(); i++) {
			buffCRC = restrictedBuffCRCs.get(i);
			if(creature->hasBuff(buffCRC)) {
				ManagedReference<Buff*> buff = creature->getBuff(buffCRC);

				Locker lock(buff, creature); // Is this necessary?

				buff->removeAllModifiers();
			}
		}

		SpeedMultiplierModChanges* changeBuffer = creature->getSpeedMultiplierModChanges();
		const int bufferSize = changeBuffer->size();

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


		return SUCCESS;
	}

};

#endif //MOUNTCOMMAND_H_
