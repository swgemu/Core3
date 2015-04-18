/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RELOADCOMMAND_H_
#define RELOADCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ReloadCommand : public QueueCommand {
public:

	ReloadCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->sendStateCombatSpam("cbt_spam", "reload", 0);

		return SUCCESS;
	}

};

#endif //RELOADCOMMAND_H_
