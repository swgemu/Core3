/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EXECUTEKNOWLEDGEBASEMESSAGECOMMAND_H_
#define EXECUTEKNOWLEDGEBASEMESSAGECOMMAND_H_

class ExecuteKnowledgeBaseMessageCommand : public QueueCommand {
public:

	ExecuteKnowledgeBaseMessageCommand(const String& name, ZoneProcessServer* server)
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

#endif //EXECUTEKNOWLEDGEBASEMESSAGECOMMAND_H_
