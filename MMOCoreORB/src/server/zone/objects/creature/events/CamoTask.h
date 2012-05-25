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
		int crc = String("skill_buff_mask_scent").hashCode();
		String buffMsg = "@skl_use:sys_conceal_stop";

		if (maskScent) {
			crc = String("skill_buff_mask_scent_self").hashCode();
			buffMsg = "@skl_use:sys_scentmask_break";
		}

		ManagedReference<CreatureObject*> target = targ.get();
		if (target == NULL)
			return;

		Locker tlocker(target);

		if (!success && target->hasBuff(crc)) {
			target->sendSystemMessage(buffMsg);
			target->removeBuff(crc);
		}

		ManagedReference<CreatureObject*> creature = creo.get();
		if (creature == NULL)
			return;

		Locker clocker(creature, target);

		ManagedReference<PlayerObject*> player = creature->getPlayerObject();
		if (player == NULL)
			return;

		if (!maskScent && !creature->hasSkill("outdoors_ranger_novice"))
			return;

		if (maskScent) {
			StringIdChatParameter success("skl_use", "sys_scentmask_success");
			success.setTT(target);

			target->sendSystemMessage(success);
		}

		player->addExperience("scout", (creature->getLevel() * 2), true);
	}
};


#endif /* CAMOTASK_H_ */
