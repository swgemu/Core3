/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REGENERATIONCOMMAND_H_
#define REGENERATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RegenerationCommand : public QueueCommand {
public:

	RegenerationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (creature->getSpecies() != CreatureObject::TRANDOSHAN) 
			return GENERALERROR;		

		CreatureObject* player = cast<CreatureObject*>(creature);

		uint32 buffcrc = BuffCRC::INNATE_BUFF_REGENERATION; // 0xD1514A47

		// Check to see if "innate_regeneration" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_regeneration")) {
			StringIdChatParameter stringId;

			Time* cdTime = player->getCooldownTime("innate_regeneration");

			// Returns -time. Multiple by -1 to return positive.
			int timeLeft = floor((float)cdTime->miliDifference() / 1000)*-1;

			stringId.setStringId("@innate:regen_wait"); // You are still recovering from your last regeneration. Command available in %DI seconds.
			stringId.setDI(timeLeft);
			player->sendSystemMessage(stringId);
			return GENERALERROR;

		}

		// Grab the SkillMod for regeneration.
		int regenMod = player->getSkillMod("private_innate_regeneration");

		// Base modifier of 175, multiplied by the skilMod of regenerate (buff food can increase this).
		int regenValue = 175 * regenMod;

		ManagedReference<Buff*> regenBuff = new Buff(player, buffcrc, 300, BuffType::INNATE); // Duration of 5min

		regenBuff->setAttributeModifier(CreatureAttribute::CONSTITUTION, regenValue);

		StringIdChatParameter startMsg;
		startMsg.setStringId("@innate:regen_active"); // You feel your blood course through your veins as your body begins to regenerate.

		regenBuff->setStartMessage(startMsg);

		player->addBuff(regenBuff);
		player->showFlyText("combat_effects", "innate_regeneration", 0, 255, 0); // +Regeneration+
		player->addCooldown("innate_regeneration", 3600 * 1000); // 1 hour reuse time.

		return SUCCESS;
	}

};

#endif //REGENERATIONCOMMAND_H_
