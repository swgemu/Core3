/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETVETERANREWARDCOMMAND_H_
#define SETVETERANREWARDCOMMAND_H_

class SetVeteranRewardCommand : public QueueCommand {
public:

	SetVeteranRewardCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETVETERANREWARDCOMMAND_H_
