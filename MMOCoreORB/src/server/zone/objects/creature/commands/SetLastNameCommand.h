/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETLASTNAMECOMMAND_H_
#define SETLASTNAMECOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

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

		StringTokenizer tokenizer(arguments.toString());
		String newLastName = arguments.toString();
		bool skipVerify = false;

		if (tokenizer.hasMoreTokens()) {
			String argument;
			tokenizer.getStringToken(argument);

			if (argument == "--force" || argument == "-f") {
				auto ghost = creature->getPlayerObject();

				if (ghost == nullptr || ghost->getAdminLevel() < 15) {
					creature->sendSystemMessage("Must be adminLevel >= 15 to use --force on setLastName.");
					return INVALIDPARAMETERS;
				}

				skipVerify = true;

				if (tokenizer.hasMoreTokens()) {
					tokenizer.getStringToken(newLastName);
				}
			} else {
				newLastName = argument;
			}
		}

		Locker clocker(targetObj, creature);

		Reference<CreatureObject*> targetCreature = targetObj.castTo<CreatureObject*>();

		String oldLastName = targetCreature->getLastName();

		String errmsg = targetCreature->setLastName(newLastName, skipVerify);

		if (!errmsg.isEmpty()) {
			creature->sendSystemMessage(errmsg);
			return INVALIDPARAMETERS;
		}

		creature->sendSystemMessage("Last name changed from '" + oldLastName + "' to '" + newLastName + "'");

		return SUCCESS;
	}
};

#endif //SETLASTNAMECOMMAND_H_
