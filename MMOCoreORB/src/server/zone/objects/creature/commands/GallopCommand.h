/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALLOPCOMMAND_H_
#define GALLOPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/buffs/GallopBuff.h"
#include "server/zone/objects/creature/events/GallopNotifyAvailableEvent.h"

class GallopCommand : public QueueCommand {
public:

	GallopCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> parent = creature->getParent().get();

		if (parent == NULL || !parent->isMount()) {
			creature->sendSystemMessage("@combat_effects:not_mounted"); // You cannot perform this command without a mount.
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> mount = cast<CreatureObject*>(parent.get());
		if (mount == NULL)
			return GENERALERROR;

		Locker crossLocker(mount, creature);

		uint32 crc = String("gallop").hashCode();

		if (mount->hasBuff(crc) || creature->hasBuff(crc)) {
			return GENERALERROR;
		}

		if (!creature->checkCooldownRecovery("gallop")) {
			creature->sendSystemMessage("@combat_effects:mount_tired"); // Your mount is too tired to gallop.
			return GENERALERROR;
		}

		if (creature->hasBuff(String("burstrun").hashCode())) {
			creature->sendSystemMessage("You cannot gallop while burst run is active.");
			return GENERALERROR;
		}

		PetManager* petManager = server->getZoneServer()->getPetManager();
		ManagedReference<PetControlDevice*> pcd = mount->getControlDevice().get().castTo<PetControlDevice*>();
		if (petManager == NULL || pcd == NULL)
			return GENERALERROR;

		SharedObjectTemplate* objectTemplate = pcd->getObjectTemplate();
		if (objectTemplate == NULL)
			return GENERALERROR;

		MountSpeedData* mountSpeedData = petManager->getMountSpeedData(objectTemplate->getAppearanceFilename());
		if (mountSpeedData == NULL)
			return GENERALERROR;

		int duration = mountSpeedData->getGallopDuration();
		float magnitude = mountSpeedData->getGallopSpeedMultiplier();
		int cooldown = mountSpeedData->getGallopCooldown();

		if (creature->getPlayerObject()->isPrivileged())
			cooldown = 5;

		StringIdChatParameter startStringId("combat_effects", "gallop_start"); // Your mount runs as fast as it can.
		StringIdChatParameter endStringId("combat_effects", "gallop_stop"); // Your mount is winded and slows down.

		ManagedReference<GallopBuff*> buff = new GallopBuff(mount, crc, duration);
		buff->setSpeedMultiplierMod(magnitude);
		buff->setAccelerationMultiplierMod(magnitude);

		mount->addBuff(buff);

		ManagedReference<GallopBuff*> buff2 = new GallopBuff(creature, crc, duration);
		buff2->setSpeedMultiplierMod(magnitude);
		buff2->setAccelerationMultiplierMod(magnitude);
		buff2->setStartMessage(startStringId);
		buff2->setEndMessage(endStringId);

		creature->addBuff(buff2);

		creature->updateCooldownTimer("gallop", (cooldown + duration) * 1000);

		Reference<GallopNotifyAvailableEvent*> task = new GallopNotifyAvailableEvent(creature);
		creature->addPendingTask("gallop_notify", task, (cooldown + duration) * 1000);

		return SUCCESS;
	}

};

#endif //GALLOPCOMMAND_H_
