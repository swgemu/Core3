/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PAUSEMUSICCOMMAND_H_
#define PAUSEMUSICCOMMAND_H_

class PauseMusicCommand : public QueueCommand {
public:

	PauseMusicCommand(const String& name, ZoneProcessServer* server)
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

#endif //PAUSEMUSICCOMMAND_H_
