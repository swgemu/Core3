/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPUBLICSTATECOMMAND_H_
#define SETPUBLICSTATECOMMAND_H_

class SetPublicStateCommand : public QueueCommand {
public:

	SetPublicStateCommand(const String& name, ZoneProcessServer* server)
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

#endif //SETPUBLICSTATECOMMAND_H_
