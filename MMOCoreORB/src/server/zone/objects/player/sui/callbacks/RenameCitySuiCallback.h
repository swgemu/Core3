/*
 * RenameCitySuiCallback.h
 *
 *  Created on: Sep 2, 2013
 *      Author: root
 */

#ifndef RENAMECITYSUICALLBACK_H_
#define RENAMECITYSUICALLBACK_H_
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/city/CityManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/planet/PlanetManager.h"


class RenameCitySuiCallback : public SuiCallback {
	ManagedWeakReference<Zone*> zne;
	ManagedWeakReference<CityRegion*> city;

public:
	RenameCitySuiCallback(Zone* zone, CityRegion* city)
			: SuiCallback(zone->getZoneServer()) {

		this->zne = zone;
		this->city = city;
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if(cancelPressed)
			return;

		if(city == NULL || server == NULL)
			return;

		ManagedReference<Zone*> zone = this->zne.get();

		if (zone == NULL)
			return;

		String cityName = args->get(0).toString();

		NameManager* nameManager = NameManager::instance();

		int result = nameManager->validateCityName(cityName);

		switch (result) {
		case NameManagerResult::DECLINED_PROFANE:
		case NameManagerResult::DECLINED_DEVELOPER:
		case NameManagerResult::DECLINED_FICT_RESERVED:
		case NameManagerResult::DECLINED_RESERVED:
			creature->sendSystemMessage("@player_structure:obscene"); //That name was rejected by the name filter. Try a different name.
			return;
			break;

		case NameManagerResult::DECLINED_RACE_INAPP:
		case NameManagerResult::DECLINED_EMPTY:
		case NameManagerResult::DECLINED_SYNTAX:
			creature->sendSystemMessage("@player_structure:not_valid_name"); // That is not a valid name.
			return;
			break;
		case NameManagerResult::ACCEPTED:
			break;
		}

		CityManager* cityManager = server->getCityManager();
		PlanetManager* planetManager = zone->getPlanetManager();

		if (!planetManager->validateRegionName(cityName) || !cityManager->validateCityName(cityName)) {
			creature->sendSystemMessage("@player_structure:cityname_not_unique"); //Another city already has this name. Your city's name must be unique.
			return;
		}

		ManagedReference<CityRegion*> cityObject = city.get();

		if(cityObject->getMayorID() != creature->getObjectID())
			return;

		Locker mlock(cityManager, creature);

		if(!cityManager->renameCity(cityObject, cityName))
			return;

		mlock.release();

		Locker clock(cityObject, creature);

		String oldName = cityObject->getRegionName();
		bool isRegistered = cityObject->isRegistered();

		if(isRegistered)
			cityManager->unregisterCity(cityObject, creature);

		cityObject->setCustomRegionName(cityName);

		if(cityObject->hasShuttleInstallation()) {
			Reference<PlanetTravelPoint*> tp = planetManager->getPlanetTravelPoint(oldName);

			if(tp != NULL) {
				Reference<PlanetTravelPoint*> newTP = tp;
				newTP->setPointName(cityName);
				planetManager->removePlayerCityTravelPoint(oldName);
				planetManager->addPlayerCityTravelPoint(newTP);
			}
		}
		if(isRegistered)
			cityManager->registerCity(cityObject, creature);

		creature->addCooldown("rename_city_cooldown", 604800 * 4); // 4 week cooldown.  need to investigate
		creature->sendSystemMessage("@city/city:name_changed"); // The city name has been successfully changed.");

	}
};




#endif /* RENAMECITYSUICALLBACK_H_ */
