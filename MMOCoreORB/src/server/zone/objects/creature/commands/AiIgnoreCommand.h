/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AIIGNORECOMMAND_H_
#define AIIGNORECOMMAND_H_

class AiIgnoreCommand : public QueueCommand {
public:

	AiIgnoreCommand(const String& name, ZoneProcessServer* server)
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

#endif //AIIGNORECOMMAND_H_
