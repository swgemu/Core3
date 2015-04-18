/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KNEELCOMMAND_H_
#define KNEELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/creature/CreatureManager.h"

class KneelCommand : public QueueCommand {
public:

	KneelCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/*if (creature->isDizzied()) {
			if (creature->getPosture() != CreaturePosture::CROUCHED) {
				creature->setPosture(CreaturePosture::KNOCKEDDOWN);
				creature->sendSystemMessage("@cbt_spam:dizzy_fall_down_single");

				return SUCCESS;
			}
		}*/

		if (!creature->checkDizzyDelay() && creature->isDizzied()) {
			creature->queueDizzyFallEvent();
		} else {
			creature->setPosture(CreaturePosture::CROUCHED, true);

			if (creature->isDizzied())
				creature->queueDizzyFallEvent();
		}

		return SUCCESS;
	}

};

#endif //KNEELCOMMAND_H_
