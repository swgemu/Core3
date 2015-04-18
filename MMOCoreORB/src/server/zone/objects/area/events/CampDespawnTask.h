/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CAMPDESPAWNTASK_H_
#define CAMPDESPAWNTASK_H_

#include "server/zone/objects/area/CampSiteActiveArea.h"
#include "server/zone/ZoneServer.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace events {

class CampDespawnTask: public Task {
	ManagedReference<CampSiteActiveArea*> campSite;

public:
	CampDespawnTask(CampSiteActiveArea* camp) {
		campSite = camp;
	}

	void run() {
		if (campSite == NULL)
			return;

		ZoneServer* zoneServer = campSite->getZoneServer();

		if (zoneServer != NULL && zoneServer->isServerLoading()) {
			schedule(1000);

			return;
		}

		Locker locker(campSite);
		campSite->despawnCamp();
	}
};


}
}
}
}
}

#endif /* CAMPDESPAWNTASK_H_ */
