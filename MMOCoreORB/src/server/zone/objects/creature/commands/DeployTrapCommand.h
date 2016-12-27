/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEPLOYTRAPCOMMAND_H_
#define DEPLOYTRAPCOMMAND_H_

class DeployTrapCommand : public QueueCommand {
public:

	DeployTrapCommand(const String& name, ZoneProcessServer* server)
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

#endif //DEPLOYTRAPCOMMAND_H_
