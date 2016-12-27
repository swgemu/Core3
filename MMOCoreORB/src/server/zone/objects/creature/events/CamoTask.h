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
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/ConcealBuff.h"

class CamoTask : public Task {
	ManagedWeakReference<CreatureObject*> creo;
	ManagedWeakReference<CreatureObject*> targ;
	bool success;
	bool maskScent;
	bool awardXp;

public:
	CamoTask(CreatureObject* cr, CreatureObject* tar, bool ms, bool succ, bool award) : Task(){
		creo = cr;
		targ = tar;
		success = succ;
		maskScent = ms;
		awardXp = award;
	}

	void run() {
		int crc = STRING_HASHCODE("skill_buff_mask_scent");

		if (maskScent) {
			crc = STRING_HASHCODE("skill_buff_mask_scent_self");
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
			creature->sendSystemMessage("@skl_use:sys_scentmask_break"); // A creature has detected you, despite your attempts at camouflage!
			creature->removeBuff(crc);
		}

		if(!success) {
			// on failure 50% chance to aggro animal if aggressive and within 40 meters
			if (System::random(100) > 50 && target->isAggressiveTo(creature) && target->isInRange(creature,40.0f))
				CombatManager::instance()->startCombat(target,creature,true);
			return;
		}

		if (creature->getPlayerObject() == NULL)
			return;

		if (maskScent) {
			StringIdChatParameter success("skl_use", "sys_scentmask_success");
			success.setTT(target->getObjectID());

			creature->sendSystemMessage(success);
		}

		if (awardXp) {
			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

			if (maskScent) {
				playerManager->awardExperience(creature, "scout", (target->getLevel() * 2), true);
			}
			else {
				ConcealBuff* buff = cast<ConcealBuff*>(creature->getBuff(crc));
				if (buff != NULL) {
					clocker.release();
					locker.release();

					ManagedReference<CreatureObject*> buffGiver = buff->getBuffGiver();
					if (buffGiver != NULL) {
						Locker buffGiverlocker(buffGiver);
						if (buffGiver->hasSkill("outdoors_ranger_novice")) {
							playerManager->awardExperience(buffGiver, "scout", (target->getLevel() * 2), true);
						}
					}
				}
			}

		}
	}
};

#endif /* CAMOTASK_H_ */
