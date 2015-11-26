/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALSCARECOMMAND_H_
#define ANIMALSCARECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class AnimalScareCommand : public ForcePowersQueueCommand {
public:

	AnimalScareCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
				return INVALIDTARGET;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || object->isPlayerCreature())
				return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>( object.get());

		if (targetCreature == NULL || targetCreature->isDead() || targetCreature->isNonPlayerCreatureObject() || targetCreature->isDroidSpecies() || targetCreature->isWalkerSpecies() || !targetCreature->isAttackableBy(creature))
				return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Commence fleeing action...

			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget != NULL) {
				Locker clocker(creatureTarget, creature);

				ManagedReference<AiAgent*> target = cast<AiMoveEvent*>(creature);

				Locker locker(target);

				CombatManager::instance()->attemptPeace(target);

				target->setOblivious() && target->clearCombatState() && target->setMovementCounter(100);

				CombatManager::instance()->broadcastCombatSpam(creature, creatureTarget, NULL, 0, "cbt_spam", combatSpam + "_hit", 1);
			}

		}

		return SUCCESS;
	}

};

#endif //ANIMALSCARECOMMAND_H_
