/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMBATSPAMCOMMAND_H_
#define COMBATSPAMCOMMAND_H_

class CombatSpamCommand : public QueueCommand {
public:

	CombatSpamCommand(const String& name, ZoneProcessServer* server)
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

#endif //COMBATSPAMCOMMAND_H_
