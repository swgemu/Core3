#include "CitizenAssessmentEvent.h"

#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/region/NewCityRegion.h"

CitizenAssessmentEvent::CitizenAssessmentEvent(NewCityRegion* city, ZoneServer* zserv) : Task() {
	cityRegion = city;
	zoneServer = zserv;
}


void CitizenAssessmentEvent::run() {
	Reference<NewCityRegion*> city = cityRegion.get();

	if (city == nullptr)
		return;

	CityManager* cityManager = zoneServer->getCityManager();
	cityManager->assessCitizens(city);
}