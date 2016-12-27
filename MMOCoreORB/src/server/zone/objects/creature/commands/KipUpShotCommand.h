/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KIPUPSHOTCOMMAND_H_
#define KIPUPSHOTCOMMAND_H_

#include "CombatQueueCommand.h"

class KipUpShotCommand : public CombatQueueCommand {
public:

	KipUpShotCommand(const String& name, ZoneProcessServer* server)
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
		}

		return SUCCESS;
	}

};

#endif //KIPUPSHOTCOMMAND_H_
