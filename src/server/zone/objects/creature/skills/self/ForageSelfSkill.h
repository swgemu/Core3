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

#ifndef FORAGESELFSKILL_H_
#define FORAGESELFSKILL_H_

#include "../SelfSkill.h"
#include "../../../player/Player.h"


class ForageSelfSkill : public SelfSkill {

protected:

	int actionCost;
	int forageType; //(0=forage, 1=medicalForage).
    String anim;

public:

	ForageSelfSkill(const String& name, const String& animation, ZoneProcessServerImplementation* serv) : SelfSkill(name, "", FORAGE, serv) {
		anim = animation;
    }

	void doSkill (CreatureObject* creature, String& modifier) {
       if (!creature->isPlayer())
    	   return;

       Player* player = (Player*)creature;

       //Check if player is already foraging.
       if (player->isForaging()) {
      	   player->sendSystemMessage("skl_use", "sys_forage_already"); //"You are already foraging."
		   return;
	   }

       //Check if player has the applicable forage skill.
       String skillBox;
       if (forageType == 0)
    	   skillBox = "outdoors_scout_camp_01";

       if (forageType == 1)
    	   skillBox = "science_medic_novice";

       if (!player->hasSkillBox(skillBox)) {
    	   player->sendSystemMessage("skl_use", "sys_forage_noskill"); //"You lack the skill to forage."
           return;
       }

       //Check for invalid states.
       bool success = forageStateCheck(player);
       if (success == false)
    	   return;

       //Check for and deduct action.
       success = forageProcessCost(player, actionCost);
       if (success == false)
    	   return;

       //Start foraging.
       player->sendSystemMessage("skl_use", "sys_forage_start"); //"You begin to search the area for goods."
       player->doAnimation(anim);
       player->startForaging(forageType);
	}

	bool forageProcessCost(Player* player, int actioncost) {
		int currentAction = player->getAction();

		if (currentAction > actioncost) {
	    	player->changeActionBar(-actioncost, 0);
	    	return true;
	    } else {
	    	player->sendSystemMessage("skl_use", "sys_forage_attrib"); //"You need to rest before you can forage again."
	        return false;
	    }
	}

	bool forageStateCheck(Player* player) {
		if (player->isInBuilding()) {
			player->sendSystemMessage("skl_use", "sys_forage_inside"); //"You can't forage inside a structure."
			return false;
		} else if (player->isInCombat() || !player->isStanding() || player->isMounted()) {
			player->sendSystemMessage("skl_use", "sys_forage_cant"); //"You can't forage right now."
	        return false;
		} else
			return true;
	}

    void setActionCost(int cost) {
       actionCost = cost;
    }

    void setSkill(int skillnum) {
       forageType = skillnum;
    }

	float calculateSpeed(CreatureObject* creature) {
		return 1.0;
	}

	bool calculateCost(CreatureObject* creature) {
		if (creature->isInCombat() || creature->isMounted())
			return false;
		else
			return true;
	}
};

#endif /*FORAGESELFSKILL_H_*/
