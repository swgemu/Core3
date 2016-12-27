/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETATTRIBUTESCOMMAND_H_
#define GETATTRIBUTESCOMMAND_H_

class GetAttributesCommand : public QueueCommand {
public:

	GetAttributesCommand(const String& name, ZoneProcessServer* server)
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

#endif //GETATTRIBUTESCOMMAND_H_
