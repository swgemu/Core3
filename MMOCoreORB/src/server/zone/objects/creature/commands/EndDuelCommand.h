/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ENDDUELCOMMAND_H_
#define ENDDUELCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class EndDuelCommand : public QueueCommand {
public:
	EndDuelCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		auto targetObject = zoneServer->getObject(target);

		CombatManager* combatManager = CombatManager::instance();

		if (combatManager == nullptr)
			return GENERALERROR;

		if (targetObject == nullptr || !targetObject->isPlayerCreature() || targetObject == creature) {
			combatManager->freeDuelList(creature);
			return SUCCESS;
		}

		auto targetPlayer = targetObject->asCreatureObject();

		if (targetPlayer == nullptr)
			return GENERALERROR;

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (combatManager->areInDuel(creature, targetPlayer)) {
			combatManager->requestEndDuel(creature, targetPlayer);
		// Player using the command has an open challenge to targetPlayer
		} else if (combatManager->hasActiveDuelChallenge(creature, targetPlayer)) {
			ghost->removeFromDuelList(targetPlayer);

			StringIdChatParameter stringId("duel", "cancel_self");
			stringId.setTT(targetPlayer->getObjectID());
			creature->sendSystemMessage(stringId);

			StringIdChatParameter stringId2("duel", "cancel_target");
			stringId2.setTT(creature->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		// Target has an open challenge to player using the command
		} else if (combatManager->hasActiveDuelChallenge(targetPlayer, creature)) {
			auto targetGhost = targetPlayer->getPlayerObject();

			if (targetGhost == nullptr)
				return GENERALERROR;

			Locker clock(targetPlayer, creature);

			targetGhost->removeFromDuelList(creature);

			StringIdChatParameter stringId("duel", "reject_self");
			stringId.setTT(targetPlayer->getObjectID());
			creature->sendSystemMessage(stringId);

			StringIdChatParameter stringId2("duel", "reject_target");
			stringId2.setTT(creature->getObjectID());
			targetPlayer->sendSystemMessage(stringId2);
		}

		return SUCCESS;
	}
};

#endif // ENDDUELCOMMAND_H_
