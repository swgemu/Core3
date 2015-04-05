/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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


		uint32 crc = String("skill_buff_mask_scent_self").hashCode();

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

		if(creature->hasBuff(String("skill_buff_mask_scent").hashCode()) || creature->getSkillModFromBuffs("private_conceal") > 0) {
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
