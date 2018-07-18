/*
 * PlayerIncapacitationRecoverTask.h
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#ifndef PLAYERINCAPACITATIONRECOVERTASK_H_
#define PLAYERINCAPACITATIONRECOVERTASK_H_

#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureObject.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PlayerIncapacitationRecoverTask : public Task {
	ManagedReference<CreatureObject*> player;
	bool deadRecovery;

public:
	PlayerIncapacitationRecoverTask(CreatureObject* pl, bool deadRecovery) : Task() {
		player = pl;

		this->deadRecovery = deadRecovery;
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



			PlayerObject* ghost = player->getPlayerObject();

			if (ghost == NULL) {
				return;
			}

			if (!deadRecovery)
				player->removePendingTask("incapacitationRecovery");

			if (!deadRecovery && !player->isIncapacitated())
				return;
			else if (deadRecovery && !player->isDead())
				return;

			ghost->setCloning(false);

			int health = player->getHAM(CreatureAttribute::HEALTH);

			if (health < 0)
				player->setHAM(CreatureAttribute::HEALTH, 1);

			int action = player->getHAM(CreatureAttribute::ACTION);

			if (action < 0)
				player->setHAM(CreatureAttribute::ACTION, 1);

			int mind = player->getHAM(CreatureAttribute::MIND);

			if (mind < 0)
				player->setHAM(CreatureAttribute::MIND, 1);

			player->removeFeignedDeath();

			player->setPosture(CreaturePosture::UPRIGHT);

			player->notifyObservers(ObserverEventType::CREATUREREVIVED, NULL, 0);

			if (ghost->getForcePowerMax() > 0 && ghost->getForcePower() < ghost->getForcePowerMax()) {
				ghost->activateForcePowerRegen();
			}

			if (deadRecovery) {
				player->playEffect("clienteffect/player_clone_compile.cef");
				player->notifyObservers(ObserverEventType::PLAYERCLONED, player, 0);
				player->broadcastPvpStatusBitmask();
			}
		} catch (Exception& e) {
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
