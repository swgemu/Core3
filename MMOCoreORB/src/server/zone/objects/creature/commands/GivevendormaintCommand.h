/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GIVEVENDORMAINTCOMMAND_H_
#define GIVEVENDORMAINTCOMMAND_H_

class GivevendormaintCommand : public QueueCommand {
public:

	GivevendormaintCommand(const String& name, ZoneProcessServer* server)
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

#endif //GIVEVENDORMAINTCOMMAND_H_
