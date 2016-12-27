/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FISHCOMMAND_H_
#define FISHCOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/minigames/FishingManager.h"

class FishCommand : public QueueCommand {
public:

	FishCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isPlayerCreature()) {
			ManagedReference<FishingManager*> manager = server->getFishingManager();

			CreatureObject* player = cast<CreatureObject*>(creature);

			// ENABLE FOR TESTING
			// manager->freeBait(player);
			// ENDENABLE

			if ((manager->getFishingState(player) != FishingManager::NOTFISHING) || (manager->isPlaying(player))) {
				player->sendSystemMessage("You are already fishing.");

				return GENERALERROR;
			}

			/*if (player->hasOpenContainer(bla)) {
				player->sendSystemMessage("You are already fishing.");

				return GENERALERROR;
			}*/

			manager->startFishing(player);

		}
		return SUCCESS;
	}

};

#endif //FISHCOMMAND_H_
