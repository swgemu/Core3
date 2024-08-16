/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEFUSEMINEFIELDCOMMAND_H_
#define DEFUSEMINEFIELDCOMMAND_H_

#include "server/zone/managers/gcw/tasks/DefuseMineTask.h"

class DefuseMinefieldCommand : public QueueCommand {
public:
	DefuseMinefieldCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectToDefuse = zoneServer->getObject(target);

		if (objectToDefuse == nullptr || (!objectToDefuse->isMinefield() && !objectToDefuse->isTurret())) {
			return GENERALERROR;
		}

		// Player has to be master ranger??
		if (!creature->hasSkill("outdoors_ranger_master")) {
			return GENERALERROR;
		}

		Locker clock(objectToDefuse, creature);

		if (!objectToDefuse->isInRange(creature, 5.f)) {
			return TOOFAR;
		}

		if (objectToDefuse->getContainerObjectsSize() < 1) {
			return GENERALERROR;
		}

		auto minefield = objectToDefuse->asTangibleObject();

		if (minefield == nullptr) {
			return GENERALERROR;
		}

		// info(true) << "Defuse Minefield command called by - " << creature->getDisplayedName() << " for target: " << objectToDefuse->getDisplayedName();

		ManagedReference<WeaponObject*> weapon = objectToDefuse->getContainerObject(0).castTo<WeaponObject*>();

		if (weapon == nullptr) {
			return GENERALERROR;
		}

		creature->sendSystemMessage("You sucessfully locate a mine. Defusing...");

		auto defuseTask = new DefuseMineTask(creature, weapon, minefield);

		if (defuseTask == nullptr) {
			return GENERALERROR;
		}

		// Set the creature posture kneeling
		creature->setPosture(CreaturePosture::CROUCHED, true, true);

		defuseTask->schedule(5000);

		return SUCCESS;
	}
};

#endif // DEFUSEMINEFIELDCOMMAND_H_
