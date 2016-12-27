/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CSSEARCHKNOWLEDGEBASECOMMAND_H_
#define CSSEARCHKNOWLEDGEBASECOMMAND_H_

class CsSearchKnowledgeBaseCommand : public QueueCommand {
public:

	CsSearchKnowledgeBaseCommand(const String& name, ZoneProcessServer* server)
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

#endif //CSSEARCHKNOWLEDGEBASECOMMAND_H_
