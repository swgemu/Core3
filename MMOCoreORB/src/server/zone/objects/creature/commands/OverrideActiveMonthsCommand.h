/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef OVERRIDEACTIVEMONTHSCOMMAND_H_
#define OVERRIDEACTIVEMONTHSCOMMAND_H_

class OverrideActiveMonthsCommand : public QueueCommand {
public:

	OverrideActiveMonthsCommand(const String& name, ZoneProcessServer* server)
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

#endif //OVERRIDEACTIVEMONTHSCOMMAND_H_
