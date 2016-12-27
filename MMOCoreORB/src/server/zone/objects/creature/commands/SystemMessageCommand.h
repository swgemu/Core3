/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SYSTEMMESSAGECOMMAND_H_
#define SYSTEMMESSAGECOMMAND_H_

class SystemMessageCommand : public QueueCommand {
public:

	SystemMessageCommand(const String& name, ZoneProcessServer* server)
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

#endif //SYSTEMMESSAGECOMMAND_H_
