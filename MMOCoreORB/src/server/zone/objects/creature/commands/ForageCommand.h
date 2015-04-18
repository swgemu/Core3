/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORAGECOMMAND_H_
#define FORAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/minigames/ForageManager.h"

class ForageCommand : public QueueCommand {
public:

	ForageCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (creature->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>(creature);
			ForageManager* forageManager = server->getForageManager();
			forageManager->startForaging(player, ForageManager::SCOUT);
		}

		return SUCCESS;

	}

};

#endif //FORAGECOMMAND_H_
