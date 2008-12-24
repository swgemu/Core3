/*
 * ConcealSkill.h
 *
 *  Created on: Oct 22, 2008
 *      Author: swgdev
 */

#ifndef CONCEALSKILL_H_
#define CONCEALSKILL_H_

#include "../CamoSkill.h"
#include "../../../tangible/camokits/CamoKit.h"

#include "../../../../managers/player/PlayerManager.h"

class ConcealSkill : public CamoSkill {
protected:
	float duration;

	int camoType;

public:
	ConcealSkill(const String& name, ZoneProcessServerImplementation* serv) : CamoSkill(name, SELF, serv) {
		setDuration(0);
		setCamoType(9);
	}


	void doSkill(CreatureObject* creature,SceneObject* target, String& modifier) {

		Player* player = (Player*) creature;

		if(player == NULL)
			return;

		CamoKit* camoKit = findCamopack(creature);

		if (camoKit == NULL) {
			player->sendSystemMessage("skl_use", "sys_conceal_nokit");
			return;
		}

		int camoMod = creature->getSkillMod("camouflage") +  creature->getSkillModBonus("camouflage");

		if (camoMod < camoKit->getConcealMin()) {
			player->sendSystemMessage("skl_use", "sys_conceal_noskill");
			return;
		}

		if (target != NULL) {
			if(!target->isPlayer()) {
				player->sendSystemMessage("skl_use", "sys_conceal_notplayer");
				return;
			}
			Player* tar = (Player*) target;

			if (!isUseful(tar)) {
				return;
			}

			if (creature-> isPlayer()) {
				camoKit->useCharge((Player*) creature);
			} else
				return;

			tar->setCamoType(camoKit->getPlanet());
			tar->activateCamo(getNameCRC(),(int)getDuration(),camoMod);

			StfParameter* params = new StfParameter();
			params->addTT(tar->getCharacterName());

			player->sendSystemMessage("skl_use", "sys_conceal_apply", params);
			delete params;
		} else {
			if (!isUseful(creature)) {
				return;
			}

			if (creature-> isPlayer()) {
				camoKit->useCharge((Player*) creature);
			} else
				return;

			creature->setCamoType(camoKit->getPlanet());
			creature->activateCamo(getNameCRC(),(int)getDuration(),camoMod);
		}
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

		//if (creature->isInCombat() || creature->hasQueuedState(getNameCRC()) || creature->isMeditating()) {

		if (creature->getCamoType() < 10) {
			player->sendSystemMessage("skl_use", "sys_target_concealed");
			return false;
		}

		if (creature->isInCombat() || creature->isMeditating()) {
			player->sendSystemMessage("skl_use", "sys_conceal_cant");
			return false;
		}

		if (creature->getCamoType() == 10) {
			player->sendSystemMessage("skl_use", "sys_conceal_scentmasked");
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

	CamoKit* findCamopack(CreatureObject* creature) {
		CamoKit* camoKit= NULL;


		Inventory* inventory = creature->getInventory();

		for (int i=0; i<inventory->objectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isCamoKit()) {
				camoKit = (CamoKit*) item;

				if (creature->getZoneID() == camoKit->getPlanet())
					return camoKit;
			}
		}

		return NULL; //Never found a stimpack
	}
};

#endif
