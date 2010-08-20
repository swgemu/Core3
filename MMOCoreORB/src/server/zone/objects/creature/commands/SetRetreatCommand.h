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

#ifndef SETRETREATCOMMAND_H_
#define SETRETREATCOMMAND_H_

#include "../../scene/SceneObject.h"

class SetRetreatCommand : public QueueCommand {
public:

	SetRetreatCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!checkRetreat(creature))
			return GENERALERROR;

		uint32 crc = String("burstrun").hashCode();

		if (creature->hasBuff(crc)) {
			return GENERALERROR;
		}

		uint32 retreatCRC = String("retreat").hashCode();

		if (creature->hasBuff(retreatCRC)) {
			return GENERALERROR;
		}

		float burstRunMod = (float) creature->getSkillMod("burst_run");

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> leaderObject = group->getLeader();

		if (leaderObject == NULL || !leaderObject->isPlayerCreature())
			return GENERALERROR;

		PlayerCreature* leader = (PlayerCreature*) leaderObject.get();

		burstRunMod += (float) leader->getSkillMod("group_burst_run");

		if (burstRunMod > 100.0f) {
			burstRunMod = 100.0f;
		}

		ParameterizedStringId startStringId("cbt_spam", "burstrun_start_single");
		ParameterizedStringId endStringId("cbt_spam", "burstrun_stop_single");

		int duration = 30;

		ManagedReference<Buff*> buff = new Buff(creature, retreatCRC, duration, BuffType::SKILL);

		buff->setSpeedModifier(4.424f);
		buff->setStartMessage(startStringId);
		buff->setEndMessage(endStringId);

		creature->addBuff(buff);

		creature->updateCooldownTimer("retreat", (300 + duration) * 1000);

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

		if (zone->getZoneID() == 39) {
			creature->sendSystemMessage("cbt_spam", "burst_run_space_dungeon"); //"The artificial gravity makes burst running impossible here."

			return false;
		}

		if (creature->getRunSpeed() > CreatureObject::DEFAULTRUNSPEED) {
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

};

#endif //SETRETREATCOMMAND_H_
