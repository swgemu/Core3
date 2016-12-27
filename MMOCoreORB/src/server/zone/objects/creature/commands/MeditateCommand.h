/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MEDITATECOMMAND_H_
#define MEDITATECOMMAND_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/events/MeditateTask.h"

class MeditateCommand : public QueueCommand {
public:

	MeditateCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature)) {
			creature->sendSystemMessage("@teraskasi:med_fail");
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (creature->isInCombat()) {
			creature->sendSystemMessage("@jedi_spam:not_while_in_combat");
			return GENERALERROR;
		}

		// Meditate
		CreatureObject* player = cast<CreatureObject*>(creature);

		Reference<Task*> task = player->getPendingTask("meditate");

		if (task != NULL) {
			player->sendSystemMessage("@jedi_spam:already_in_meditative_state");
			return GENERALERROR;
		}

		// Meditate Task
		Reference<MeditateTask*> meditateTask = new MeditateTask(player);
		meditateTask->setMoodString(player->getMoodString());
		player->sendSystemMessage("@teraskasi:med_begin");

		player->setMeditateState();

		player->addPendingTask("meditate", meditateTask, 3500);

		PlayerManager* playermgr = server->getZoneServer()->getPlayerManager();
		player->registerObserver(ObserverEventType::POSTURECHANGED, playermgr);

		return SUCCESS;

	}

};

#endif //MEDITATECOMMAND_H_
