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

		Locker clocker(player, creature);

		PlayerManager* playerManager = server->getPlayerManager();

		if (!CollisionManager::checkLineOfSight(creature, player)) {
			creature->sendSystemMessage("@container_error_message:container18"); //You can't see that object.  You may have to move closer to it.
			return GENERALERROR;
		}

		WeaponObject* weapon = creature->getWeapon();

		if (!player->isIncapacitated() && !player->isDead()) {
			creature->sendSystemMessage("@error_message:target_not_incapacitated");  //You cannot perform the death blow. Your target is not incapacitated.
			return GENERALERROR;
		}  else if (player->isDead()) {
			StringIdChatParameter params("error_message", "prose_target_already_dead");
			params.setTT(player->getDisplayedName());
			creature->sendSystemMessage(params); //But %TT is already dead!
			return GENERALERROR;
		}

		int maxRange = weapon->getMaxRange();

		if (!player->isInRange(creature, maxRange + player->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;

 		if (player->isAttackableBy(creature) && player->isIncapacitated())
 			playerManager->killPlayer(creature, player, 1);

 		return doCombatAction(creature,target);

	}

};

#endif //SNIPERSHOTCOMMAND_H_
