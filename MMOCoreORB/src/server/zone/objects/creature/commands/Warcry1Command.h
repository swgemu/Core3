/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WARCRY1COMMAND_H_
#define WARCRY1COMMAND_H_

#include "server/zone/managers/combat/CombatManager.h"
#include "CombatQueueCommand.h"

class Warcry1Command : public CombatQueueCommand {
public:

	Warcry1Command(const String& name, ZoneProcessServer* server)
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

		if (res == TOOFAR)
			CombatManager::instance()->broadcastCombatSpam(creature, targetObject, NULL, 0, "cbt_spam", "warcry_out_of_range", 0);

		if (res == SUCCESS && creature->isPlayerCreature()) {
			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

			if (ghost != NULL && !ghost->getCommandMessageString(STRING_HASHCODE("warcry1")).isEmpty() && creature->checkCooldownRecovery("command_message")) {
					UnicodeString shout(ghost->getCommandMessageString(STRING_HASHCODE("warcry1")));
					server->getChatManager()->broadcastChatMessage(creature, shout, 0, 80, creature->getMoodID(), 0, ghost->getLanguageID());
					creature->updateCooldownTimer("command_message", 30 * 1000);
			}
		}
		return res;
	}

};

#endif //WARCRY1COMMAND_H_
