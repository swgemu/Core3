/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSGETTICKETSCOMMAND_H_
#define CSGETTICKETSCOMMAND_H_

class CsGetTicketsCommand : public QueueCommand {
public:

	CsGetTicketsCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSGETTICKETSCOMMAND_H_
