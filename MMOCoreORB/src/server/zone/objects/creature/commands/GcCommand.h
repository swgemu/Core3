/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GCCOMMAND_H_
#define GCCOMMAND_H_

class GcCommand : public QueueCommand {
public:

	GcCommand(const String& name, ZoneProcessServer* server)
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

#endif //GCCOMMAND_H_
