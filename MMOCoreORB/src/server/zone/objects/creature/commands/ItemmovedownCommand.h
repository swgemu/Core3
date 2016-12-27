/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMMOVEDOWNCOMMAND_H_
#define ITEMMOVEDOWNCOMMAND_H_

class ItemmovedownCommand : public QueueCommand {
public:

	ItemmovedownCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->executeObjectControllerAction(0x4B74A403, target, "down 10");

		return SUCCESS;
	}

};

#endif //ITEMMOVEDOWNCOMMAND_H_
