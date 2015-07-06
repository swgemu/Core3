
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
		printf("pulsing game\n");
		if (game == NULL || game->isGameEnded()) {
			printf("game null or ended\n");
			return;
		}

		uint32 factionControl = game->getFactionControl();

		if (factionControl == 0x16148850) { // Rebel
			printf("rebel score increase\n");
			game->increaseRebelScore();
		} else if (factionControl == 0xDB4ACC54) { // Imperial
			printf("imperial score increase\n");
			game->increaseImperialScore();
		}

		uint64 timeLimit = game->getTimeLimit();
		Time* startTime = game->getGameStartTime();

		Time currentTime;
		uint64 timeDelta = currentTime.getMiliTime() - startTime->getMiliTime();

		printf("time limit: %s\n", String::valueOf(timeLimit).toCharArray());
		printf("time delta: %s\n", String::valueOf(timeDelta).toCharArray());

		if (timeDelta >= timeLimit) {
			printf("Ending game\n");
			game->endGame();
		} else {
			printf("Rescheduling task 15 secs\n");
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
