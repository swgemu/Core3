
#ifndef FLAGGAMEPULSETASK_H_
#define FLAGGAMEPULSETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/eventperk/FlagGame.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class FlagGamePulseTask : public Task {
	ManagedReference<FlagGame*> game;

public:
	FlagGamePulseTask(FlagGame* ga) {
		game = ga;
	}

	void run() {
		if (game == NULL || game->isGameEnded())
			return;

		Locker locker(game);

		uint32 factionControl = game->getFactionControl();

		if (factionControl == 0x16148850) { // Rebel
			game->increaseRebelScore();
		} else if (factionControl == 0xDB4ACC54) { // Imperial
			game->increaseImperialScore();
		}

		uint64 timeLimit = game->getTimeLimit();
		Time* startTime = game->getGameStartTime();

		Time currentTime;
		uint64 timeDelta = currentTime.getMiliTime() - startTime->getMiliTime();

		if (timeDelta >= timeLimit) {
			game->endGame();
		} else {
			this->reschedule(15 * 1000); // 15 second pulse
		}
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* FLAGGAMEPULSETASK_H_ */
