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
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"

class PlaceCityHallSuiCallback : public SuiCallback {
	ManagedWeakReference<Zone*> zone;
	ManagedWeakReference<Deed*> deed;

	float x;
	float y;
	int angle;

public:
	PlaceCityHallSuiCallback(Zone* zone, Deed* deed, float x, float y, int angle)
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

		String cityName = args->get(0).toString();

		//Check the city hall name for:
		//- Uniqueness
		//- Vulgarity
		//- Fiction/Reserved

		NameManager* nameManager = NameManager::instance();

		if (nameManager->isProfane(cityName)) {
			//Resend the sui.
			creature->sendSystemMessage("@player_structure:obscene"); //That name was rejected by the name filter. Try a different name.
			return;
		}

		//Check unique
		PlanetManager* planetManager = zone->getPlanetManager();

		if (planetManager != NULL && planetManager->hasRegion(cityName)) {
			creature->sendSystemMessage("@player_structure:cityname_not_unique"); //Another city already has this name. Your city's name must be unique.
			//Resend the sui.
			return;
		}

		StructureManager* structureManager = zone->getStructureManager();
		int result = structureManager->placeStructureFromDeed(creature, deed, x, y, angle);

		if (result == 0) {
			//The building was successfully placed. Place the city area, and name it.
			CityRegion* city = new CityRegion(zone, cityName);
			city->setCityRank(CityManager::OUTPOST);
			city->setMayorID(creature->getObjectID());

			uint16 radius = CityManagerImplementation::radiusPerRank.get(CityManager::OUTPOST);
			city->addRegion(x, y, radius);
		}
	}
};

#endif /* PLACECITYHALLSUICALLBACK_H_ */
