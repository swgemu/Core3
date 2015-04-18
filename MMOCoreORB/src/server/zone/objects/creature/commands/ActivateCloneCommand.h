/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ACTIVATECLONECOMMAND_H_
#define ACTIVATECLONECOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class ActivateCloneCommand : public QueueCommand {
public:

	ActivateCloneCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		if (!player->isDead())
			return GENERALERROR;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->sendActivateCloneRequest(player);

		return SUCCESS;
	}

};

#endif //ACTIVATECLONECOMMAND_H_
