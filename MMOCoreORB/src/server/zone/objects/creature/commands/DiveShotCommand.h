/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DIVESHOTCOMMAND_H_
#define DIVESHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage3.h"

class DiveShotCommand : public CombatQueueCommand {
public:

	DiveShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		int ret = doCombatAction(creature, target);

		if (ret != SUCCESS)
			return ret;

		if (creature->isDizzied() && System::random(100) < 85) {
			creature->queueDizzyFallEvent();
		} else {
			creature->setPosture(CreaturePosture::PRONE, false);

			CreatureObjectDeltaMessage3* pmsg = new CreatureObjectDeltaMessage3(creature);
			pmsg->updatePosture();
			pmsg->close();
			creature->broadcastMessage(pmsg, true);
		}

		return SUCCESS;
	}

};

#endif //DIVESHOTCOMMAND_H_
