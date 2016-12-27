/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTTARGETSPAWNERCOMMAND_H_
#define STARTTARGETSPAWNERCOMMAND_H_

class StartTargetSpawnerCommand : public QueueCommand {
public:

	StartTargetSpawnerCommand(const String& name, ZoneProcessServer* server)
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

#endif //STARTTARGETSPAWNERCOMMAND_H_
