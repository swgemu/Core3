/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPLANETLIMITCOMMAND_H_
#define SETPLANETLIMITCOMMAND_H_

class SetPlanetLimitCommand : public QueueCommand {
public:

	SetPlanetLimitCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //SETPLANETLIMITCOMMAND_H_
