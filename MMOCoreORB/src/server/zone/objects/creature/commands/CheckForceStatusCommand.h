/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHECKFORCESTATUSCOMMAND_H_
#define CHECKFORCESTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/jedi/JediManager.h"

class CheckForceStatusCommand : public QueueCommand {
public:

	CheckForceStatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		JediManager::instance()->checkForceStatusCommand(creature);

		return SUCCESS;
	}

};

#endif //CHECKFORCESTATUSCOMMAND_H_
