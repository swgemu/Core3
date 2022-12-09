/*
 * CityManageMilitiaSuiCallback.h
 *
 *  Created on: Feb 13, 2012
 *      Author: xyborn
 */

#ifndef CITYMANAGEMILITIASUICALLBACK_H_
#define CITYMANAGEMILITIASUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
namespace region {
	class NewCityRegion;
}
}
}
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::region;

class CityManageMilitiaSuiCallback : public SuiCallback {
	ManagedWeakReference<NewCityRegion*> cityRegion;

public:
	CityManageMilitiaSuiCallback(ZoneServer* server, NewCityRegion* city)
		: SuiCallback(server) {

		cityRegion = city;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args);
};

#endif /* CITYMANAGEMILITIASUICALLBACK_H_ */
