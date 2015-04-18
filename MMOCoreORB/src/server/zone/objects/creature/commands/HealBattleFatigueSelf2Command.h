/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALBATTLEFATIGUESELF2COMMAND_H_
#define HEALBATTLEFATIGUESELF2COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealBattleFatigueSelf2Command : public QueueCommand {
public:

	HealBattleFatigueSelf2Command(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {

		if (creature->getShockWounds() == 0) {
			creature->sendSystemMessage("@jedi_spam:no_damage_heal_self"); // You have no damage of that type.
			return false;
		}

		return true;
	}

	int healBattleFatigue(CreatureObject* creature, int damage) const {

		int currentValue = creature->getShockWounds();

		int healedValue = MIN(currentValue, damage);

		creature->addShockWounds(-healedValue, true, false);

		return healedValue;

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		if (isWearingArmor(creature))
			return NOJEDIARMOR;

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= 150) {
				creature->sendSystemMessage("@jedi_spam:no_force_power");
				return GENERALERROR;
			}

			// At this point, the player has enough Force... Can they perform skill?

			if (!canPerformSkill(creature))
				return GENERALERROR;


			int forceCost = 0;

			// Lets see how much healing they are doing.
			uint32 bfHealed = healBattleFatigue(creature, 300);



			// Send system message(s).


			if (bfHealed > 0){
				StringIdChatParameter message2("jedi_spam", "heal_self");
				message2.setDI(bfHealed);
				message2.setTO("@jedi_spam:battle_fatigue");
				creature->sendSystemMessage(message2);
			}


			// Play client effect, and deduct Force Power.

			forceCost = MIN((bfHealed / 2), 150);

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

#endif //HEALBATTLEFATIGUESELF2COMMAND_H_
