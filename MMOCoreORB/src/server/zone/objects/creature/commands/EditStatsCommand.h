/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EDITSTATSCOMMAND_H_
#define EDITSTATSCOMMAND_H_

class EditStatsCommand : public QueueCommand {
public:

	EditStatsCommand(const String& name, ZoneProcessServer* server)
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

#endif //EDITSTATSCOMMAND_H_
