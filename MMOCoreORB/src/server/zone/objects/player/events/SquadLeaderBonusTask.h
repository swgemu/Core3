/*
 * SquadLeaderBonusTask.h
 *
 *  Created on: Aug 21, 2010
 *      Author: swgemu
 */

#ifndef SQUADLEADERBONUSTASK_H_
#define SQUADLEADERBONUSTASK_H_

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

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

} // namespace tasks
} // namespace group
} // namespace objects
} // namespace player
} // namespace events

#endif /* SQUADLEADERBONUSTASK_H_ */
