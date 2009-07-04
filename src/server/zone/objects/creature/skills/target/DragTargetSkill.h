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

#ifndef DRAGTARGETSKILL_H_
#define DRAGTARGETSKILL_H_

#include "../TargetSkill.h"

#include "../../../../managers/player/PlayerManager.h"

class DragTargetSkill : public TargetSkill {

protected:

	float maxRange;
	float maxMovement;
	float speed;
	bool needsConsent;

public:
	DragTargetSkill(const String& name, const char* effect, ZoneProcessServerImplementation* serv) : TargetSkill(name, effect, DRAG, serv) {
		//Defaults, replaced with lua values.
		maxRange = 20.0f;
		maxMovement = 5.0f;
		speed = 0.0f;
		needsConsent = true;
	}


	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		Player* player;
		Player* targetPlayer;

		if (!creature->isPlayer()) {
			return 0;
		} else {
			player = (Player*)creature;
		}

		//Determine if the player has the proper skill.
		String skillBox = "science_medic_injury_speed_02";
		if (!player->hasSkillBox(skillBox)) {
			player->sendSystemMessage("healing_response", "healing_response_a9"); //"You lack the ability to drag incapacitated players!"
			return 0;
		}

		//Validate the target.
		if (target == NULL) {
			player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return 0;
		}

		if (target->isPlayer()) {
			targetPlayer = (Player*)target;
		} else {
			player->sendSystemMessage("healing_response", "healing_response_a6"); //"You may only drag players!"
			return 0;
		}

		if (targetPlayer == player) {
			player->sendSystemMessage("healing_response", "healing_response_a5"); //"You must first have a valid target to drag before you can perform this command."
			return 0;
		}

		//Determine the maximum drag range.
		int skillMod = player->getSkillMod("healing_injury_speed");

		float actualRange = (float)skillMod / 3.75f;
		if (actualRange > maxRange) {
			actualRange = maxRange;
		}

		//Attempt to drag the target player.
		player->drag(targetPlayer, actualRange, maxMovement, needsConsent, false);

		return 0;
	}


	void setMaxRange(float max) {
		maxRange = max;
	}

	void setMaxMovement(float max) {
		maxMovement = max;
	}

	void setSpeed(float spd) {
		speed = spd;
	}

	void setNeedsConsent(bool consent) {
		needsConsent = consent;
	}

	float getSpeed() {
		return speed;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

};

#endif /*DRAGTARGETSKILL_H_*/
