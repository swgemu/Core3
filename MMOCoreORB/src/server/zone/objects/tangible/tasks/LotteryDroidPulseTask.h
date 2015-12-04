
#ifndef LOTTERYDROIDPULSETASK_H_
#define LOTTERYDROIDPULSETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/eventperk/LotteryDroid.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class LotteryDroidPulseTask : public Task {
	ManagedReference<LotteryDroid*> droid;

public:
	LotteryDroidPulseTask(LotteryDroid* dr) {
		droid = dr;
	}

	void run() {
		if (droid == NULL)
			return;

		Locker locker(droid);

		int gameStatus = droid->getGameStatus();

		if (gameStatus == 1) {
			uint64 timeLimit = droid->getGameDuration() * 3600 * 1000;
			Time* startTime = droid->getGameStartTime();

			Time currentTime;
			uint64 timeDelta = currentTime.getMiliTime() - startTime->getMiliTime();

			if (timeDelta >= timeLimit) {
				droid->endGame();

				// Resets duration to so that droid will stay in world for 72 hours after game ends to give lottery results
				droid->resetGameStartTime();
				droid->setGameDuration(6); // 72 hours
			}

			this->reschedule(3600 * 1000); // 60 minute pulse
		} else if (gameStatus == 2) {
			uint64 timeLimit = droid->getGameDuration() * 3600 * 1000;
			Time* startTime = droid->getGameStartTime();

			Time currentTime;
			uint64 timeDelta = currentTime.getMiliTime() - startTime->getMiliTime();

			if (timeDelta >= timeLimit) {
				droid->activateRemoveEvent(true);
			}
		}
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* LOTTERYDROIDPULSETASK_H_ */
