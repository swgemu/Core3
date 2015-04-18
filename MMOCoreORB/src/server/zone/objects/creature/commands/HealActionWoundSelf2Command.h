/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALACTIONWOUNDSELF2COMMAND_H_
#define HEALACTIONWOUNDSELF2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealActionWoundSelf2Command : public QueueCommand {
public:

	HealActionWoundSelf2Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if ((!creature->getWounds(CreatureAttribute::ACTION)) && (!creature->getWounds(CreatureAttribute::QUICKNESS)) && (!creature->getWounds(CreatureAttribute::STAMINA))) {
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

		int actionHealed = creature->healWound(creature, CreatureAttribute::ACTION, 350);
		int quicknessHealed = creature->healWound(creature, CreatureAttribute::QUICKNESS, 350);
		int staminaHealed = creature->healWound(creature, CreatureAttribute::STAMINA, 350);

			
		// Send system message(s).

		if (actionHealed > 0){
			StringIdChatParameter message1("jedi_spam", "heal_self");
			message1.setDI(actionHealed);
			message1.setTO("@jedi_spam:action_wounds");
			creature->sendSystemMessage(message1);
		}


		if (quicknessHealed > 0){
			StringIdChatParameter message2("jedi_spam", "heal_self");
			message2.setDI(quicknessHealed);
			message2.setTO("@jedi_spam:quickness_wounds");
			creature->sendSystemMessage(message2);
		}

		if (staminaHealed > 0){
			StringIdChatParameter message3("jedi_spam", "heal_self");
			message3.setDI(staminaHealed);
			message3.setTO("@jedi_spam:stamina_wounds");
			creature->sendSystemMessage(message3);			
		}
		
		int forceCost = 0;
		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= 100) {
				creature->sendSystemMessage("@jedi_spam:no_force_power");
				return GENERALERROR;
			}

		forceCost = MIN(((actionHealed + quicknessHealed + staminaHealed) / 15), 100);

			
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

#endif //HEALACTIONWOUNDSELF2COMMAND_H_
