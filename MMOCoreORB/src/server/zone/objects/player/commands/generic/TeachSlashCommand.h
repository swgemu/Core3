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

#ifndef TEACHSLASHCOMMAND_H_

#define TEACHSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
class TeachSlashCommand : public QueueCommand {
public:

	TeachSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doSlashCommand(PlayerCreature* player, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(player))
			return false;

		if (!checkInvalidPostures(player))
			return false;

		Zone* zone = player->getZone();
		if (zone == NULL)
			return false;

		/*

		uint64 targetid = packet->parseLong();

		SceneObject* object = zone->lookupObject(targetid);
		if (object == NULL) {
			player->sendSystemMessage("teaching", "no_target");
			return false;
		}

		Player* target = NULL;
		if (object->isPlayer())
			target = (Player*) object;
		else {
			player->sendSystemMessage("teaching", "no_target");
			return false;
		}

		StfParameter *params = new StfParameter();
		params->addTT(target->getFirstNameProper());

		if (player == target) {
			player->sendSystemMessage("teaching", "no_teach_self");
			delete params;
			return false;
		} else if (target->isDead() || target->isIncapacitated()) {
			player->sendSystemMessage("teaching", "student_dead", params);
			delete params;
			return false;
		} else if (!player->isInRange(target, 128)) {
			player->sendSystemMessage("teaching", "student_too_far_target", params);
			delete params;
			return false;
		} else if (!player->isInAGroup() || !target->isInAGroup()
				|| (player->getGroupObject() != target->getGroupObject())) {
			player->sendSystemMessage("teaching", "not_in_same_group");
			delete params;
			return false;
		} else if (target->getTeacher() != NULL) {
			player->sendSystemMessage("teaching", "student_has_offer_to_learn",
					params);
			delete params;
			return false;
		}

		delete params;

		UnicodeString opts;
		packet->parseUnicode(opts);

		String skillname = opts.toString();

		if (skillname.length() <= 0) {
			player->teachPlayer(target);
		}*/
		return true;
	}

};

#endif //TEACHSLASHCOMMAND_H_

