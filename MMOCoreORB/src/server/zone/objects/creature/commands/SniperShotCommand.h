/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SNIPERSHOTCOMMAND_H_
#define SNIPERSHOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "CombatQueueCommand.h"
#include "server/zone/managers/combat/CombatManager.h"

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

		Locker clocker(player, creature);

		PlayerManager* playerManager = server->getPlayerManager();

		WeaponObject* weapon = creature->getWeapon();

		int maxRange = weapon->getMaxRange();
		if (!player->isInRange(creature, maxRange + player->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

		if (!CollisionManager::checkLineOfSight(creature, player)) {
			creature->sendSystemMessage("@container_error_message:container18"); //You can't see that object.  You may have to move closer to it.
			return GENERALERROR;
		}

		if (player->isDead()) {
			StringIdChatParameter params("error_message", "prose_target_already_dead");
			params.setTT(player->getDisplayedName());
			creature->sendSystemMessage(params); //But %TT is already dead!
			return GENERALERROR;
		}

		int res = doCombatAction(creature, target);

		if (player->isAttackableBy(creature) && player->isFeigningDeath() == false) {

			if (player->isIncapacitated()) {

				if (CombatManager::instance()->applySpecialAttackCost(creature, creature->getWeapon(), CreatureAttackData("", this, target))) {
						CombatManager::instance()->broadcastCombatSpam(creature, player, NULL, 50, "cbt_spam", combatSpam + "_hit", 1);
						playerManager->killPlayer(creature, player, 1, true);
						player->updatePostures(false);
						creature->doCombatAnimation(player, STRING_HASHCODE ("fire_1_special_single_medium_face"), 0x01, 0xFF);
						return SUCCESS;
				} else {
					return INSUFFICIENTHAM;
				}

			} else {
				doCombatAction(creature, target);
				if (player->isIncapacitated()) {
					playerManager->killPlayer(creature, player, 1, true);
					return SUCCESS;
				}
			}

		} else if ((!player->isIncapacitated() || player->isFeigningDeath()) && res == SUCCESS) {
			creature->sendSystemMessage("@error_message:target_not_incapacitated");  //You cannot perform the death blow. Your target is not incapacitated.
			return res;
		}

 		return res;

	}

};

#endif //SNIPERSHOTCOMMAND_H_
