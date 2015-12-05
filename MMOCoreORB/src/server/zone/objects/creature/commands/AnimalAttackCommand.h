/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ANIMALATTACKCOMMAND_H_
#define ANIMALATTACKCOMMAND_H_

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

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

			Locker clocker(targetCreature, creature);

			// Commence controlling action...

			CombatManager::instance()->forcePeace(targetCreature);

			TangibleObject* defender = cast<TangibleObject*>(creature->getMainDefender());

			if (defender == NULL || defender == targetCreature) {
				creature->sendSystemMessage("@jedi_spam:animal_attack_fail"); //"You fail to enrage your target."
				return GENERALERROR;
			}

			{
				Locker clocker (defender, creature);
				if (!defender->isAttackableBy(targetCreature)) {
					return INVALIDTARGET;
				}
			}

			targetCreature->setDefender(defender);

			creature->doCombatAnimation(targetCreature, STRING_HASHCODE("mind_trick_1"), 1, 0);
			creature->sendSystemMessage("@jedi_spam:animal_attack_success"); //"You successfully enrage your target."

			return SUCCESS;
		}
		else {
					creature->sendSystemMessage("@jedi_spam:animal_attack_fail"); //"You fail to enrage your target."
		}
		return res;
	}
};

#endif //ANIMALATTACKCOMMAND_H_