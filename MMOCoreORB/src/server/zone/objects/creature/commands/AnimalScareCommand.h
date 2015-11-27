/*

				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALSCARECOMMAND_H_
#define ANIMALSCARECOMMAND_H_

#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/managers/combat/CombatManager.h"
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

		if (targetObject == NULL || !targetObject->isCreature()) {
			creature->sendSystemMessage("@jedi_spam:animal_scare_fail"); //"You fail to scare your target."
			return INVALIDTARGET;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

		// Commence fleeing action...

			ManagedReference<Creature*> creatureTarget = targetObject.castTo<Creature*>();

			Locker clocker(creatureTarget, creature);

			AiAgent* aiAgent = cast<AiAgent*>(creatureTarget.get());

			AiMoveEvent* aiEvent = new AiMoveEvent(aiAgent);
			aiEvent->schedule(AiAgent::FLEEING);

			creatureTarget->dropFromDefenderLists(creature);
			creatureTarget->clearQueueActions();
			creatureTarget->setState(CreatureState::COMBATATTITUDEEVASIVE);
			creatureTarget->isFleeing();
			creature->doCombatAnimation(creatureTarget, STRING_HASHCODE("mind_trick_1"), 1, 0);
			creature->sendSystemMessage("@jedi_spam:animal_scare_success"); //"You successfully scare your target."

			CombatManager::instance()->broadcastCombatSpam(creature, creatureTarget, NULL, 0, "cbt_spam", combatSpam + "_hit", 1);

			return res;

			}

		return SUCCESS;
	}

};

#endif //ANIMALSCARECOMMAND_H_
