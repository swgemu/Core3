/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AIIGNORECOMMAND_H_
#define AIIGNORECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"


class AiIgnoreCommand : public QueueCommand {
public:

	AiIgnoreCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL || !ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		return SUCCESS;
	}

};

#endif //AIIGNORECOMMAND_H_
