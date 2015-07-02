
#ifndef REMOVEEVENTPERKDEEDTASK_H_
#define REMOVEEVENTPERKDEEDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class RemoveEventPerkDeedTask : public Task {
	ManagedReference<EventPerkDeed*> deed;

public:
	RemoveEventPerkDeedTask(EventPerkDeed* de) {
		deed = de;
	}

	void run() {
		if (deed == NULL) {
			return;
		}

		ManagedReference<TangibleObject*> genOb = deed->getGeneratedObject().get();
		ManagedReference<CreatureObject*> player = deed->getOwner().get();

		Locker locker(deed);

		if (genOb != NULL) {
			Locker clocker(genOb, deed);
			genOb->destroyObjectFromWorld(true);
			genOb->destroyObjectFromDatabase();
		} else if (player != NULL) {
			player->sendSystemMessage("@event_perk:deed_expired"); // Your unused Rental Deed expired and has been removed from your inventory.
		}

		deed->destroyObjectFromWorld(true);
		deed->destroyObjectFromDatabase();

	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* REMOVEEVENTPERKDEEDTASK_H_ */
