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
#ifndef MASKSCENTSELFSKILL_H_
#define MASKSCENTSELFSKILL_H_

#include "../CamoSkill.h"

class MaskScentSelfSkill : public CamoSkill {
protected:
	float duration;

	int camoType;

	String startFlyText;
	String finishFlyText;

public:
	MaskScentSelfSkill(const String& name, ZoneProcessServerImplementation* serv) : CamoSkill(name, SELF, serv) {
		setDuration(0);
		setCamoType(NONE);
	}


	void doSkill(CreatureObject* creature, String& modifier) {
		if (!isUseful(creature)) {
			return;
		}

		int camoMod = creature->getSkillMod("mask_scent") +  creature->getSkillModBonus("mask_scent");

		creature->setCamoType(getCamoType());
		creature->activateCamo(getNameCRC(), (int)getDuration(), camoMod);
	}

	void doAnimations(CreatureObject* creature) {
	}

	void finish(CreatureObject* creature) {
		creature->deactivateCamo(false);
	}

	float calculateSpeed(CreatureObject* creature) {
			return 0;
	}

	bool isUseful(CreatureObject* creature) {

		Player* player = (Player*) creature;

		if(player == NULL)
			return false;

		String skillName = "outdoors_scout_novice";

		if (!creature->hasSkillMod("mask_scent")) {
			player->sendSystemMessage("skl_use", "sys_scentmask_noskill");

			return false;
		}

		if (creature->isInCombat() || creature->isMeditating()) {
			player->sendSystemMessage("skl_use", "sys_scentmask_fail");

			return false;
		}

//		if (creature->hasQueuedState(getNameCRC())) {
		if (creature->getCamoType() == 10) {
			player->sendSystemMessage("skl_use", "sys_scentmask_already");

			return false;

		}
		if (creature->getCamoType() < 10) {
			player->sendSystemMessage("skl_use", "sys_scentmask_concealed");

			return false;
		}


		if(!creature->isCamoCooldownActive()) {

			int left = creature->getCamoCooldownLeft() / 1000;
			int seconds = left % 60;

			StfParameter* params = new StfParameter();
			params->addDI(seconds);

			player->sendSystemMessage("skl_use", "sys_conceal_delay", params);
			delete params;

			return false;
		}

		if  (!creature->changeHAMBars(-50,-100,-50,false)) {
			return false;
		}

		return true;
	}
};


#endif
