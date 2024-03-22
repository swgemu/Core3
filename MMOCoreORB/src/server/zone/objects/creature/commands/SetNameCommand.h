/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETNAMECOMMAND_H_
#define SETNAMECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetNameCommand : public QueueCommand {
public:
	SetNameCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		StringTokenizer args(arguments.toString());

		if (!args.hasMoreTokens()) {
			return INVALIDPARAMETERS;
		}

		uint64 targetID = target;

		if (targetID == 0) {
			targetID = args.getLongToken();
		}

		Reference<SceneObject*> targetObj = zoneServer->getObject(targetID);

		if (targetObj == nullptr) {
			creature->sendSystemMessage("Invalid Target. Syntax: \"/setName objectID New Name String here\" or Target the intended object \"/setName New Name String Here\".");
			return INVALIDTARGET;
		}

		if (targetObj->isPlayerCreature()) {
			creature->sendSystemMessage("Player Names cannot be changed with this command. Use \"/setFirstName\" and \"/setLastName\" commands.");
			return INVALIDTARGET;
		}

		auto ghost = creature->getPlayerObject();

		bool bypassFilter = (ghost != nullptr && ghost->isPrivileged());

		Locker clocker(targetObj, creature);

		String newName = args.getRemainingString();

		if (newName.isEmpty()) {
			creature->sendSystemMessage("You must specify a new name.");
			return GENERALERROR;
		}

		NameManager* nameManager = server->getNameManager();

		if (!bypassFilter && nameManager != nullptr && nameManager->validateName(newName, -1) != NameManagerResult::ACCEPTED) {
			creature->sendSystemMessage("That name was rejected by the name filter.");
			return GENERALERROR;
		}

		String oldName = targetObj->getDisplayedName();

		targetObj->setCustomObjectName(newName, true);

		creature->sendSystemMessage("Name changed from '" + oldName + "' to '" + newName + "'");

		return SUCCESS;
	}
};

#endif // SETNAMECOMMAND_H_
