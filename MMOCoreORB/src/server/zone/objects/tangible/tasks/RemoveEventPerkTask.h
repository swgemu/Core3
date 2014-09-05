
#ifndef REMOVEEVENTPERKTASK_H_
#define REMOVEEVENTPERKTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class RemoveEventPerkTask : public Task {
	ManagedReference<EventPerkDeed*> deed;

public:
	RemoveEventPerkTask(EventPerkDeed* de) {
		deed = de;
	}

	void run() {
		if (deed == NULL) {
			return;
		}

		ManagedReference<TangibleObject*> genOb = deed->getGeneratedObject().get();
		ManagedReference<CreatureObject*> player = deed->getOwner().get();

		if (genOb != NULL) {
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

#endif /* REMOVEEVENTPERKTASK_H_ */
