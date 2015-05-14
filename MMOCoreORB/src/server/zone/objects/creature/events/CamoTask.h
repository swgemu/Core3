/*
 * CamoTask.h
 *
 *  Created on: May 23, 2012
 *      Author: da
 */

#ifndef CAMOTASK_H_
#define CAMOTASK_H_
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "system/lang/String.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CamoTask : public Task {
	ManagedWeakReference<CreatureObject*> creo;
	ManagedWeakReference<CreatureObject*> targ;
	bool success;
	bool maskScent;

public:
	CamoTask(CreatureObject* cr, CreatureObject* tar, bool ms, bool succ) : Task(){
		creo = cr;
		targ = tar;
		success = succ;
		maskScent = ms;
	}

	void run() {
		int crc = STRING_HASHCODE("skill_buff_mask_scent");
		String buffMsg = "@skl_use:sys_conceal_stop";

		if (maskScent) {
			crc = STRING_HASHCODE("skill_buff_mask_scent_self");
			buffMsg = "@skl_use:sys_scentmask_break";
		}

		ManagedReference<CreatureObject*> target = targ.get();
		if (target == NULL)
			return;

		ManagedReference<CreatureObject*> creature = creo.get();
		if (creature == NULL)
			return;

		Locker locker(target);
		Locker clocker(creature, target);

		if (!success && creature->hasBuff(crc)) {
			creature->sendSystemMessage(buffMsg);
			creature->removeBuff(crc);
		}

		if(!success) {
			// on failure 50% chance to aggro animal if aggressive and within 40 meters
			if (System::random(100) > 50 && target->isAggressiveTo(creature) && target->isInRange(creature,40.0f)) {
				CombatManager::instance()->startCombat(target,creature,true);
			}
			return;
		}

		if (creature->getPlayerObject() == NULL)
			return;

		if (!maskScent && !creature->hasSkill("outdoors_ranger_novice"))
			return;

		if (maskScent) {
			StringIdChatParameter success("skl_use", "sys_scentmask_success");
			success.setTT(target);

			creature->sendSystemMessage(success);
		}
		ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(creature, "scout", (target->getLevel() * 2), true);
	}
};


#endif /* CAMOTASK_H_ */
