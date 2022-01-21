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
#include "server/zone/objects/creature/ai/AiAgent.h"

class CamoTask : public Task {
	ManagedWeakReference<CreatureObject*> player;
	ManagedWeakReference<CreatureObject*> creature;
	bool success;
	bool maskScent;

public:
	CamoTask(CreatureObject* pl, CreatureObject* creo, bool ms, bool succ) : Task() {
		player = pl;
		creature = creo;
		success = succ;
		maskScent = ms;
	}

	void run() {
		int crc = STRING_HASHCODE("skill_buff_mask_scent");

		if (maskScent) {
			crc = STRING_HASHCODE("skill_buff_mask_scent_self");
		}

		ManagedReference<CreatureObject*> aiCreo = creature.get();
		ManagedReference<CreatureObject*> playerCreo = player.get();

		if (aiCreo == nullptr || playerCreo == nullptr)
			return;

		Locker locker(aiCreo);
		Locker clocker(playerCreo, aiCreo);

		if (!success) {
			if (playerCreo->hasBuff(crc)) {
				playerCreo->sendSystemMessage("@skl_use:sys_scentmask_break"); // A creature has detected you, despite your attempts at camouflage!
				playerCreo->removeBuff(crc);
			}

			int timer = (70 - (playerCreo->getSkillMod("mask_scent") / 2)) * 1000;

			if (timer > 0) {
				playerCreo->updateCooldownTimer("skill_buff_mask_scent_self", timer);
			}

			// on failure 50% chance to aggro animal if aggressive and within 40 meters
			if (System::random(100) > 50 && aiCreo->isInRange3d(playerCreo, 40.0f)) {
				if (aiCreo->isAiAgent()) {
					AiAgent* agent = aiCreo->asAiAgent();

					if (agent != nullptr)
						agent->setDefender(playerCreo);
				}
			}

			return;
		}

		if (maskScent) {
			StringIdChatParameter success("skl_use", "sys_scentmask_success"); // Due to your scent mask, a %TT ignores you.
			success.setTT(aiCreo->getObjectID());
			playerCreo->sendSystemMessage(success);
		}

		ManagedReference<PlayerManager*> playerManager = playerCreo->getZoneServer()->getPlayerManager();

		if (maskScent) {
			playerManager->awardExperience(playerCreo, "scout", (aiCreo->getLevel() * 2), true);
		} else {
			Reference<ConcealBuff*> buff = cast<ConcealBuff*>(playerCreo->getBuff(crc));
			if (buff != nullptr) {
				clocker.release();
				locker.release();

				ManagedReference<CreatureObject*> buffGiver = buff->getBuffGiver();
				if (buffGiver != nullptr) {
					Locker buffGiverlocker(buffGiver);
					if (buffGiver->hasSkill("outdoors_ranger_novice")) {
						playerManager->awardExperience(buffGiver, "scout", (aiCreo->getLevel() * 2), true);
					}
				}
			}
		}
	}
};

#endif /* CAMOTASK_H_ */
