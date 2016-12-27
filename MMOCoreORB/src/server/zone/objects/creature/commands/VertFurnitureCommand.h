/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VERTFURNITURECOMMAND_H_
#define VERTFURNITURECOMMAND_H_

class VertFurnitureCommand : public QueueCommand {
public:

	VertFurnitureCommand(const String& name, ZoneProcessServer* server)
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

#endif //VERTFURNITURECOMMAND_H_
