/*
 * SquadLeaderBonusTask.h
 *
 *  Created on: Aug 21, 2010
 *      Author: swgemu
 */

#ifndef SQUADLEADERBONUSTASK_H_
#define SQUADLEADERBONUSTASK_H_

class SquadLeaderBonusTask : public Task {
	ManagedReference<CreatureObject*> player;

public:
	SquadLeaderBonusTask(CreatureObject* player) {
		this->player = player;
	}

	void run() {
		Locker playerLocker(player);

		if (player->isGrouped()) {
			ManagedReference<GroupObject*> group = player->getGroup();

			if (group == NULL)
				return;

			playerLocker.release();

			Locker glocker(group);

			if (group->hasSquadLeader())
				group->addGroupModifiers();
		}
	}
};

#endif /* SQUADLEADERBONUSTASK_H_ */
