/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALSCARECOMMAND_H_
#define ANIMALSCARECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/events/AiMoveEvent.h"

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

		if (targetObject == NULL || !targetObject->isCreatureObject() || targetObject->isPlayerCreature() || targetObject->isDroidObject() || !targetObject->isCreature()) {
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			// Commence fleeing action...

			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget != NULL) {
				Locker clocker(creatureTarget, creature);

				AiAgent* aiAgent = cast<AiAgent*>(creatureTarget.get());

				AiMoveEvent* aiEvent = new AiMoveEvent(aiAgent);
				aiEvent->schedule();

				CombatManager::instance()->attemptPeace(creatureTarget);

				creature->sendSystemMessage("@jedi_spam:animal_scare_success"); //"You successfully scare your target."

			}

		}

		else {
			bool attemptPeace = CombatManager::instance()->attemptPeace;

			creature->sendSystemMessage("@jedi_spam:animal_scare_fail"); //"You fail to scare your target."
		}

		return SUCCESS;
	}

};

#endif //ANIMALSCARECOMMAND_H_
