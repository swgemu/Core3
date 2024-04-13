
#ifndef SCHEDULESHUTTLETASK_H_
#define SCHEDULESHUTTLETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

class ScheduleShuttleTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> shuttleObject;
	Zone* zone;

public:
	ScheduleShuttleTask(CreatureObject* shuttle, Zone* zon) : Task() {
		shuttleObject = shuttle;
		zone = zon;

		Logger::setLoggingName("ScheduleShuttleTask");
	}

	void run() {
		if (zone == nullptr) {
			error() << " zone has a nullptr.";
			return;
		}

		auto zoneServer = zone->getZoneServer();

		if (zoneServer == nullptr) {
			error() << " zoneServer is nullptr.";
			return;
		}

		if (zoneServer->isServerLoading()) {
			schedule(1000);
			return;
		}

		ManagedReference<CreatureObject*> strongShuttle = shuttleObject.get();

		if (strongShuttle == nullptr) {
			error() << " Shuttle strongShuttle has a nullptr in Zone: " << zone->getZoneName();
			return;
		}

		Locker lock(strongShuttle);

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			zone->error() << " planetManager has a nullptr in Zone: " << zone->getZoneName();
			return;
		}

		ManagedReference<CityRegion*> cityRegion = strongShuttle->getCityRegion().get();

		// Player City
		if ((cityRegion != nullptr) && !cityRegion->isClientRegion()) {
			float x = strongShuttle->getWorldPositionX();
			float y = strongShuttle->getWorldPositionY();
			float z = strongShuttle->getWorldPositionZ();

			Vector3 arrivalVector(x, y, z);

			String zoneName = zone->getZoneName();

			Locker clocker(cityRegion, strongShuttle);

			cityRegion->setShuttleID(strongShuttle->getObjectID());
			clocker.release();

			PlanetTravelPoint* planetTravelPoint = new PlanetTravelPoint(zoneName, cityRegion->getCityRegionName(), arrivalVector, arrivalVector, strongShuttle, 6.f);

			planetManager->addPlayerCityTravelPoint(planetTravelPoint);
			planetManager->scheduleShuttle(strongShuttle, PlanetManager::SHUTTLEPORT);
		} else {
			Reference<PlanetTravelPoint*> travelPoint = planetManager->getNearestPlanetTravelPoint(strongShuttle, 128.f);

			if (travelPoint == nullptr) {
				error() << " Planet Travel Point (travelPoint) has a nullptr in Zone: " << zone->getZoneName();
				return;
			}

			auto oldShuttle = travelPoint->getShuttle();

			if (oldShuttle == nullptr) {
				travelPoint->setShuttle(strongShuttle);

				if (travelPoint->isInterplanetary()) {
					planetManager->scheduleShuttle(strongShuttle, PlanetManager::STARPORT);
				} else {
					planetManager->scheduleShuttle(strongShuttle, PlanetManager::SHUTTLEPORT);
				}
			} else if (oldShuttle != strongShuttle) {
				strongShuttle->destroyObjectFromWorld(true);
				strongShuttle->destroyObjectFromDatabase(true);
			}
		}
	}
};

#endif /* SCHEDULESHUTTLETASK_H_ */
