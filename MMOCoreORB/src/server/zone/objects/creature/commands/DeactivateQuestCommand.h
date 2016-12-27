/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEACTIVATEQUESTCOMMAND_H_
#define DEACTIVATEQUESTCOMMAND_H_

class DeactivateQuestCommand : public QueueCommand {
public:

	DeactivateQuestCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEACTIVATEQUESTCOMMAND_H_
