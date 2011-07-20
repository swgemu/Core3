/*
 * AwardXpEvent.h
 *
 *  Created on: Apr 4, 2011
 *      Author: polonel
 */

#ifndef AWARDXPEVENT_H_
#define AWARDXPEVENT_H_

#include "engine/engine.h"
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/PlayerObject.h"

namespace server {
namespace zone {
namespace managers {
namespace vendor {
namespace events {

class AwardXpEvent : public Task {
public:
	AwardXpEvent() : Task() {

	}

	~AwardXpEvent() {

	}

	void run() {
		VendorManager* vman = VendorManager::instance();

		for (int i = 0; i < vman->getVendorMapSize(); ++i) {
			Vendor* vendor = vman->getVendor(i);

			if (vendor == NULL)
				continue;

			if (!vendor->isInitialized())
				continue;

			ManagedReference<SceneObject*> vendorRef = vendor->getVendor();

			if (vendorRef == NULL || !vendorRef->isVendor())
				continue;

			ManagedReference<SceneObject*> ownerRef = vendorRef->getZoneServer()->getObject(vendor->getOwnerID());
			ManagedReference<PlayerManager*> pman = vendorRef->getZoneServer()->getPlayerManager();

			if (ownerRef == NULL || pman == NULL || !ownerRef->isPlayerCreature())
				continue;

			ManagedReference<CreatureObject*> owner = (CreatureObject*) ownerRef.get();

			Locker locker(owner);

			pman->awardExperience(owner, "merchant", 150, false);

		}

		if (this->isScheduled())
			this->reschedule(60 * 60000); // 60min
		else
			this->schedule(60 * 60000); // 60min

	}

};

}
}
}
}
}

using namespace server::zone::managers::vendor::events;


#endif /* AWARDXPEVENT_H_ */
