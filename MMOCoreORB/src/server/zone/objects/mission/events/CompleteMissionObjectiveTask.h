/*
 * AwardRewardTask.h
 *
 *  Created on: 13/06/2012
 *      Author: victor
 */

#ifndef AWARDREWARDTASK_H_
#define AWARDREWARDTASK_H_

#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CompleteMissionObjectiveTask : public Task {
	ManagedReference<MissionObjective*> objective;

public:
	CompleteMissionObjectiveTask(MissionObjective* missionObjective) {
		objective = missionObjective;
	}

	void run() {
		Locker locker(missionObjective);

		if (objective->getPlayerOwner() == NULL)
			return;

		missionObjective->awardReward();

		missionObjective->awardFactionPoints();

		missionObjective->removeMissionFromPlayer();
	}
};


#endif /* AWARDREWARDTASK_H_ */
