/*
 * PlayerIncapacitationRecoverTask.h
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#ifndef PLAYERINCAPACITATIONRECOVERTASK_H_
#define PLAYERINCAPACITATIONRECOVERTASK_H_


#include "../PlayerCreature.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerIncapacitationRecoverTask : public Task {
	ManagedReference<PlayerCreature*> player;

public:
	PlayerIncapacitationRecoverTask(PlayerCreature* pl) : Task() {
		player = pl;
	}

	~PlayerIncapacitationRecoverTask() {
		/*if (enQueued) {
			System::out << "ERROR: PlayerRecoveryEvent scheduled event deleted\n";
			raise(SIGSEGV);
		}*/
	}

	void run() {
		try {
			Locker playerLocker(player);

			int health = player->getHAM(CreatureAttribute::HEALTH);

			if (health < 0)
				player->setHAM(CreatureAttribute::HEALTH, 1);

			int action = player->getHAM(CreatureAttribute::HEALTH);

			if (action < 0)
				player->setHAM(CreatureAttribute::ACTION, 1);

			int mind = player->getHAM(CreatureAttribute::MIND);

			if (mind < 0)
				player->setHAM(CreatureAttribute::MIND, 1);

			player->setPosture(CreaturePosture::UPRIGHT);
		} catch (...) {
			player->error("unreported exception caught in PlayerRecoveryEvent::activate");

		}
	}

};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PLAYERINCAPACITATIONRECOVERTASK_H_ */
