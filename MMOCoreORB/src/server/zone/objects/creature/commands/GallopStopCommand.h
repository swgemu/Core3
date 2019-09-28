/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALLOPSTOPCOMMAND_H_
#define GALLOPSTOPCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GallopStopCommand : public QueueCommand {
public:

	GallopStopCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> parent = creature->getParent().get();

		if (parent == nullptr || !parent->isMount()) {
			creature->sendSystemMessage("@combat_effects:cant_stop_gallop_not_mounted"); // You can't stop galloping if you aren't mounted.
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> mount = cast<CreatureObject*>(parent.get());
		if (mount == nullptr)
			return GENERALERROR;

		Locker crossLocker(mount, creature);

		uint32 crc = STRING_HASHCODE("gallop");

		if (!mount->hasBuff(crc)) {
			creature->sendSystemMessage("@combat_effects:cant_stop_galloping_not_galloping"); // You can't stop galloping if you aren't already galloping.
			return GENERALERROR;
		}

		PetManager* petManager = server->getZoneServer()->getPetManager();
		ManagedReference<PetControlDevice*> pcd = mount->getControlDevice().get().castTo<PetControlDevice*>();
		if (petManager == nullptr || pcd == nullptr)
			return GENERALERROR;

		SharedObjectTemplate* objectTemplate = pcd->getObjectTemplate();
		if (objectTemplate == nullptr)
			return GENERALERROR;

		MountSpeedData* mountSpeedData = petManager->getMountSpeedData(objectTemplate->getAppearanceFilename());
		if (mountSpeedData == nullptr)
			return GENERALERROR;

		int cooldown = mountSpeedData->getGallopCooldown();

		creature->removeBuff(crc);
		mount->removeBuff(crc);
		creature->getCooldownTimerMap()->updateToCurrentAndAddMili("gallop", cooldown * 1000);
		creature->removePendingTask("gallop_notify");

		Reference<GallopNotifyAvailableEvent*> task = new GallopNotifyAvailableEvent(creature);
		creature->addPendingTask("gallop_notify", task, cooldown * 1000);

		return SUCCESS;
	}

};

#endif //GALLOPSTOPCOMMAND_H_
