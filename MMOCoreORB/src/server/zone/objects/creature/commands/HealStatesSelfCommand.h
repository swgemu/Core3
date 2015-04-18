/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HEALSTATESSELFCOMMAND_H_
#define HEALSTATESSELFCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HealStatesSelfCommand : public QueueCommand {
public:

	HealStatesSelfCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	bool canPerformSkill(CreatureObject* creature) const {
		if (!creature->hasState(CreatureState::STUNNED) && !creature->hasState(CreatureState::DIZZY) && !creature->hasState(CreatureState::INTIMIDATED) && !creature->hasState(CreatureState::BLINDED)) {
			creature->sendSystemMessage("@healing_response:healing_response_72"); // You have no states of that type.		
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

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject != NULL) {
			if (playerObject->getForcePower() <= 50) {
				creature->sendSystemMessage("@jedi_spam:no_force_power");
				return GENERALERROR;
			}

			// At this point, the player has enough Force... Can they perform skill?

			if (!canPerformSkill(creature))
				return GENERALERROR;


			int forceCost = 50; // Static amount.

			if (creature->hasState(CreatureState::STUNNED))
			creature->removeStateBuff(CreatureState::STUNNED);

			if (creature->hasState(CreatureState::DIZZY))
			creature->removeStateBuff(CreatureState::DIZZY);

			if (creature->hasState(CreatureState::BLINDED))
			creature->removeStateBuff(CreatureState::BLINDED);

			if (creature->hasState(CreatureState::INTIMIDATED))
			creature->removeStateBuff(CreatureState::INTIMIDATED);

			// Play client effect, and deduct Force Power.

			creature->playEffect("clienteffect/pl_force_heal_self.cef", "");
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		return SUCCESS;
		}

		return GENERALERROR;
	}


	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return defaultTime * 2.0;
	}

};

#endif //HEALSTATESSELFCOMMAND_H_
