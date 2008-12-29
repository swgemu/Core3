/*
 * MascScentSelfSkill.h
 *
 *  Created on: Oct 16, 2008
 *      Author: swgdev
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
		setCamoType(10);
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
