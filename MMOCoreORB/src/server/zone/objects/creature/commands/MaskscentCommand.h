/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MASKSCENTCOMMAND_H_
#define MASKSCENTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MaskscentCommand : public QueueCommand {
public:

	MaskscentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!checkMaskScent(creature))
			return GENERALERROR;


		uint32 crc = STRING_HASHCODE("skill_buff_mask_scent_self");

		if (creature->hasBuff(crc)) {
			creature->sendSystemMessage("@skl_use:sys_scentmask_already"); // You are already masking your scent.
			return GENERALERROR;
		}

		StringIdChatParameter startStringId("skl_use", "sys_scentmask_start"); // Your natural scent has been masked from creatures.
		StringIdChatParameter endStringId("skl_use", "sys_scentmask_stop"); // Your masked scent has worn off.


		int maskScentMod = creature->getSkillMod("mask_scent");
		int cdReduction = ((float)(maskScentMod / 100.0f)) * 45;
		int duration = 60 + (((float)(maskScentMod / 100.0f)) * 200);

		ManagedReference<Buff*> buff = new Buff(creature, crc, duration, BuffType::SKILL);

		Locker locker(buff);

		buff->addState(CreatureState::MASKSCENT);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		creature->addBuff(buff);

		int timer = (60 - cdReduction) * 1000;
		if (timer > 0) {
			creature->updateCooldownTimer("skill_buff_mask_scent_self", timer);
		}

		return SUCCESS;
	}

	bool checkMaskScent(CreatureObject* creature) const {

		if(creature->getSkillMod("mask_scent") <= 0) {
			creature->sendSystemMessage("@skl_use:sys_scentmask_noskill"); // You might be a very clean person, but you lack the skill to mask your scent from creatures.
			return false;
		}

		if(creature->hasBuff(STRING_HASHCODE("skill_buff_mask_scent")) || creature->getSkillModFromBuffs("private_conceal") > 0) {
			creature->sendSystemMessage("@skl_use:sys_scentmask_concealed"); // You can't mask your scent while you are concealed.
			return false;
		}

		if(creature->getOptionsBitmask() & CreatureState::MASKSCENT) {
			creature->sendSystemMessage("@skl_use:sys_scentmask_already"); // You are already masking your scent.
			return false;
		}

		if (!creature->checkCooldownRecovery("skill_buff_mask_scent_self")) {
			StringIdChatParameter waitTime("@skl_use:sys_scentmask_delay"); // You must wait %DI seconds to mask your scent again.
			int timeLeft = (creature->getCooldownTime("skill_buff_mask_scent_self")->getMiliTime() / 1000) - System::getTime();
			waitTime.setDI(timeLeft);

			creature->sendSystemMessage(waitTime);

			return false;
		}

		Zone* zone = creature->getZone();
		if (creature->getZone() == NULL || creature->isInCombat()) {
			creature->sendSystemMessage("@skl_use:sys_scentmask_fail"); // You cannot mask your scent now.
			return false;
		}

		return true;

	}

};

#endif //MASKSCENTCOMMAND_H_
