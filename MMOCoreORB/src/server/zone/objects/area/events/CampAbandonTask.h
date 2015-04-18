/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CAMPABANDONTASK_H_
#define CAMPABANDONTASK_H_

#include "server/zone/objects/area/CampSiteActiveArea.h"

namespace server {
namespace zone {
namespace objects {
namespace area {
namespace events {

class CampAbandonTask: public Task {
	ManagedReference<CampSiteActiveArea*> campSite;


public:
	CampAbandonTask(CampSiteActiveArea* camp) {
		campSite = camp;
	}

	void run() {
		if (campSite == NULL)
			return;

		Locker locker(campSite);
		campSite->abandonCamp();
	}
};


}
}
}
}
}

#endif /* CAMPABANDONTASK_H_ */
