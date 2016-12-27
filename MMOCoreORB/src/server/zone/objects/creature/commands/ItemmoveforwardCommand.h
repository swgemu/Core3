/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ITEMMOVEFORWARDCOMMAND_H_
#define ITEMMOVEFORWARDCOMMAND_H_

class ItemmoveforwardCommand : public QueueCommand {
public:

	ItemmoveforwardCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->executeObjectControllerAction(0x4B74A403, target, "forward 10");

		return SUCCESS;
	}

};

#endif //ITEMMOVEFORWARDCOMMAND_H_
