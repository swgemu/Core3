/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
#define CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_

class CreateSpawningElementWithDifficultyCommand : public QueueCommand {
public:

	CreateSpawningElementWithDifficultyCommand(const String& name, ZoneProcessServer* server)
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

#endif //CREATESPAWNINGELEMENTWITHDIFFICULTYCOMMAND_H_
