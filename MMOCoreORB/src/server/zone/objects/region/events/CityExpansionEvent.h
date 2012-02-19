/*
 * CityExpansionEvent.h
 *
 *  Created on: Feb 19, 2012
 *      Author: xyborn
 */

#ifndef CITYEXPANSIONEVENT_H_
#define CITYEXPANSIONEVENT_H_

#include "engine/engine.h"
#include "../CityRegion.h"
#include "server/zone/managers/city/CityManager.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace region {
    namespace events {

class CityExpansionEvent : public Task {
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CityExpansionEvent(CityRegion* city, uint32 duration) : Task(duration) {
		cityRegion = city;
	}

	void run() {
		ManagedReference<CityRegon*> city = cityRegion.get();

		if (city == NULL)
			return;

		Locker locker(city);

		CityManager* cityManager = city->getZone()->getCityManager();
		cityManager->expandCityRegion(city);
	}
};

    }
   }
  }
 }
}

using namespace server::zone::objects::region::events;

#endif /* CITYEXPANSIONEVENT_H_ */
