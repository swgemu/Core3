
#ifndef LOTTERYDROIDPULSETASK_H_
#define LOTTERYDROIDPULSETASK_H_

#include "server/zone/objects/tangible/eventperk/LotteryDroid.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/tangible/components/EventPerkDataComponent.h"

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

		if (gameStatus == LotteryDroid::GAMESTARTED) {
				droid->endGame();

				// Resets duration to so that droid will stay in world for 72 hours after game ends to give lottery results
				this->reschedule(72 * 60 * 60 * 1000); // 72 hours
		} else if (gameStatus == LotteryDroid::GAMEENDED) {
			EventPerkDataComponent* gameData = cast<EventPerkDataComponent*>(droid->getDataObjectComponent()->get());

			if (gameData == NULL)
				return;

			EventPerkDeed* deed = gameData->getDeed();

			if (deed == NULL)
				return;

			deed->activateRemoveEvent(true);
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
