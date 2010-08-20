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

#ifndef STEADYAIMCOMMAND_H_
#define STEADYAIMCOMMAND_H_

#include "../../scene/SceneObject.h"

class SteadyaimCommand : public QueueCommand {
public:

	SteadyaimCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (creature->isPlayerCreature()) {

			ManagedReference<PlayerCreature*> player = (PlayerCreature*)creature;
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group == NULL) {
				player->sendSystemMessage("@error_message:not_grouped");
			}
			else if (group->getLeader() == player) {

				float retreatMod = (float) creature->getSkillMod("steadyaim");
				float groupMod = (float) group->getGroupSize() / 10.0f;

				if (groupMod < 1.0)
					groupMod += 1.0f;

				int hamCost = (int) (100.0f * (1.0f - (retreatMod / 100.0f))) * groupMod;

				creature->inflictDamage(creature, CreatureAttribute::HEALTH, hamCost, true);
				creature->inflictDamage(creature, CreatureAttribute::ACTION, hamCost, true);
				creature->inflictDamage(creature, CreatureAttribute::MIND, hamCost, true);

				String action = "setsteadyaim";
				uint64 actionCRC = action.hashCode();

				for (int i = 0; i < group->getGroupSize(); i++) {

					ManagedReference<SceneObject*> member = group->getGroupMember(i);

					if (member->isPlayerCreature()) {

						PlayerCreature* memberPlayer = (PlayerCreature*) member.get();

						if (!arguments.toString().isEmpty())
							memberPlayer->sendSystemMessage("Squad Leader " + player->getFirstName() + ": " + arguments.toString());
						else
							memberPlayer->sendSystemMessage("@cbt_spam:steadyaim_buff");

						Locker clocker(memberPlayer, creature);
						memberPlayer->enqueueCommand(actionCRC, 0, 0, "");
					}
				}

			} else {
				player->sendSystemMessage("@error_message:not_group_leader");
			}
		}

		return SUCCESS;
	}

};

#endif //STEADYAIMCOMMAND_H_
