/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETFIRSTNAMECOMMAND_H_
#define SETFIRSTNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetFirstNameCommand : public QueueCommand {
public:

	SetFirstNameCommand(const String& name, ZoneProcessServer* server)
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

		String newFirstName = arguments.toString();

		if (newFirstName.isEmpty()) {
			creature->sendSystemMessage("Usage: /setfirstname {NewFirstName}");
			return INVALIDPARAMETERS;
		}

		Locker clocker(targetObj, creature);

		Reference<CreatureObject*> targetCreature = targetObj.castTo<CreatureObject*>();

		String oldFirstName = targetCreature->getFirstName();

		String errmsg = targetCreature->setFirstName(newFirstName);

		if (!errmsg.isEmpty()) {
			creature->sendSystemMessage(errmsg);
			return INVALIDPARAMETERS;
		}

		creature->sendSystemMessage("First name changed from '" + oldFirstName + "' to '" + newFirstName + "'");

		return SUCCESS;
	}
};

#endif // SETFIRSTNAMECOMMAND_H_
