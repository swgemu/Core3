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

#ifndef BURSTRUNCOMMAND_H_
#define BURSTRUNCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/events/BurstRunNotifyAvailableEvent.h"

class BurstRunCommand : public QueueCommand {
public:

	BurstRunCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!checkBurstRun(creature))
			return GENERALERROR;


		uint32 crc = String("burstrun").hashCode();

		if (creature->hasBuff(crc)) {
			return GENERALERROR;
		}

		float burstRunMod = (float) creature->getSkillMod("burst_run");

		if (burstRunMod > 100.0f) {
			burstRunMod = 100.0f;
		}

		float hamCost = 100.0f;

		float efficiency = 1.0f - (burstRunMod / 100.0f);
		hamCost *= efficiency;
		int newHamCost = (int) hamCost;

		//Check for and deduct HAM cost.
		if (creature->getHAM(CreatureAttribute::HEALTH) <= newHamCost
				|| creature->getHAM(CreatureAttribute::ACTION) <= newHamCost
				|| creature->getHAM(CreatureAttribute::MIND) <= newHamCost) {
			creature->sendSystemMessage("combat_effects", "burst_run_wait"); //"You are too tired to Burst Run."

			return GENERALERROR;

		}

		creature->inflictDamage(creature, CreatureAttribute::HEALTH, newHamCost, true);
		creature->inflictDamage(creature, CreatureAttribute::ACTION, newHamCost, true);
		creature->inflictDamage(creature, CreatureAttribute::MIND, newHamCost, true);

		StringIdChatParameter startStringId("cbt_spam", "burstrun_start_single");
		StringIdChatParameter endStringId("cbt_spam", "burstrun_stop_single");

		int duration = 30;

		ManagedReference<Buff*> buff = new Buff(creature, crc, duration, BuffType::SKILL);
		buff->setSpeedMultiplierMod(1.822f);
		buff->setAccelerationMultiplierMod(1.822f);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		creature->addBuff(buff);

		creature->updateCooldownTimer("burstrun", (300 + duration) * 1000);

		Reference<BurstRunNotifyAvailableEvent*> task = new BurstRunNotifyAvailableEvent(creature);
		task->schedule((300 + duration) * 1000);


		return SUCCESS;
	}

	bool checkBurstRun(CreatureObject* creature) {
		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("cbt_spam", "no_burst"); //"You cannot burst-run while mounted on a creature or vehicle."
			return false;
		}

		Zone* zone = creature->getZone();

		if (creature->getZone() == NULL) {
			return false;
		}

		if (zone->getZoneID() == 39) {
			creature->sendSystemMessage("cbt_spam", "burst_run_space_dungeon"); //"The artificial gravity makes burst running impossible here."

			return false;
		}

		uint32 retreatCRC = String("retreat").hashCode();

		if (creature->getRunSpeed() > CreatureObject::DEFAULTRUNSPEED) {

			if (!creature->hasBuff(retreatCRC)) {

				creature->sendSystemMessage("combat_effects", "burst_run_no");

				return false;
			}
		}

		if (!creature->checkCooldownRecovery("burstrun")) {
			creature->sendSystemMessage("combat_effects", "burst_run_wait"); //You are too tired to Burst Run.

			return false;
		}

		return true;

	}

};

#endif //BURSTRUNCOMMAND_H_
