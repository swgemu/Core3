
#ifndef SCHEDULESHUTTLETASK_H_
#define SCHEDULESHUTTLETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

class ScheduleShuttleTask : public Task {
	ManagedWeakReference<CreatureObject*> shuttleObject;
	Zone* zone;

public:
	ScheduleShuttleTask(CreatureObject* shuttle, Zone* zon) : Task() {
		shuttleObject = shuttle;
		zone = zon;
	}

	void run() {
		if (zone->getZoneServer()->isServerLoading()) {
			schedule(1000);
			return;
		}

		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == nullptr) {
			return;
		}

		Locker _lock(strongReference);

		ManagedReference<PlanetManager*> planetManager = zone->getPlanetManager();

		if (planetManager == nullptr) {
			return;
		}

		ManagedReference<CityRegion*> cityRegion = strongReference->getCityRegion().get();

		if ((cityRegion != nullptr) && (cityRegion->getMayorID() != 0)) {
			float x = strongReference->getWorldPositionX();
			float y = strongReference->getWorldPositionY();
			float z = strongReference->getWorldPositionZ();

			Vector3 arrivalVector(x, y, z);

			String zoneName = zone->getZoneName();

			Locker clocker(cityRegion, strongReference);
			cityRegion->setShuttleID(strongReference->getObjectID());
			clocker.release();

			PlanetTravelPoint* planetTravelPoint = new PlanetTravelPoint(zoneName, cityRegion->getRegionName(), arrivalVector, arrivalVector, strongReference);
			planetManager->addPlayerCityTravelPoint(planetTravelPoint);
			planetManager->scheduleShuttle(strongReference, PlanetManager::SHUTTLEPORT);

		} else {
			Reference<PlanetTravelPoint*> ptp = planetManager->getNearestPlanetTravelPoint(strongReference, 128.f);

			if (ptp != nullptr) {
				auto oldShuttle = ptp->getShuttle();

				if (oldShuttle == nullptr) {
					if (ptp->isInterplanetary())
						planetManager->scheduleShuttle(strongReference, PlanetManager::STARPORT);
					else
						planetManager->scheduleShuttle(strongReference, PlanetManager::SHUTTLEPORT);

					ptp->setShuttle(strongReference);

				} else if (oldShuttle != strongReference) {
					strongReference->destroyObjectFromWorld(true);
					strongReference->destroyObjectFromDatabase(true);
				}
			}
		}
	}

};

#endif /* SCHEDULESHUTTLETASK_H_ */
