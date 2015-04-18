/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCERESISTBLEEDINGCOMMAND_H_
#define FORCERESISTBLEEDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class ForceResistBleedingCommand : public QueueCommand {
public:

	ForceResistBleedingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		uint32 buffcrc = BuffCRC::JEDI_RESIST_BLEEDING;

		if(creature->hasBuff(buffcrc)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}


		// Force cost of skill.
		int forceCost = 250;


		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forceresistbleeding");
		StringIdChatParameter endStringId("jedi_spam", "remove_forceresistbleeding");

		int duration = 900;

		ManagedReference<Buff*> buff = new Buff(creature, buffcrc, duration, BuffType::JEDI);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("resistance_bleeding", 25);
		buff->setSkillModifier("absorption_bleeding", 25);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_resist_bleeding_self.cef", "");

		return SUCCESS;
	}

};

#endif //FORCERESISTBLEEDINGCOMMAND_H_
