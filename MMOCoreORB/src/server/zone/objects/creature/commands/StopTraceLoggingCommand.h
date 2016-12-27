/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPTRACELOGGINGCOMMAND_H_
#define STOPTRACELOGGINGCOMMAND_H_

class StopTraceLoggingCommand : public QueueCommand {
public:

	StopTraceLoggingCommand(const String& name, ZoneProcessServer* server)
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

#endif //STOPTRACELOGGINGCOMMAND_H_
