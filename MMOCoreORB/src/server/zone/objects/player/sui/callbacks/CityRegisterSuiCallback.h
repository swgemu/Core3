/*
 * CityRegisterSuiCallback.h
 *
 *  Created on: Feb 20, 2012
 *      Author: xyborn
 */

#ifndef CITYREGISTERSUICALLBACK_H_
#define CITYREGISTERSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/region/CityRegion.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

class CityRegisterSuiCallback : public SuiCallback {
	ManagedWeakReference<CityRegion*> cityRegion;

	bool unregister;

public:
	CityRegisterSuiCallback(ZoneServer* server, CityRegion* city, bool unregister = false)
		: SuiCallback(server) {

		cityRegion = city;
		this->unregister = unregister;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL || cancelPressed)
			return;

		Locker lock(city, player);

		CityManager* cityManager = server->getCityManager();

		if (unregister) {
			cityManager->unregisterCity(city, player);
		} else {
			cityManager->registerCity(city, player);
		}
	}
};

#endif /* CITYREGISTERSUICALLBACK_H_ */
