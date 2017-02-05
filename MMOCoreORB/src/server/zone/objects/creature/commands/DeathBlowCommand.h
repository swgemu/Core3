/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DEATHBLOWCOMMAND_H_
#define DEATHBLOWCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/CollisionManager.h"

class DeathBlowCommand : public QueueCommand {
public:

	DeathBlowCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (creature == targetObject || targetObject == NULL)
			return GENERALERROR;

		//TODO: play coup_de_grace combat animations - ranged_coup_de_grace, melee_coup_de_grace, unarmed_coup_de_grace

		if (targetObject->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( targetObject.get());

			Locker clocker(player, creature);

			if (!CollisionManager::checkLineOfSight(creature, player)) {
				creature->sendSystemMessage("@combat_effects:cansee_fail");// You cannot see your target.
				return GENERALERROR;
			}

			if (!player->isIncapacitated() || player->isFeigningDeath()){
				creature->sendSystemMessage("@error_message:target_not_incapacitated"); //You cannot perform the death blow. Your target is not incapacitated.
				return GENERALERROR;
			}

			if (player->isAttackableBy(creature) && checkDistance(player, creature, 5)) {
				PlayerManager* playerManager = server->getPlayerManager();

				playerManager->killPlayer(creature, player, 1);
			}
		} else if (targetObject->isPet()) {
			AiAgent* pet = cast<AiAgent*>( targetObject.get());

			Locker clocker(pet, creature);

			if (!CollisionManager::checkLineOfSight(creature, pet)) {
				creature->sendSystemMessage("@combat_effects:cansee_fail");// You cannot see your target.
				return GENERALERROR;
			}

			if (!pet->isIncapacitated()){
				creature->sendSystemMessage("@error_message:target_not_incapacitated"); //You cannot perform the death blow. Your target is not incapacitated.
				return GENERALERROR;
			}

			if (pet->isAttackableBy(creature) && checkDistance(pet, creature, 5)) {
				PetManager* petManager = server->getZoneServer()->getPetManager();

				petManager->killPet(creature, pet);
			}
		} else {
			return GENERALERROR;
		}

		StringIdChatParameter params("base_player", "prose_target_dead"); // %TT is no more.
		params.setTT(targetObject->getDisplayedName());
		creature->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //DEATHBLOWCOMMAND_H_
