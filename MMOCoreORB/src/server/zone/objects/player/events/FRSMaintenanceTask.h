/*
 * FrsMaintenanceTask.h
 *
 *  Created on: Jun 29, 2013
 *      Author: Dreadlow
 */

#ifndef FRSMAINTENANCETASK_H_
#define FRSMAINTENANCETASK_H_

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/forcerank/ForceRankObject.h"
#include "server/zone/managers/frs/FrsManager.h"

class FRSMaintenanceTask: public Task {
	ManagedReference<CreatureObject*> creature;
	ManagedReference<PlayerObject*> player;
	ManagedReference<PlayerManager*> playerManager;
	ManagedReference<ChatManager*> chatManager;
	ManagedReference<FrsManager*> frsManager;
	ManagedReference<ForceRankObject*> enclaveObject;

	static const int TWENTYFOURHOURS = 86400000;

public:
	FRSMaintenanceTask(CreatureObject* creo) {
		creature      = creo;
		player        = creo->getPlayerObject();
		playerManager = creo->getZoneServer()->getPlayerManager();
		chatManager   = creo->getZoneServer()->getChatManager();
		frsManager    = creo->getZoneServer()->getFrsManager();
		enclaveObject = creo->getForceRankObject();
	}

	void run() {
		Locker locker(creature);

		Time* currentTime = new Time();
		uint64 timeDelta = currentTime->getMiliTime() - player->getLastFRSMaintenance();

		if (timeDelta >= TWENTYFOURHOURS) {
			int catchUp = floor(timeDelta / TWENTYFOURHOURS);

			for (int i = 0; i < catchUp; ++i) {
				Locker locker(creature);

				int payment = 0;

				SkillList* skillList = creature->getSkillList();

				for (int i = 0; i < skillList->size(); ++i) {
					Skill* checkSkill = skillList->get(i);

					if (checkSkill->getSkillName().beginsWith("force_rank_") && !checkSkill->getSkillName().contains("_novice")) {
						payment += 100;
					}
				}

				if (payment != 0) {
					if (player->getExperience("force_rank_xp") > payment) {
						playerManager->awardExperience(creature, "force_rank_xp", payment, true);

						StringIdChatParameter message("force_rank", "xp_maintenance_body");
						message.setDI(payment);
						chatManager->sendMail("@jedi_trials:from_unknown", "@force_rank:xp_maintenace_sub", message, creature->getFirstName());
					}

					if (!qualificationCheck()) {
						demotePlayer();

						StringIdChatParameter message("force_rank", "demote_xp_debt_body");
						chatManager->sendMail("@jedi_trials:from_unknown", "@force_rank:demote_xp_debt_sub", message, creature->getFirstName());
					}
				}
			}

			player->updateLastFRSMaintenance();
		}
	}

	bool qualificationCheck() {
		SkillList* skillList = creature->getSkillList();

		for (int i = 0; i < skillList->size(); ++i) {
			Skill* checkSkill = skillList->get(i);

			if (checkSkill->getSkillName().beginsWith("force_rank_") && !checkSkill->getSkillName().endsWith("_novice")) {
				if (checkSkill->getSkillName().endsWith("_master")) {
					if (player->getExperience("force_rank_xp") < (checkSkill->getXpCost() - 100000))
						return false;
				} else if (checkSkill->getSkillName().endsWith("_10")) {
					if (player->getExperience("force_rank_xp") < (checkSkill->getXpCost() - 50000))
						return false;
				} else if (checkSkill->getSkillName().endsWith("_08") || checkSkill->getSkillName().endsWith("_09")) {
					if (player->getExperience("force_rank_xp") < (checkSkill->getXpCost() - 20000))
						return false;
				} else if (checkSkill->getSkillName().endsWith("_05") || checkSkill->getSkillName().endsWith("_06") || checkSkill->getSkillName().endsWith("_07")) {
					if (player->getExperience("force_rank_xp") < (checkSkill->getXpCost() - 10000))
						return false;
				} else {
					if (player->getExperience("force_rank_xp") < (checkSkill->getXpCost() - 5000))
						return false;
				}
			}
		}

		return true;
	}

	void demotePlayer() {
		String council;
		String markedSkill;

		int highestRank = 0;

		SkillList* skillList = creature->getSkillList();

		for (int i = 0; i < skillList->size(); ++i) {
			Skill* checkSkill = skillList->get(i);

			if (checkSkill->getSkillName().beginsWith("force_rank_") && !checkSkill->getSkillName().contains("_novice"))
				highestRank = highestRank + 1;
		}

		if (player->getJediState() == 8)
			council = "dark";
		else
			council = "light";

		if (highestRank == 11)
			markedSkill = "force_rank_" + council + "_master";
		else if (highestRank < 10)
			markedSkill = "force_rank_" + council + "_rank_0" + String::valueOf(highestRank);
		else
			markedSkill = "force_rank_" + council + "_rank_10";

		SkillManager::instance()->surrenderSkill(markedSkill, creature, true);
	}
};

#endif /* FRSMAINTENANCETASK_H_ */
