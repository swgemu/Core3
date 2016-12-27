/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REVOKEBADGECOMMAND_H_
#define REVOKEBADGECOMMAND_H_

class RevokeBadgeCommand : public QueueCommand {
public:

	RevokeBadgeCommand(const String& name, ZoneProcessServer* server)
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

#endif //REVOKEBADGECOMMAND_H_
