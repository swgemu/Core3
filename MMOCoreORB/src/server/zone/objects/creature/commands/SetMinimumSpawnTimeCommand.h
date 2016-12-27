/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETMINIMUMSPAWNTIMECOMMAND_H_
#define SETMINIMUMSPAWNTIMECOMMAND_H_

class SetMinimumSpawnTimeCommand : public QueueCommand {
public:

	SetMinimumSpawnTimeCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETMINIMUMSPAWNTIMECOMMAND_H_
