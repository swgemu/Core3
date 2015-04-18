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

		if (targetObject->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( targetObject.get());

			Locker clocker(player, creature);

			if (!CollisionManager::checkLineOfSight(creature, player)) {
				creature->sendSystemMessage("@container_error_message:container18");
				return GENERALERROR;
			}

			if (!player->isIncapacitated()){
				creature->sendSystemMessage("@error_message:target_not_incapacitated");
				return GENERALERROR;
			}

			if (player->isAttackableBy(creature) && player->isInRange(creature, 5)) {
				PlayerManager* playerManager = server->getPlayerManager();

				playerManager->killPlayer(creature, player, 1);
			}
		} else if (targetObject->isPet()) {
			AiAgent* pet = cast<AiAgent*>( targetObject.get());

			Locker clocker(pet, creature);

			if (!CollisionManager::checkLineOfSight(creature, pet)) {
				creature->sendSystemMessage("@container_error_message:container18");
				return GENERALERROR;
			}

			if (!pet->isIncapacitated()){
				creature->sendSystemMessage("@error_message:target_not_incapacitated");
				return GENERALERROR;
			}

			if (pet->isAttackableBy(creature) && pet->isInRange(creature, 5)) {
				PetManager* petManager = server->getZoneServer()->getPetManager();

				petManager->killPet(creature, pet);
			}
		} else {
			return GENERALERROR;
		}

		return SUCCESS;
	}

};

#endif //DEATHBLOWCOMMAND_H_
