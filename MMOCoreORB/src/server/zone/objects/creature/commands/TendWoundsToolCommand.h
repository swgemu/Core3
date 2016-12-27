/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TENDWOUNDSTOOLCOMMAND_H_
#define TENDWOUNDSTOOLCOMMAND_H_

class TendWoundsToolCommand : public QueueCommand {
public:

	TendWoundsToolCommand(const String& name, ZoneProcessServer* server)
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

#endif //TENDWOUNDSTOOLCOMMAND_H_
