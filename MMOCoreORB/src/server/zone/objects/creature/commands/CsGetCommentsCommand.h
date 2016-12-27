/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSGETCOMMENTSCOMMAND_H_
#define CSGETCOMMENTSCOMMAND_H_

class CsGetCommentsCommand : public QueueCommand {
public:

	CsGetCommentsCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSGETCOMMENTSCOMMAND_H_
