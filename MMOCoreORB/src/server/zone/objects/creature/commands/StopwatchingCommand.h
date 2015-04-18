/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPWATCHINGCOMMAND_H_
#define STOPWATCHINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/managers/player/PlayerManager.h"

class StopwatchingCommand : public QueueCommand {
public:

	StopwatchingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isWatching())
			return GENERALERROR;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (playerManager != NULL)
			playerManager->stopWatch(creature, target);

		return SUCCESS;
	}

};

#endif //STOPWATCHINGCOMMAND_H_
