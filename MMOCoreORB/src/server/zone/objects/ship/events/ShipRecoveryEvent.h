/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef SHIPRECOVERYEVENT_H_
#define SHIPRECOVERYEVENT_H_

#include "server/zone/objects/ship/ShipObject.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace events {

class ShipRecoveryEvent : public Task {
	ManagedWeakReference<ShipObject*> weakShip;

public:
	ShipRecoveryEvent(ShipObject* shipObj) {
		weakShip = shipObj;
	}

	void run() {
		ManagedReference<ShipObject*> ship = weakShip.get();

		if (ship == nullptr)
			return;

		ship->doRecovery(1000);
	}
};

}
}
}
}
}

using namespace server::zone::objects::ship::events;

#endif /*SHIPRECOVERYEVENT_H_*/
