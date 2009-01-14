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

#ifndef GROUPSKILL_H_
#define GROUPSKILL_H_

#include "../CreatureObject.h"
#include "../CreatureObjectImplementation.h"

#include "../../player/Player.h"

#include "Skill.h"

class GroupSkill : public Skill {
public:


protected:

	int healthCost;
	int actionCost;
	int mindCost;
	int cooldownTime;
	String combatSpam;

public:
	GroupSkill(const String& name, const String& anim, int tp, ZoneProcessServerImplementation* serv) : Skill(name, tp, GROUP, serv) {
		setAnimation(anim);
		healthCost = 0;
		actionCost = 0;
		mindCost = 0;
		cooldownTime = 0;
		combatSpam = "";
	}

	virtual void doSkill(CreatureObject* creature, bool doAnimation = true) = 0;

	virtual void doAnimations(CreatureObject* creature) {

	}

	bool canBePerformed(CreatureObject* creature) {
		if(creature->isPlayer()) {
			Player* player = (Player*)creature;
			GroupObject* group = player->getGroupObject();
			if(group == NULL) {
				player->sendSystemMessage("You must be in a group to perform this action.");
				return false;
			}

			if(group->getLeader() != player) {
				player->sendSystemMessage("You must be the group leader to perform this action.");
				return false;
			}

			if(!checkHAMCost(creature))
				return false;

			return derivedCanBePerformed(creature);
		}

		return false;
	}

	virtual bool derivedCanBePerformed(CreatureObject* creature) = 0;

	virtual bool checkHAMCost(CreatureObject* creature) {
		if(creature->getHealth() < healthCost) {
			creature->sendSystemMessage("You do not have enough Health to perform this action.");
			return false;
		}
		if(creature->getAction() < actionCost) {
			creature->sendSystemMessage("You do not have enough Action to perform this action.");
			return false;
		}
		if(creature->getMind() < mindCost) {
			creature->sendSystemMessage("You do not have enough Mind to perform this action.");
			return false;
		}

		return true;
	}

	virtual float getSpeed() {
		return 1.0f;
	}

	void setHealthCost(int value) {
		healthCost = value;
	}

	void setActionCost(int value) {
		actionCost = value;
	}

	void setMindCost(int value) {
		mindCost = value;
	}

	void setCombatSpam(const String& value) {
		combatSpam = value;
	}

	void setCooldownTime(int value) {
		cooldownTime = value;
	}
};

#endif /*GROUPSKILL_H_*/
