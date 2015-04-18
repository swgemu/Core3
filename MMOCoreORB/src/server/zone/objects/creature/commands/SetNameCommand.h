/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETNAMECOMMAND_H_
#define SETNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetNameCommand : public QueueCommand {
public:

	SetNameCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		Reference<SceneObject*> targetObj = zoneServer->getObject(target);

		if(targetObj == NULL) {
			creature->sendSystemMessage("Invalid Target.");
			return INVALIDTARGET;
		}

		if (targetObj->isPlayerCreature()) {
			creature->sendSystemMessage("Player Names cannot be changed with this command. Use setFirstName and/or setLastName");
			return INVALIDTARGET;
		}

		Locker clocker(targetObj, creature);

		String newName = arguments.toString();

		if (newName.isEmpty()) {
			creature->sendSystemMessage("You must specify a new name.");
			return GENERALERROR;
		}

		NameManager* nameManager = server->getNameManager();

		if (nameManager->validateName(newName, -1) != NameManagerResult::ACCEPTED) {
			creature->sendSystemMessage("That name was rejected by the name filter.");
			return GENERALERROR;
		}

		String oldName = targetObj->getDisplayedName();

		targetObj->setCustomObjectName(newName, true);

		creature->sendSystemMessage("Name changed from '" + oldName + "' to '" + newName + "'");

		return SUCCESS;
	}

};

#endif //SETNAMECOMMAND_H_
