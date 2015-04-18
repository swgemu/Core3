/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef HEALALLSELF2COMMAND_H_
#define HEALALLSELF2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "ForceHealQueueCommand.h"

class HealAllSelf2Command : public ForceHealQueueCommand {
public:

	HealAllSelf2Command(const String& name, ZoneProcessServer* server)
: ForceHealQueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if ((!creature->hasDamage(CreatureAttribute::HEALTH)) && (!creature->hasDamage(CreatureAttribute::ACTION)) && (!creature->hasDamage(CreatureAttribute::MIND))) {
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
		int healAmount = 1500;

		uint32 healthHealed = creature->healDamage(creature, CreatureAttribute::HEALTH, healAmount);
		uint32 actionHealed = creature->healDamage(creature, CreatureAttribute::ACTION, healAmount);
		uint32 mindHealed = creature->healDamage(creature, CreatureAttribute::MIND, healAmount);


		forceCostDeducted = MIN(((healthHealed + actionHealed + mindHealed) / 9.5), forceCost);


		// Send system message(s).

		if (healthHealed > 0){
			StringIdChatParameter message1("jedi_spam", "heal_self");
			message1.setDI(healthHealed);
			message1.setTO("@jedi_spam:health_damage");
			creature->sendSystemMessage(message1);
		}


		if (actionHealed > 0){
			StringIdChatParameter message2("jedi_spam", "heal_self");
			message2.setDI(actionHealed);
			message2.setTO("@jedi_spam:action_damage");
			creature->sendSystemMessage(message2);
		}

		if (mindHealed > 0){
			StringIdChatParameter message3("jedi_spam", "heal_self");
			message3.setDI(mindHealed);
			message3.setTO("@jedi_spam:mind_damage");
			creature->sendSystemMessage(message3);			
		}

		doAnimations(creature, creature);


		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCostDeducted);

		return SUCCESS;
	}


};

#endif //HEALALLSELF2COMMAND_H_
