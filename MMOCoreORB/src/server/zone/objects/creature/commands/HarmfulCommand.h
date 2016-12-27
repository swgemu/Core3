/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARMFULCOMMAND_H_
#define HARMFULCOMMAND_H_

class HarmfulCommand : public QueueCommand {
public:

	HarmfulCommand(const String& name, ZoneProcessServer* server)
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

#endif //HARMFULCOMMAND_H_
