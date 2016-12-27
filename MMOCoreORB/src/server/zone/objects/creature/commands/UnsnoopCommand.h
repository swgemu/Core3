/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNSNOOPCOMMAND_H_
#define UNSNOOPCOMMAND_H_

class UnsnoopCommand : public QueueCommand {
public:

	UnsnoopCommand(const String& name, ZoneProcessServer* server)
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

#endif //UNSNOOPCOMMAND_H_
