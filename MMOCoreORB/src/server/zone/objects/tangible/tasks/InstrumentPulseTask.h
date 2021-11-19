
#ifndef INSTRUMENTPULSETASK_H_
#define INSTRUMENTPULSETASK_H_

#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class InstrumentPulseTask : public Task {
	WeakReference<Instrument*> instrument;

public:
	InstrumentPulseTask(Instrument* inst) {
		instrument = inst;
	}

	void run() {
		ManagedReference<Instrument*> strongRef = instrument.get();

		if (strongRef == nullptr)
			return;

		Locker locker(strongRef);

		ManagedReference<CreatureObject*> spawnerPlayer = strongRef->getSpawnerPlayer().get();

		if (spawnerPlayer == nullptr || !spawnerPlayer->isPlayerCreature() || !spawnerPlayer->getPlayerObject()->isOnline() || spawnerPlayer->getParentID() != strongRef->getParentID() || !strongRef->isInRange(spawnerPlayer, 8.0f)) {
			strongRef->destroyObjectFromWorld(true);
			return;
		}

		reschedule(5 * 1000); // 5 seconds
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* INSTRUMENTPULSETASK_H_ */
