/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETLASTNAMECOMMAND_H_
#define SETLASTNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetLastNameCommand : public QueueCommand {
public:

	SetLastNameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto zoneServer = server->getZoneServer();

		Reference<SceneObject*> targetObj = zoneServer->getObject(target);

		if(targetObj == nullptr || !targetObj->isPlayerCreature()) {
			creature->sendSystemMessage("Invalid target. This command only works on players");
			return INVALIDTARGET;
		}

		String newLastName = arguments.toString();

		Locker clocker(targetObj, creature);

		Reference<CreatureObject*> targetCreature = targetObj.castTo<CreatureObject*>();

		String oldLastName = targetCreature->getLastName();

		String errmsg = targetCreature->setLastName(newLastName);

		if (!errmsg.isEmpty()) {
			creature->sendSystemMessage(errmsg);
			return INVALIDPARAMETERS;
		}

		creature->sendSystemMessage("Last name changed from '" + oldLastName + "' to '" + newLastName + "'");

		return SUCCESS;
	}

};

#endif //SETLASTNAMECOMMAND_H_
