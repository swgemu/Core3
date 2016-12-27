/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETMATCHMAKINGPERSONALIDCOMMAND_H_
#define SETMATCHMAKINGPERSONALIDCOMMAND_H_

class SetMatchMakingPersonalIdCommand : public QueueCommand {
public:

	SetMatchMakingPersonalIdCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETMATCHMAKINGPERSONALIDCOMMAND_H_
