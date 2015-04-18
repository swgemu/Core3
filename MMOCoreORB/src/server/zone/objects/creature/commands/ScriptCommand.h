/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCRIPTCOMMAND_H_
#define SCRIPTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/loot/LootkitObject.h"
#include "server/zone/managers/loot/LootManager.h"

class ScriptCommand : public QueueCommand {
public:

	ScriptCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //SCRIPTCOMMAND_H_
