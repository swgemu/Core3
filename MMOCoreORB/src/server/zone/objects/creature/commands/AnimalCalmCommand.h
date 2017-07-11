/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALCALMCOMMAND_H_
#define ANIMALCALMCOMMAND_H_

#include "server/zone/objects/creature/commands/JediQueueCommand.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/managers/combat/CombatManager.h"

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

		Creature* targetCreature = cast<Creature*>(targetObject.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			ManagedReference<Creature*> creatureTarget = targetObject.castTo<Creature*>();

			// Commence calming action...

			Locker clocker(creatureTarget, creature);

			if (targetObject == NULL || !targetObject->isCreature()) {
				creature->sendSystemMessage("@error_message:target_not_creature"); //"The selected action cannot be performed because your target is not a creature."
				return GENERALERROR;
			}

			if (creatureTarget->getMainDefender() == creature) {
				creatureTarget->removeDefender(creature);
				//CombatManager::instance()->forcePeace(creatureTarget);
			}

			creature->doCombatAnimation(creatureTarget, STRING_HASHCODE("mind_trick_1"), 1, 0);
			creature->sendSystemMessage("@jedi_spam:calm_target"); //"You successfully calm down your target."

			CombatManager::instance()->broadcastCombatSpam(creature, targetCreature, NULL, 0, "cbt_spam", combatSpam + "_hit", 1);

			return SUCCESS;

		} else {
			creature->sendSystemMessage("@jedi_spam:fail_calm_target"); //"You fail to calm your target."
			CombatManager::instance()->broadcastCombatSpam(creature, targetCreature, NULL, 0, "cbt_spam", combatSpam + "_miss", 1);
		}

		return res;
	}
};

#endif //ANIMALCALMCOMMAND_H_
