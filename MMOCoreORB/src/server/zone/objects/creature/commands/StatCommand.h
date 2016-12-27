/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STATCOMMAND_H_
#define STATCOMMAND_H_

class StatCommand : public QueueCommand {
public:

	StatCommand(const String& name, ZoneProcessServer* server)
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

#endif //STATCOMMAND_H_
