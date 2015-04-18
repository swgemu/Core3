/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALMINDWOUNDSELF1COMMAND_H
#define HEALMINDWOUNDSELF1COMMAND_H

#include "server/zone/objects/scene/SceneObject.h"

class HealMindWoundSelf1Command : public QueueCommand {
public:

	HealMindWoundSelf1Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if (!creature->getWounds(CreatureAttribute::MIND) && !creature->getWounds(CreatureAttribute::FOCUS) && !creature->getWounds(CreatureAttribute::WILLPOWER)) {
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

		int mindHealed = creature->healWound(creature, CreatureAttribute::MIND, 250);
		int focusHealed = creature->healWound(creature, CreatureAttribute::FOCUS, 250);
		int willpowerHealed = creature->healWound(creature, CreatureAttribute::WILLPOWER, 250);

			
		// Send system message(s).

		if (mindHealed > 0){
			StringIdChatParameter message1("jedi_spam", "heal_self");
			message1.setDI(mindHealed);
			message1.setTO("@jedi_spam:mind_wounds");
			creature->sendSystemMessage(message1);
		}

			
		if (focusHealed > 0){
			StringIdChatParameter message2("jedi_spam", "heal_self");
			message2.setDI(focusHealed);
			message2.setTO("@jedi_spam:focus_wounds");
			creature->sendSystemMessage(message2);
		}

			
		if (willpowerHealed > 0){
			StringIdChatParameter message3("jedi_spam", "heal_self");
			message3.setDI(willpowerHealed);
			message3.setTO("@jedi_spam:willpower_wounds");
			creature->sendSystemMessage(message3);
		}
		
		int forceCost = 0;
		
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= 65) {
				creature->sendSystemMessage("@jedi_spam:no_force_power");
				return GENERALERROR;
			}

		forceCost = MIN(((mindHealed + focusHealed + willpowerHealed) / 7), 65);

			
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

#endif //HEALMINDWOUNDSELF1COMMAND_H
