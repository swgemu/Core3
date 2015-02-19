
#ifndef CITIZENASSESSMENTEVENT_H_
#define CITIZENASSESSMENTEVENT_H_

#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/ZoneServer.h"

class CitizenAssessmentEvent : public Task {
	ManagedReference<ZoneServer*> zoneServer;
	ManagedWeakReference<CityRegion*> cityRegion;

public:
	CitizenAssessmentEvent(CityRegion* city, ZoneServer* zserv) : Task() {
		cityRegion = city;
		zoneServer = zserv;
	}

	void run() {
		ManagedReference<CityRegion*> city = cityRegion.get();

		if (city == NULL)
			return;

		CityManager* cityManager = zoneServer->getCityManager();
		cityManager->assessCitizens(city);
	}
};

#endif /* CITIZENASSESSMENTEVENT_H_ */
