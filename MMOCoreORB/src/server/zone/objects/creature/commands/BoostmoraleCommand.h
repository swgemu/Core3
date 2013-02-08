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

#ifndef BOOSTMORALECOMMAND_H_
#define BOOSTMORALECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/chat/ChatManager.h"
#include "SquadLeaderCommand.h"

class BoostmoraleCommand : public SquadLeaderCommand {
public:

	BoostmoraleCommand(const String& name, ZoneProcessServer* server)
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

		shoutCommand(player, group);

		int wounds[9] = {0,0,0,0,0,0,0,0,0};
		if (!getWounds(player, group, wounds))
			return GENERALERROR;

		if (!distributeWounds(player, group, wounds))
			return GENERALERROR;

		return SUCCESS;
	}

	bool getWounds(CreatureObject* leader, GroupObject* group, int* wounds) {
		if (group == NULL || leader == NULL || sizeof(wounds)/sizeof(wounds[0]) != 9)
			return false;

		for (int i = 0; i < group->getGroupSize(); i++) {

			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (member == NULL)
				continue;

			if (!member->isPlayerCreature())
				continue;

			CreatureObject* memberPlayer = cast<CreatureObject*>( member.get());
			Locker clocker(memberPlayer, leader);

			for (int j = 0; j < 9; j++) {
				wounds[j] = wounds[j] + memberPlayer->getWounds(j);
				memberPlayer->setWounds(j, 0);
			}
		}

		return true;
	}

	bool distributeWounds(CreatureObject* leader, GroupObject* group, int* wounds) {
		if (group == NULL || leader == NULL || sizeof(wounds)/sizeof(wounds[0]) != 9)
			return false;

		int groupSize = group->getGroupSize();

		for (int i = 0; i < groupSize; i++) {

			ManagedReference<SceneObject*> member = group->getGroupMember(i);

			if (!member->isPlayerCreature())
				continue;

			CreatureObject* memberPlayer = cast<CreatureObject*>( member.get());

			Locker clocker(memberPlayer, leader);

			sendCombatSpam(memberPlayer);

			for (int j = 0; j < 9; j++)
				memberPlayer->addWounds(j, (int) wounds[j] / groupSize);
		}

		return true;
	}

};

#endif //BOOSTMORALECOMMAND_H_
