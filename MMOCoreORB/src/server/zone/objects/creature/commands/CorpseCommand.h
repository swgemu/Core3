/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CORPSECOMMAND_H_
#define CORPSECOMMAND_H_

class CorpseCommand : public QueueCommand {
public:

	CorpseCommand(const String& name, ZoneProcessServer* server)
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

#endif //CORPSECOMMAND_H_
