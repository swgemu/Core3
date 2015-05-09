/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VITALIZECOMMAND_H_
#define VITALIZECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class VitalizeCommand : public QueueCommand {
public:

	VitalizeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (creature->getSpecies() != CreatureObject::ZABRAK)
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		// Check to see if "innate_vitalize" Cooldown isPast();
		if (!player->checkCooldownRecovery("innate_vitalize")) {
			StringIdChatParameter stringId;

			Time* cdTime = player->getCooldownTime("innate_vitalize");

			// Returns -time. Multiple by -1 to return positive.
			int timeLeft = floor((float)cdTime->miliDifference() / 1000) *-1;

			stringId.setStringId("@innate:vit_wait"); // You are still recovering from you last vitalization. Command available in %DI seconds.
			stringId.setDI(timeLeft);

			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		uint32 buffcrc = BuffCRC::INNATE_BUFF_VITALIZE; // 0x477D7E4

		StringIdChatParameter startMsg;
		startMsg.setStringId("@innate:vit_active"); // You feel adrenaline pour into your bloodstream as you become more vitalized.

		ManagedReference<Buff*> buff = new Buff(player, buffcrc, 600, BuffType::INNATE); // Duration of 10min

		Locker locker(buff);

		buff->setAttributeModifier(CreatureAttribute::HEALTH, 50);
		buff->setAttributeModifier(CreatureAttribute::ACTION, 50);
		buff->setAttributeModifier(CreatureAttribute::MIND, 50);
		buff->setStartMessage(startMsg);

		player->addBuff(buff);
		player->showFlyText("combat_effects", "innate_vitalize", 0, 255, 0); // +Vitalize+
		player->addCooldown("innate_vitalize", 3600 * 1000);

		return SUCCESS;
	}

};

#endif //VITALIZECOMMAND_H_
