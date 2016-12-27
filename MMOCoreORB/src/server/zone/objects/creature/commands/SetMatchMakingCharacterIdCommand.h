/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETMATCHMAKINGCHARACTERIDCOMMAND_H_
#define SETMATCHMAKINGCHARACTERIDCOMMAND_H_

class SetMatchMakingCharacterIdCommand : public QueueCommand {
public:

	SetMatchMakingCharacterIdCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETMATCHMAKINGCHARACTERIDCOMMAND_H_
