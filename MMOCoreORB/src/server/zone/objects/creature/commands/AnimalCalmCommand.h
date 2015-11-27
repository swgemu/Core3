/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALCALMCOMMAND_H_
#define ANIMALCALMCOMMAND_H_

#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/Creature.h"

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

		if (targetObject == NULL || !targetObject->isCreature()) {
			creature->sendSystemMessage("@jedi_spam:fail_calm_target"); //"You fail to calm your target."
			return INVALIDTARGET;
		} else {

		// Commence calming action...

		ManagedReference<Creature*> creatureTarget = targetObject.castTo<Creature*>();

		Locker clocker(creatureTarget, creature);

		CombatManager::instance()->forcePeace(creatureTarget);

		creature->doCombatAnimation(creatureTarget, STRING_HASHCODE("mind_trick_1"), 1, 0);
		creature->sendSystemMessage("@jedi_spam:calm_target"); //"You successfully calm down your target."

		}

		return SUCCESS;
	}

};

#endif //ANIMALCALMCOMMAND_H_
