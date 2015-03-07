
#ifndef CITYREMOVEAMENITYTASK_H_
#define CITYREMOVEAMENITYTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/scene/SceneObject.h"

class CityRemoveAmenityTask : public Task {
	ManagedReference<SceneObject*> amenity;
	ManagedReference<CityRegion*> city;

public:
	CityRemoveAmenityTask(SceneObject* sceno, CityRegion* cityRegion) {
		amenity = sceno;
		city = cityRegion;
	}

	void run() {
		if (city == NULL || amenity == NULL)
			return;

		Locker locker(city);
		Locker clocker(amenity, city);

		if (amenity->isMissionTerminal())
			city->removeMissionTerminal(amenity);
		else
			city->removeSkillTrainers(amenity);

		amenity->destroyObjectFromWorld(true);
		amenity->destroyObjectFromDatabase(true);
	}
};

#endif /* CITYREMOVEAMENITYTASK_H_ */
