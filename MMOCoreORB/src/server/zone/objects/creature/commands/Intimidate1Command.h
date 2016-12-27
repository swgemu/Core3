/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INTIMIDATE1COMMAND_H_
#define INTIMIDATE1COMMAND_H_

#include "server/zone/packets/object/CombatSpam.h"
#include "CombatQueueCommand.h"

class Intimidate1Command : public CombatQueueCommand {
public:

	Intimidate1Command(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Reference<TangibleObject*> targetObject = server->getZoneServer()->getObject(target).castTo<TangibleObject*>();

		if (targetObject == NULL || !targetObject->isCreatureObject())
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == TOOFAR && creature->isPlayerCreature()) {
			CombatSpam* msg = new CombatSpam(creature, targetObject, creature, NULL, 0, "cbt_spam", "intim_out_of_range", 0);
			creature->sendMessage(msg);
		}
		
		if (res == SUCCESS && creature->isPlayerCreature()) {
			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

			if (ghost != NULL && !ghost->getCommandMessageString(STRING_HASHCODE("intimidate1")).isEmpty() && creature->checkCooldownRecovery("command_message")) {
				UnicodeString shout(ghost->getCommandMessageString(STRING_HASHCODE("intimidate1")));
				server->getChatManager()->broadcastChatMessage(creature, shout, 0, 80, creature->getMoodID(), 0, ghost->getLanguageID());
				creature->updateCooldownTimer("command_message", 30 * 1000);
			}
		}
		return res;
	}

};

#endif //INTIMIDATE1COMMAND_H_
