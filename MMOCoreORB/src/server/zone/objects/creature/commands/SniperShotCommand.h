/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SNIPERSHOTCOMMAND_H_
#define SNIPERSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"

class SniperShotCommand : public CombatQueueCommand {
public:

	SniperShotCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (creature == targetObject || targetObject == NULL || !targetObject->isPlayerCreature())
			return INVALIDTARGET;

		CreatureObject* player = cast<CreatureObject*>( targetObject.get());

		if (player->isDead()) {
			StringIdChatParameter params("error_message", "prose_target_already_dead"); // But %TT is already dead!
			params.setTT(player->getDisplayedName());
			creature->sendSystemMessage(params);
			return GENERALERROR;
		}

		UnicodeString arg = "hitIncapTarget=1;";
		int ret = doCombatAction(creature, target, arg);

		if (ret != SUCCESS)
			return ret;

		if (player->isIncapacitated() && !player->isFeigningDeath()) {
			Locker clocker(player, creature);

			PlayerManager* playerManager = server->getPlayerManager();
			playerManager->killPlayer(creature, player, 1, false);

			StringIdChatParameter params("base_player", "prose_target_dead"); // %TT is no more.
			params.setTT(player->getDisplayedName());
			creature->sendSystemMessage(params);
		} else if (!player->isDead()) {
			creature->sendSystemMessage("@error_message:target_not_incapacitated");  // You cannot perform the death blow. Your target is not incapacitated.
		}

		return ret;
	}

};

#endif //SNIPERSHOTCOMMAND_H_
