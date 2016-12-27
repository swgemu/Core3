/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTDRAFTSLOTSCOMMAND_H_
#define REQUESTDRAFTSLOTSCOMMAND_H_

class RequestDraftSlotsCommand : public QueueCommand {
public:

	RequestDraftSlotsCommand(const String& name, ZoneProcessServer* server)
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

#endif //REQUESTDRAFTSLOTSCOMMAND_H_
