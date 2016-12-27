/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETVETERANREWARDTIMECSCOMMAND_H_
#define GETVETERANREWARDTIMECSCOMMAND_H_

class GetVeteranRewardTimeCsCommand : public QueueCommand {
public:

	GetVeteranRewardTimeCsCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETVETERANREWARDTIMECSCOMMAND_H_
