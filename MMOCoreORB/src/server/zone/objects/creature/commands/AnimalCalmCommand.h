/*
					Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALCALMCOMMAND_H_
#define ANIMALCALMCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/AiAgent.h"

class AnimalCalmCommand : public ForcePowersQueueCommand {
public:

	AnimalCalmCommand(const String& name, ZoneProcessServer* server)
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

			// Commence calming action...

			ManagedReference<CreatureObject*> creatureTarget = targetObject.castTo<CreatureObject*>();

			if (creatureTarget != NULL) {
				Locker clocker(creatureTarget, creature);

				AiAgent* aiAgent = cast<AiAgent*>(creatureTarget.get());

				CombatManager::instance()->forcePeace(creatureTarget);

				creature->sendSystemMessage("@jedi_spam:calm_target"); //"You successfully calm down your target."

				CombatManager::instance()->broadcastCombatSpam(creature, creatureTarget, NULL, 0, "cbt_spam", combatSpam + "_hit", 1);
			}

		}

		else if (!res == SUCCESS) {
				creature->sendSystemMessage("@jedi_spam:fail_calm_target"); //"You fail to calm your target."
		}

		return SUCCESS;
	}

};

#endif //ANIMALCALMCOMMAND_H_
