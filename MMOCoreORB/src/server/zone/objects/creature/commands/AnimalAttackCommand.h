/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALATTACKCOMMAND_H_
#define ANIMALATTACKCOMMAND_H_

//#include "server/zone/objects/scene/SceneObject.h"
//#include "server/zone/objects/tangible/TangibleObject.h"
#include "ForcePowersQueueCommand.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/managers/combat/CombatManager.h"

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

		Creature* targetCreature = cast<Creature*>(targetObject.get());

		if (targetCreature == NULL)
			return INVALIDTARGET;

		// Commence controlling action...

		TangibleObject* defender = cast<TangibleObject*>(creature->getMainDefender());

		if (defender == NULL || defender == targetCreature) {
			creature->sendSystemMessage("@jedi_spam:animal_attack_fail"); //"You fail to enrage your target."
			return GENERALERROR;
		}

		{
			Locker clocker (defender, creature);
			if (!defender->isAttackableBy(targetCreature)) {
				creature->sendSystemMessage("@jedi_spam:animal_attack_fail"); //"You fail to enrage your target."
				return GENERALERROR;
			}
		}

		Locker clocker(targetCreature, creature);

		CombatManager::instance()->forcePeace(targetCreature);
		targetCreature->setDefender(defender);

		creature->sendSystemMessage("@jedi_spam:animal_attack_success"); //"You successfully enrage your target."

		return SUCCESS;
	}

};

#endif //ANIMALATTACKCOMMAND_H_
