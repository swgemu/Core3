/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETMAXIMUMSPAWNTIMECOMMAND_H_
#define SETMAXIMUMSPAWNTIMECOMMAND_H_

class SetMaximumSpawnTimeCommand : public QueueCommand {
public:

	SetMaximumSpawnTimeCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETMAXIMUMSPAWNTIMECOMMAND_H_
