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

#ifndef RETREATCOMMAND_H_
#define RETREATCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class RetreatCommand : public SquadLeaderCommand {
public:

	RetreatCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<CreatureObject*> player = creature;
		ManagedReference<GroupObject*> group = player->getGroup();

		if (!checkGroupLeader(player, group))
			return GENERALERROR;

		float burstRunMod = (float) player->getSkillMod("group_burst_run");
		int hamCost = (int) (100.0f * (1.0f - (burstRunMod / 100.0f))) * calculateGroupModifier(group);

		if (!inflictHAM(player, 0, hamCost, hamCost))
			return GENERALERROR;

		shoutCommand(player, group);

		for (int i = 1; i < group->getGroupSize(); ++i) {
			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (!member->isPlayerCreature())
				continue;

			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			Locker clocker(memberPlayer, player);

			sendCombatSpam(memberPlayer);
			doRetreat(memberPlayer);
		}

		return SUCCESS;
	}

	bool checkRetreat(CreatureObject* creature) {

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("cbt_spam", "no_burst"); //"You cannot burst-run while mounted on a creature or vehicle."
			return false;
		}

		Zone* zone = creature->getZone();

		if (creature->getZone() == NULL) {
			return false;
		}

		if (zone->getZoneName() == "dungeon1") {
			creature->sendSystemMessage("cbt_spam", "burst_run_space_dungeon"); //"The artificial gravity makes burst running impossible here."

			return false;
		}

		uint32 crc = String("burstrun").hashCode();

		if ((creature->getRunSpeed() > CreatureObjectImplementation::DEFAULTRUNSPEED) && (!creature->hasBuff(crc))) {
			creature->sendSystemMessage("combat_effects", "burst_run_no");

			return false;
		}

		if (!creature->checkCooldownRecovery("retreat")) {
			// is there a message for retreat?
			creature->sendSystemMessage("combat_effects", "burst_run_no");

			return false;
		}

		return true;
	}

	void doRetreat(CreatureObject* player) {
		if (player == NULL)
			return;

		if (!checkRetreat(player) || player->hasBuff(actionCRC))
			return;

		float runMod = (float) player->getSkillMod("burst_run");

		if (runMod > 100.0f)
			runMod = 100.0f;

		int newHamCost = (int) (100.0f * (1.0f - (runMod / 100.0f)));

		if (!inflictHAM(player, newHamCost, newHamCost, newHamCost)) {
			player->sendSystemMessage("combat_effects", "burst_run_wait");
			return;
		}

		StringIdChatParameter startStringId("cbt_spam", "burstrun_start_single");
		StringIdChatParameter endStringId("cbt_spam", "burstrun_stop_single");

		int duration = 30;

		ManagedReference<Buff*> buff = new Buff(player, actionCRC, duration, BuffType::SKILL);

		buff->setSpeedMultiplierMod(1.822f);
		buff->setAccelerationMultiplierMod(1.822f);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		player->addBuff(buff);

		player->updateCooldownTimer("retreat", (300 + duration) * 1000);

		Reference<BurstRunNotifyAvailableEvent*> task = new BurstRunNotifyAvailableEvent(player);
		task->schedule((300 + duration) * 1000);
	}

};

#endif //RETREATCOMMAND_H_
