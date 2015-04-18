/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STANDCOMMAND_H_
#define STANDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"

class StandCommand : public QueueCommand {
public:

	StandCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//StringTokenizer args(arguments.toString());

		if (!creature->checkDizzyDelay() && creature->isDizzied()) {
			creature->queueDizzyFallEvent();
		} else {
			creature->setPosture(CreaturePosture::UPRIGHT);

			if (creature->isDizzied())
				creature->queueDizzyFallEvent();
		}

		return SUCCESS;
	}

};

#endif //STANDCOMMAND_H_

