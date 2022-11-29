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
	RenameCitySuiCallback(Zone* zone, CityRegion* city) : SuiCallback(zone->getZoneServer()) {
		this->zne = zone;
		this->city = city;
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if(cancelPressed || server == nullptr)
			return;

		ManagedReference<CityRegion*> cityRegion = city.get();
		if(cityRegion == nullptr)
			return;

		ManagedReference<Zone*> zone = this->zne.get();
		if (zone == nullptr)
			return;

		PlayerObject* ghost = creature->getPlayerObject();
		if (ghost == nullptr)
			return;

		String cityName = args->get(0).toString();

		ZoneProcessServer* zps = creature->getZoneProcessServer();
		NameManager* nameManager = zps->getNameManager();

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

		if(cityRegion->getMayorID() != creature->getObjectID() && !ghost->isStaff())
			return;

		Locker mlock(cityManager, creature);

		if(!cityManager->renameCity(cityRegion, cityName))
			return;

		mlock.release();

		Locker clock(cityRegion, creature);

		String oldName = cityRegion->getCityRegionName();
		bool isRegistered = cityRegion->isRegistered();

		if(isRegistered)
			cityManager->unregisterCity(cityRegion, creature);

		cityRegion->setCustomRegionName(cityName);

		if(cityRegion->hasShuttleInstallation()) {
			Reference<PlanetTravelPoint*> tp = planetManager->getPlanetTravelPoint(oldName);

			if(tp != nullptr) {
				Reference<PlanetTravelPoint*> newTP = tp;
				newTP->setPointName(cityName);
				planetManager->removePlayerCityTravelPoint(oldName);
				planetManager->addPlayerCityTravelPoint(newTP);
			}
		}

		if(isRegistered)
			cityManager->registerCity(cityRegion, creature);

		creature->addCooldown("rename_city_cooldown", 604800 * 4); // 4 week cooldown.  need to investigate
		creature->sendSystemMessage("@city/city:name_changed"); // The city name has been successfully changed.");
	}
};




#endif /* RENAMECITYSUICALLBACK_H_ */
