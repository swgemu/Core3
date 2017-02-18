/*
 * CamoTask.h
 *
 *  Created on: May 23, 2012
 *      Author: da
 */

#ifndef CAMOTASK_H_
#define CAMOTASK_H_

#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/ConcealBuff.h"

class CamoTask : public Task {
	ManagedWeakReference<CreatureObject*> play;
	ManagedWeakReference<CreatureObject*> mob;
	bool success;
	bool maskScent;

public:
	CamoTask(CreatureObject* pl, CreatureObject* mobile, bool ms, bool succ) : Task() {
		play = pl;
		mob = mobile;
		success = succ;
		maskScent = ms;
	}

	void run() {
		int crc = STRING_HASHCODE("skill_buff_mask_scent");

		if (maskScent) {
			crc = STRING_HASHCODE("skill_buff_mask_scent_self");
		}

		ManagedReference<CreatureObject*> ai = mob.get();
		ManagedReference<CreatureObject*> player = play.get();
		if (ai == NULL || player == NULL)
			return;

		Locker locker(ai);
		Locker clocker(player, ai);

		if (!success) {
			if (player->hasBuff(crc)) {
				player->sendSystemMessage("@skl_use:sys_scentmask_break"); // A creature has detected you, despite your attempts at camouflage!
				player->removeBuff(crc);
			}

			// on failure 50% chance to aggro animal if aggressive and within 40 meters
			if (System::random(100) > 50 && ai->isAggressiveTo(player) && ai->isInRange3d(player, 40.0f))
				CombatManager::instance()->startCombat(ai, player, true);

			return;
		}

		if (maskScent) {
			StringIdChatParameter success("skl_use", "sys_scentmask_success"); // Due to your scent mask, a %TT ignores you.
			success.setTT(ai->getObjectID());
			player->sendSystemMessage(success);
		}

		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		if (maskScent) {
			playerManager->awardExperience(player, "scout", (ai->getLevel() * 2), true);
		} else {
			Reference<ConcealBuff*> buff = cast<ConcealBuff*>(player->getBuff(crc));
			if (buff != NULL) {
				clocker.release();
				locker.release();

				ManagedReference<CreatureObject*> buffGiver = buff->getBuffGiver();
				if (buffGiver != NULL) {
					Locker buffGiverlocker(buffGiver);
					if (buffGiver->hasSkill("outdoors_ranger_novice")) {
						playerManager->awardExperience(buffGiver, "scout", (ai->getLevel() * 2), true);
					}
				}
			}
		}
	}
};

#endif /* CAMOTASK_H_ */
