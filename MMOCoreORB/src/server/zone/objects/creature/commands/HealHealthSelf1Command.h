/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHSELF1COMMAND_H_
#define HEALHEALTHSELF1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealHealthSelf1Command : public ForceHealQueueCommand {
public:

	HealHealthSelf1Command(const String& name, ZoneProcessServer* server)
		: ForceHealQueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if (!creature->hasDamage(CreatureAttribute::HEALTH)) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self"); // You have no damage of that type.
			return false;
		}
		
		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		if (!checkForceCost(creature)) {
			creature->sendSystemMessage("@jedi_spam:no_force_power");
			return GENERALERROR;
		}

		// At this point, the player has enough Force... Can they perform skill?

		if (!canPerformSkill(creature))
			return GENERALERROR;


		int forceCostDeducted = forceCost;

		// Lets see how much healing they are doing.
		int healAmount = 500;

		uint32 healthHealed = creature->healDamage(creature, CreatureAttribute::HEALTH, healAmount);


		forceCostDeducted = MIN((healthHealed / 7), forceCost);


		// Send system message(s).

		if (healthHealed > 0){
			StringIdChatParameter message1("jedi_spam", "heal_self");
			message1.setDI(healthHealed);
			message1.setTO("@jedi_spam:health_damage");
			creature->sendSystemMessage(message1);
		}

		doAnimations(creature, creature);


		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCostDeducted);

		return SUCCESS;
	}
};

#endif //HEALHEALTHSELF1COMMAND_H_
