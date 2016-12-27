/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REPORTCOMMAND_H_
#define REPORTCOMMAND_H_

class ReportCommand : public QueueCommand {
public:

	ReportCommand(const String& name, ZoneProcessServer* server)
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

#endif //REPORTCOMMAND_H_
