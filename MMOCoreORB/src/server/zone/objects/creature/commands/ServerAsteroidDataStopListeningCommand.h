/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SERVERASTEROIDDATASTOPLISTENING_H_
#define SERVERASTEROIDDATASTOPLISTENING_H_

#include "CombatQueueCommand.h"

class ServerAsteroidDataStopListeningCommand : public CombatQueueCommand {
public:

	ServerAsteroidDataStopListeningCommand(const String& name, ZoneProcessServer* server)
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

#endif //SERVERASTEROIDDATASTOPLISTENING_H_
