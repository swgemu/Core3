/*
 * MissionTargetMap.h
 *
 *  Created on: Aug 22, 2010
 *      Author: dannuic
 */

#ifndef MISSIONTARGETMAP_H_
#define MISSIONTARGETMAP_H_

#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"

class MissionTargetMap : public Object {
	SynchronizedSortedVector<Reference<SceneObject*> > missions;

public:
	MissionTargetMap() {
		missions.setNoDuplicateInsertPlan();
	}

	/*int put(SceneObject* mission) {
		return missions.put(mission);
	}*/

	bool add(SceneObject* mission) {
		return missions.put(mission);
	}

	bool remove(SceneObject* mission) {
		return missions.drop(mission);
	}

	int size() {
		return missions.size();
	}

	SceneObject* getRandomTarget(SceneObject* origin, int diff) {
		SceneObject* result = nullptr;
		Zone* zone = origin->getZone();

		float distance = 16000.f;
		Coordinate coord(origin->getPositionX(), origin->getPositionZ(), origin->getPositionY());

		float randomForCord = 1000 * pow(4.f, diff - 1);
		coord.randomizePosition((2.f * randomForCord), randomForCord);

		if (coord.getPositionX() > zone->getMaxX())
			coord.setPositionX(zone->getMaxX());
		if (coord.getPositionX() < zone->getMinX())
			coord.setPositionX(zone->getMinX());
		if (coord.getPositionY() > zone->getMaxY())
			coord.setPositionY(zone->getMaxY());
		if (coord.getPositionY() < zone->getMinY())
			coord.setPositionY(zone->getMinY());

		//rlock();

		try {
			for (int i = 0; i < missions.size(); ++i) {
				SceneObject* vectorObject = missions.get(i);
				if (vectorObject == nullptr)
					continue;

				float objDistance = vectorObject->getDistanceTo(&coord);

				if (objDistance < distance) {
					result = vectorObject;
					distance = objDistance;
				}
			}
		} catch (...) {
			throw;
		}

		//runlock();

		return result;
	}
};

#endif /* MISSIONTARGETMAP_H_ */
