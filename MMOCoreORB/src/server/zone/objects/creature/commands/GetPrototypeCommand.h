/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETPROTOTYPECOMMAND_H_
#define GETPROTOTYPECOMMAND_H_

class GetPrototypeCommand : public QueueCommand {
public:

	GetPrototypeCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETPROTOTYPECOMMAND_H_
