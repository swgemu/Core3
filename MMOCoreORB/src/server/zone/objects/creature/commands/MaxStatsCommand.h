/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MAXSTATSCOMMAND_H_
#define MAXSTATSCOMMAND_H_

class MaxStatsCommand : public QueueCommand {
public:

	MaxStatsCommand(const String& name, ZoneProcessServer* server)
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

#endif //MAXSTATSCOMMAND_H_
