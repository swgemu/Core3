
#ifndef CITYREMOVEAMENITYTASK_H_
#define CITYREMOVEAMENITYTASK_H_

#include "server/zone/objects/region/NewCityRegion.h"
#include "server/zone/objects/scene/SceneObject.h"

class CityRemoveAmenityTask : public Task {
	ManagedReference<SceneObject*> amenity;
	ManagedReference<NewCityRegion*> city;

public:
	CityRemoveAmenityTask(SceneObject* sceno, NewCityRegion* cityRegion) {
		amenity = sceno;
		city = cityRegion;
	}

	void run() {
		if (city == nullptr || amenity == nullptr)
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
