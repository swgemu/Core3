/*
 * StartTutorialTask.h
 *
 *  Created on: 28/05/2011
 *      Author: victor
 */

#include "server/zone/managers/director/DirectorManager.h"

namespace server {
namespace zone {
namespace objects {
namespace building {
namespace tutorial {
namespace events {

class StartTutorialTask : public Task {
	ManagedReference<CreatureObject*> player;

public:
	StartTutorialTask(CreatureObject* play) :
		Task() {

		player = play;
	}

	void run() {
		Locker _locker(player);

		DirectorManager::instance()->startScreenPlay(player, "TutorialScreenPlay");
	}

};

}
}
}
}
}
}
