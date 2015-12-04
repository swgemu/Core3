/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALATTACKCOMMAND_H_
#define ANIMALATTACKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/events/AiMoveEvent.h"
#include "server/zone/objects/creature/ai/events/AiLoadTask.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/objects/creature/commands/QueueCommand.h"

class AnimalAttackCommand : public ForcePowersQueueCommand {
public:

	AnimalAttackCommand(const String& name, ZoneProcessServer* server)
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

		if (targetObject == NULL || !targetObject->isCreature()) {
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		if (!targetCreature->isAttackableBy(creature))
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		CombatManager* combatManager = CombatManager::instance();

		if (res == SUCCESS) {

			// Commence controlling action...

			ManagedReference<AiAgent*> creatureTarget = targetObject.castTo<AiAgent*>();

			if (creatureTarget != NULL) {
				Locker clocker(creatureTarget, creature);

				AiAgent* aiAgent = cast<AiAgent*>(creatureTarget.get());

				AiMoveEvent* aiEvent = new AiMoveEvent(aiAgent);
				aiEvent->schedule();

				CombatManager::instance()->forcePeace(creatureTarget);

				AiLoadTask* aiTask = new AiLoadTask(aiAgent);
				aiTask->schedule();

				creature->getMainDefender();
				creatureTarget->setDefender(creature->getMainDefender());

				Reference<CreatureObject*> defender = server->getZoneServer()->getObject(target, true).castTo<CreatureObject*>();
				if (defender == NULL || !defender->isAttackableBy(creatureTarget) ) {
					return GENERALERROR;
				} else {
					creatureTarget->enqueueAttack(QueueCommand::FRONT);
				}

				creature->sendSystemMessage("@jedi_spam:animal_attack_success"); //"You successfully enrage your target."

			}
		}

		else {
			creature->sendSystemMessage("@jedi_spam:animal_attack_fail"); //"You fail to enrage your target."

		}

		return SUCCESS;
	}

};

#endif //ANIMALATTACKCOMMAND_H_
