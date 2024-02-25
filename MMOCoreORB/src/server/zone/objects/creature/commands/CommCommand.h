/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMCOMMAND_H_
#define COMMCOMMAND_H_

class CommCommand : public QueueCommand {
public:

	CommCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPilotingShip())
			return INVALIDSTATE;

		return SUCCESS;
	}

};

#endif //COMMCOMMAND_H_
