/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATCOMMAND_H_
#define COMBATCOMMAND_H_

class CombatCommand : public QueueCommand {
public:

	CombatCommand(const String& name, ZoneProcessServer* server)
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

#endif //COMBATCOMMAND_H_
