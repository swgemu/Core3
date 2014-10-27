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

#ifndef RALLYCOMMAND_H_
#define RALLYCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "SquadLeaderCommand.h"

class RallyCommand : public SquadLeaderCommand {
public:

	RallyCommand(const String& name, ZoneProcessServer* server)
		: SquadLeaderCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;			
	
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<GroupObject*> group = player->getGroup();

		if (!checkGroupLeader(player, group))
			return GENERALERROR;

		int hamCost = (int) (100.0f * calculateGroupModifier(group));

		int healthCost = creature->calculateCostAdjustment(CreatureAttribute::STRENGTH, hamCost);
		int actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, hamCost);
		int mindCost = creature->calculateCostAdjustment(CreatureAttribute::FOCUS, hamCost);

		if (!inflictHAM(player, healthCost, actionCost, mindCost))
			return GENERALERROR;

		int chance = 75;

		if (System::random(100) > chance)
			player->sendSystemMessage("@cbt_spam:rally_fail_single");
		else
			if (!doRally(player, group))
				return GENERALERROR;

		return SUCCESS;
	}

	bool doRally(CreatureObject* leader, GroupObject* group) {
		if (leader == NULL || group == NULL)
			return false;

		int amount = 25;
		int duration = 30;

		sendCombatSpam(leader);

		for (int i = 0; i < group->getGroupSize(); i++) {

			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (!member->isPlayerCreature() || member == NULL || member->getZone() != leader->getZone())
				continue;

			ManagedReference<CreatureObject*> memberPlayer = cast<CreatureObject*>( member.get());

			if (!isValidGroupAbilityTarget(leader, memberPlayer))
				continue;

			Locker clocker(memberPlayer, leader);

			ManagedReference<Buff*> buff = new Buff(memberPlayer, actionCRC, duration, BuffType::SKILL);

			ManagedReference<WeaponObject*> weapon = memberPlayer->getWeapon();

			if (weapon != NULL) {
				if (!weapon->getCreatureAccuracyModifiers()->isEmpty()) {
					String skillCRC = weapon->getCreatureAccuracyModifiers()->get(0);

					buff->setSkillModifier(skillCRC, amount);
				}
			}

			buff->setSkillModifier("ranged_defense", amount);
			buff->setSkillModifier("melee_defense", amount);

			memberPlayer->addBuff(buff);

			memberPlayer->setRalliedState(duration);
		}

//		What is this used for?		
//		leader->updateCooldownTimer("rally", (duration + 30) * 1000);

		return true;
	}

};

#endif //RALLYCOMMAND_H_
