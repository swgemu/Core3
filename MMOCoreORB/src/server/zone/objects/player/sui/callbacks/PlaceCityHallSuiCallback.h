/*
 * PlaceCityHallSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: xyborn
 */

#ifndef PLACECITYHALLSUICALLBACK_H_
#define PLACECITYHALLSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/structure/StructureDeed.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"

class PlaceCityHallSuiCallback : public SuiCallback {
	ManagedWeakReference<Zone*> zone;
	ManagedWeakReference<StructureDeed*> deed;

	float x;
	float y;
	int angle;

public:
	PlaceCityHallSuiCallback(Zone* zone, StructureDeed* deed, float x, float y, int angle)
			: SuiCallback(zone->getZoneServer()) {

		this->zone = zone;
		this->deed = deed;
		this->x = x;
		this->y = y;
		this->angle = angle;
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isInputBox() || cancelPressed || creature == NULL)
			return;

		if (args->size() < 0)
			return;

		ManagedReference<Zone*> zone = this->zone.get();

		if (zone == NULL)
			return;

		String cityName = args->get(0).toString();

		//Check the city hall name for:
		//- Uniqueness
		//- Vulgarity
		//- Fiction/Reserved

		NameManager* nameManager = NameManager::instance();

		if (nameManager->isProfane(cityName) || cityName.contains("\\") || cityName.contains("#")) {
			//Resend the sui.
			creature->sendSystemMessage("@player_structure:obscene"); //That name was rejected by the name filter. Try a different name.
			return;
		}

		//Check unique
		PlanetManager* planetManager = zone->getPlanetManager();
		CityManager* cityManager = server->getCityManager();

		Locker locker(cityManager);

		if (!cityManager->validateCityInRange(creature, zone, x, y) || !planetManager->validateClientCityInRange(creature, x, y))
			return;

		if (!planetManager->validateRegionName(cityName) || !cityManager->validateCityName(cityName)) {
			creature->sendSystemMessage("@player_structure:cityname_not_unique"); //Another city already has this name. Your city's name must be unique.
			//Resend the sui.
			return;
		}

		/*SortedVector<ManagedReference<ActiveArea*> > activeAreas;
		zone->getInRangeActiveAreas(x, y, activeAreas, true);

		for (int i = 0; i < activeAreas.size(); ++i) {
			Region*
		}*/

		StructureManager* structureManager = zone->getStructureManager();
		int result = structureManager->placeStructureFromDeed(creature, deed, x, y, angle);

		if (result == 0) {
			cityManager->createCity(creature, cityName, x, y);
		}
	}
};

#endif /* PLACECITYHALLSUICALLBACK_H_ */
