/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLONECOMMAND_H_
#define CLONECOMMAND_H_

class CloneCommand : public QueueCommand {
public:

	CloneCommand(const String& name, ZoneProcessServer* server)
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

#endif //CLONECOMMAND_H_
