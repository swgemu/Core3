/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETLOGINTITLECOMMAND_H_
#define SETLOGINTITLECOMMAND_H_

class SetLoginTitleCommand : public QueueCommand {
public:

	SetLoginTitleCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETLOGINTITLECOMMAND_H_
