
#ifndef PVPTEFREMOVALTASK_H_
#define PVPTEFREMOVALTASK_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "templates/params/creature/CreatureFlag.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class PvpTefRemovalTask: public Task {
	ManagedWeakReference<CreatureObject*> creature;

public:
	PvpTefRemovalTask(CreatureObject* creo) {
		creature = creo;
	}

	void run() {
		ManagedReference<CreatureObject*> player = creature.get();

		if (player == nullptr)
			return;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject().get();

		if (ghost == nullptr) {
			return;
		}

		Locker locker(player);

		if (ghost->hasTef()) {
			auto gcwCrackdownTefMs = ghost->getLastGcwCrackdownCombatActionTimestamp().miliDifference();
			auto gcwTefMs = ghost->getLastGcwPvpCombatActionTimestamp().miliDifference();
			auto bhTefMs = ghost->getLastBhPvpCombatActionTimestamp().miliDifference();
			auto pvpAreaMs = ghost->getLastPvpAreaCombatActionTimestamp().miliDifference();

			auto rescheduleTime = gcwTefMs < bhTefMs ? gcwTefMs : bhTefMs;
			rescheduleTime = gcwCrackdownTefMs < rescheduleTime ? gcwCrackdownTefMs : rescheduleTime;
			rescheduleTime = pvpAreaMs < rescheduleTime ? pvpAreaMs : rescheduleTime;

			this->reschedule(llabs(rescheduleTime));
		} else {
			ghost->updateInRangeBuildingPermissions();
			ghost->setCrackdownTefTowards(0, false);
			player->clearPvpStatusBit(CreatureFlag::TEF, true);

			if (ConfigManager::instance()->useCovertOvertSystem())
				player->broadcastPvpStatusBitmask();
		}

		if (!ghost->hasBhTef())
			player->notifyObservers(ObserverEventType::BHTEFCHANGED);
	}
};

}
}
}
}
}

using namespace server::zone::objects::player::events;

#endif /* PVPTEFREMOVALTASK_H_ */
