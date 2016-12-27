/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MEDICALFORAGECOMMAND_H_
#define MEDICALFORAGECOMMAND_H_

#include "server/zone/managers/minigames/ForageManager.h"

class MedicalForageCommand : public QueueCommand {
public:

	MedicalForageCommand(const String& name, ZoneProcessServer* server)
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
			forageManager->startForaging(player, ForageManager::MEDICAL);
		}

		return SUCCESS;

	}

};

#endif //MEDICALFORAGECOMMAND_H_
