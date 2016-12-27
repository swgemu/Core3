/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HASVETERANREWARDCOMMAND_H_
#define HASVETERANREWARDCOMMAND_H_

class HasVeteranRewardCommand : public QueueCommand {
public:

	HasVeteranRewardCommand(const String& name, ZoneProcessServer* server)
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

#endif //HASVETERANREWARDCOMMAND_H_
