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

#ifndef FORCERUNSELFSKILL_H_
#define FORCERUNSELFSKILL_H_

#include "../../SelfSkill.h"
#include "../../../buffs/Buff.h"
#include "../../../../../packets.h"
#include "../../../events/CreatureForceRunOverEvent.h"

class ForceRunSelfSkill : public SelfSkill {

public:

	float speed;
	float acceleration;
	int slope;
	int duration;

	int forceCost;
	uint32 buffState;

	 ForceRunSelfSkill(const String& name, const String& effect, float sp, float acc, int sl, int du, ZoneProcessServerImplementation* serv) : SelfSkill(name, effect.toCharArray(), SELF, serv) {
		 speed = sp;
		 acceleration = acc;
		 slope = sl;
		 duration = du;

		 if (name == "forcerun2")
			 buffState = BuffCRC::JEDI_FORCE_RUN_2;
		 else if (name == "forcerun3")
			 buffState = BuffCRC::JEDI_FORCE_RUN_3;
		 else
			 buffState = BuffCRC::JEDI_FORCE_RUN_1;
	 }

	void doSkill(CreatureObject* creature, String& modifier) {
		// Updates
		float new_speed = creature->getSpeed() + speed;
		float new_acceleration = creature->getAcceleration() + acceleration;
		creature->addSkillMod("slope_move", slope, true);

		// Implement Speed
		creature->updateSpeed(new_speed, new_acceleration); // also update terrain nav

		// Msg to Client
		creature->sendSystemMessage("cbt_spam", "forcerun_start_single");

		// Buff Icon
		creature->addBuff(buffState, 120.0f);
		creature->addQueuedState(buffState);

		// Timer
		Event* e = new CreatureForceRunOverEvent(creature, speed, acceleration, slope, duration, buffState);
		server->addEvent(e);

		// Effect
		doAnimations(creature);
	}

	float calculateSpeed(CreatureObject* creature) {
		return 1.0;
	}

	bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*) creature;

		if (player->hasQueuedState(BuffCRC::JEDI_FORCE_RUN_1) ||
			player->hasQueuedState(BuffCRC::JEDI_FORCE_RUN_2) ||
			player->hasQueuedState(BuffCRC::JEDI_FORCE_RUN_3)) {
			player->sendSystemMessage("You are already force running.");

			return false;
		}

		if (
			player->hasQueuedState(BuffCRC::JEDI_AVOID_INCAPACITATION_1) ||
			player->hasQueuedState(BuffCRC::JEDI_AVOID_INCAPACITATION) ||
			player->hasQueuedState(BuffCRC::JEDI_AVOID_INCAPACITATION_4) ||
			player->hasQueuedState(BuffCRC::JEDI_AVOID_INCAPACITATION_2) ||
			player->hasQueuedState(BuffCRC::JEDI_AVOID_INCAPACITATION_3) ||
			player->isDizzied()) {
			//UnicodeString msg = UnicodeString("You are incapable of such speed right now.");
			player->sendSystemMessage("You are incapable of such speed right now.");

			return false;
		}

		return player->changeForcePowerBar(-forceCost);
	}

	void doAnimations(CreatureObject* creature) {
		if (!effectName.isEmpty())
			creature->playEffect(effectName, "");

		if (!secondaryAnim.isEmpty())
			creature->doAnimation(secondaryAnim);
	}

	void setForceCost(int cost) {
		forceCost = cost;
	}
};

#endif /*FORCERUNSELFSKILL_H_*/
