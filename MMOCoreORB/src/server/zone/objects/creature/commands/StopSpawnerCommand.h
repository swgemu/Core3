/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STOPSPAWNERCOMMAND_H_
#define STOPSPAWNERCOMMAND_H_

class StopSpawnerCommand : public QueueCommand {
public:

	StopSpawnerCommand(const String& name, ZoneProcessServer* server)
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

#endif //STOPSPAWNERCOMMAND_H_
