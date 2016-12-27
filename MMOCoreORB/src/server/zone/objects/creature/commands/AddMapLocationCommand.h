/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDMAPLOCATIONCOMMAND_H_
#define ADDMAPLOCATIONCOMMAND_H_

class AddMapLocationCommand : public QueueCommand {
public:

	AddMapLocationCommand(const String& name, ZoneProcessServer* server)
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

#endif //ADDMAPLOCATIONCOMMAND_H_
