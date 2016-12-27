/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAGCOMMAND_H_
#define LAGCOMMAND_H_

class LagCommand : public QueueCommand {
public:

	LagCommand(const String& name, ZoneProcessServer* server)
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

#endif //LAGCOMMAND_H_
