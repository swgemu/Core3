/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALHEALTHWOUNDSELF1COMMAND_H_
#define HEALHEALTHWOUNDSELF1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealHealthWoundSelf1Command : public QueueCommand {
public:

	HealHealthWoundSelf1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if (!creature->getWounds(CreatureAttribute::HEALTH) && !creature->getWounds(CreatureAttribute::STRENGTH) && !creature->getWounds(CreatureAttribute::CONSTITUTION)) {
			creature->sendSystemMessage("@healing_response:healing_response_67"); // You have no wounds of that type.
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

		// At this point, the player has enough Force... Can they perform skill?

		if (!canPerformSkill(creature))
				return GENERALERROR;



		// Lets see how much healing they are doing.

		int healthHealed = creature->healWound(creature, CreatureAttribute::HEALTH, 250);
		int strengthHealed = creature->healWound(creature, CreatureAttribute::STRENGTH, 250);
		int constitutionHealed = creature->healWound(creature, CreatureAttribute::CONSTITUTION, 250);

			
		// Send system message(s).

		if (healthHealed > 0){
			StringIdChatParameter message1("jedi_spam", "heal_self");
			message1.setDI(healthHealed);
			message1.setTO("@jedi_spam:health_wounds");
			creature->sendSystemMessage(message1);
		}
			 
			
		if (strengthHealed > 0){
			StringIdChatParameter message2("jedi_spam", "heal_self");
			message2.setDI(strengthHealed);
			message2.setTO("@jedi_spam:strength_wounds");
			creature->sendSystemMessage(message2);
		}

		if (constitutionHealed > 0){
			StringIdChatParameter message3("jedi_spam", "heal_self");
			message3.setDI(constitutionHealed);
			message3.setTO("@jedi_spam:constitution_wounds");
			creature->sendSystemMessage(message3);			
		}
		
		int forceCost = 0;
		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= 65) {
				creature->sendSystemMessage("@jedi_spam:no_force_power");
				return GENERALERROR;
			}

		forceCost = MIN(((healthHealed + strengthHealed + constitutionHealed) / 7), 65);

			
		// Play client effect, and deduct Force Power.


		creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
		playerObject->setForcePower(playerObject->getForcePower() - forceCost);
			
		return SUCCESS;
		}

		return GENERALERROR;
	}


	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 3.0;
	}

};

#endif //HEALHEALTHWOUNDSELF1COMMAND_H_
