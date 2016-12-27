/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETMOODCOMMAND_H_
#define SETMOODCOMMAND_H_

class SetMoodCommand : public QueueCommand {
public:

	SetMoodCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETMOODCOMMAND_H_
