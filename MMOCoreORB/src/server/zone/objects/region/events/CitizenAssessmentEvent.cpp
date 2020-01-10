#include "CitizenAssessmentEvent.h"

#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/region/CityRegion.h"

CitizenAssessmentEvent::CitizenAssessmentEvent(CityRegion* city, ZoneServer* zserv) : Task() {
	cityRegion = city;
	zoneServer = zserv;
}


void CitizenAssessmentEvent::run() {
	Reference<CityRegion*> city = cityRegion.get();

	if (city == nullptr)
		return;

	CityManager* cityManager = zoneServer->getCityManager();
	cityManager->assessCitizens(city);
}