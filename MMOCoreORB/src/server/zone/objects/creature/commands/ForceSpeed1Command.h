/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FORCESPEED1COMMAND_H_
#define FORCESPEED1COMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"

class ForceSpeed1Command : public QueueCommand {
public:

	ForceSpeed1Command(const String& name, ZoneProcessServer* server)
	: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		uint32 buffcrc1 = BuffCRC::JEDI_FORCE_SPEED_1;
		uint32 buffcrc2 = BuffCRC::JEDI_FORCE_SPEED_2;

		if(creature->hasBuff(buffcrc1) || creature->hasBuff(buffcrc2)) {
			creature->sendSystemMessage("@jedi_spam:force_buff_present");
			return GENERALERROR;
		}


		// Force cost of skill.
		int forceCost = 150;

		//Check for and deduct Force cost.

		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();


		if (playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}

		playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		StringIdChatParameter startStringId("jedi_spam", "apply_forcespeed1");
		StringIdChatParameter endStringId("jedi_spam", "remove_forcespeed1");

		int duration = 180;

		ManagedReference<Buff*> buff = new Buff(creature, buffcrc1, duration, BuffType::JEDI);

		Locker locker(buff);

		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);
		buff->setSkillModifier("combat_haste", 15);

		creature->addBuff(buff);
		creature->playEffect("clienteffect/pl_force_speed_self.cef", "");

		return SUCCESS;
	}

};

#endif //FORCESPEED1COMMAND_H_
