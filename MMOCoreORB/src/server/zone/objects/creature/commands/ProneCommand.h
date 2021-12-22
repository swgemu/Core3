/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PRONECOMMAND_H_
#define PRONECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ProneCommand : public QueueCommand {
public:

	ProneCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isAiAgent()) {
			if (creature->isNonPlayerCreatureObject() && creature->isDizzied() && System::random(100) < 85) {
				creature->queueDizzyFallEvent();
			} else if (creature->isInCombat()) {
				creature->setPosture(CreaturePosture::PRONE);
				creature->doCombatAnimation(STRING_HASHCODE("change_posture"));
			} else {
				creature->setPosture(CreaturePosture::PRONE);
			}
		} else {
			if (creature->isDizzied() && System::random(100) < 85) {
				creature->queueDizzyFallEvent();
			} else {
				creature->setPosture(CreaturePosture::PRONE, true, true);
			}
		}

		return SUCCESS;
	}
};

#endif //PRONECOMMAND_H_
