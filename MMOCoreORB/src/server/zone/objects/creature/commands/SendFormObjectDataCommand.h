/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SENDFORMOBJECTDATA_H_
#define SENDFORMOBJECTDATA_H_

#include "CombatQueueCommand.h"

class SendFormObjectDataCommand : public CombatQueueCommand {
public:

	SendFormObjectDataCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};

#endif //SENDFORMOBJECTDATA_H_
