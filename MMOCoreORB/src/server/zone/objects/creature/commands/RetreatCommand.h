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

	bool checkRetreat(CreatureObject* creature) const {
		if (creature->isRidingMount()) {
			creature->sendSystemMessage("@cbt_spam:no_burst"); // You cannot burst-run while mounted on a creature or vehicle.
			return false;
		}

		Zone* zone = creature->getZone();		

		if (creature->getZone() == NULL) {
			return false;
		}

		if (zone->getZoneName() == "dungeon1") {
			creature->sendSystemMessage("@combat_effects:burst_run_space_dungeon"); //The artificial gravity makes burst running impossible here.
			return false;
		}

		uint32 burstCRC = String("burstrun").hashCode();
		uint32 forceRun1CRC = BuffCRC::JEDI_FORCE_RUN_1;
		uint32 forceRun2CRC = BuffCRC::JEDI_FORCE_RUN_2;
		uint32 forceRun3CRC = BuffCRC::JEDI_FORCE_RUN_3;

		if (creature->hasBuff(burstCRC) || creature->hasBuff(forceRun1CRC) || creature->hasBuff(forceRun2CRC) || creature->hasBuff(forceRun3CRC)) {
			creature->sendSystemMessage("@combat_effects:burst_run_no"); //You cannot burst run right now.
			return false;
		}

		if (!creature->checkCooldownRecovery("retreat")) {
			creature->sendSystemMessage("@combat_effects:burst_run_no"); //You cannot burst run right now.
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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

		float groupBurstRunMod = (float) player->getSkillMod("group_burst_run");
		int hamCost = (int) (100.0f * (1.0f - (groupBurstRunMod / 100.0f))) * calculateGroupModifier(group);

		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, 0, actionCost, mindCost))
			return GENERALERROR;

		for (int i = 1; i < group->getGroupSize(); ++i) {
			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (member == NULL || !member->isPlayerCreature() || member->getZone() != creature->getZone())
				continue;
			
			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			if (!isValidGroupAbilityTarget(creature, memberPlayer))
				continue;

			Locker clocker(memberPlayer, player);

			sendCombatSpam(memberPlayer);
			doRetreat(memberPlayer);

			checkForTef(player, memberPlayer);
		}

		if (player->isPlayerCreature() && player->getPlayerObject()->getCommandMessageString(String("retreat").hashCode()).isEmpty()==false && creature->checkCooldownRecovery("command_message")) {
			UnicodeString shout(player->getPlayerObject()->getCommandMessageString(String("retreat").hashCode()));
 	 	 	server->getChatManager()->broadcastMessage(player, shout, 0, 0, 80);
 	 	 	creature->updateCooldownTimer("command_message", 30 * 1000);
		}

		return SUCCESS;
	}


	void doRetreat(CreatureObject* player) const {
		if (player == NULL)
			return;

		if (!checkRetreat(player))
			return;

		uint32 actionCRC = String("retreat").hashCode();

		if (player->hasBuff(actionCRC)) {
			return;
		}

		float groupRunMod = (float) player->getSkillMod("group_burst_run");

		if (groupRunMod > 100.0f)
			groupRunMod = 100.0f;

		StringIdChatParameter startStringId("cbt_spam", "burstrun_start_single");
		StringIdChatParameter endStringId("cbt_spam", "burstrun_stop_single");

		int duration = 30;

		ManagedReference<Buff*> buff = new Buff(player, actionCRC, duration, BuffType::SKILL);

		buff->setSpeedMultiplierMod(1.822f);
		buff->setAccelerationMultiplierMod(1.822f);
		buff->setStartMessage(startStringId);;
		buff->setEndMessage(endStringId);		

		player->addBuff(buff);

		player->updateCooldownTimer("retreat", 30000);

	}

};

#endif //RETREATCOMMAND_H_
