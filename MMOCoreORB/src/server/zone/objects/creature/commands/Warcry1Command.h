/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WARCRY1COMMAND_H_
#define WARCRY1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/chat/ChatMessage.h"
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

		if (res == SUCCESS && creature->isPlayerCreature() && creature->getPlayerObject()->getCommandMessageString(STRING_HASHCODE("warcry1")).isEmpty()==false && creature->checkCooldownRecovery("command_message")) {
			UnicodeString shout(creature->getPlayerObject()->getCommandMessageString(STRING_HASHCODE("warcry1")));
 	 	 	server->getChatManager()->broadcastMessage(creature, shout, 0, 0, 80);
 	 	 	creature->updateCooldownTimer("command_message", 30 * 1000);
		}

		return res;
	}

};

#endif //WARCRY1COMMAND_H_
