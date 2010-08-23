/*
 * MissionTargetMap.h
 *
 *  Created on: Aug 22, 2010
 *      Author: dannuic
 */

#ifndef MISSIONTARGETMAP_H_
#define MISSIONTARGETMAP_H_

#include "engine/engine.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"

class MissionTargetMap : public SortedVector<SceneObject*>, public ReadWriteLock {
public:
	MissionTargetMap() {

		setNoDuplicateInsertPlan();
	}

	SceneObject* getRandomTarget(SceneObject* origin, int diff) {
		SceneObject* result = NULL;
		Zone* zone = origin->getZone();

		float distance = 16000.f;
		Coordinate coord(origin->getPositionX(), origin->getPositionZ(), origin->getPositionY());
		coord.randomizePosition(1000 * pow(4, diff - 1));

		if (coord.getPositionX() > origin->getZone()->getMaxX())
			coord.setPositionX(origin->getZone()->getMaxX());
		if (coord.getPositionX() < origin->getZone()->getMinX())
			coord.setPositionX(origin->getZone()->getMinX());
		if (coord.getPositionY() > origin->getZone()->getMaxY())
			coord.setPositionY(origin->getZone()->getMaxY());
		if (coord.getPositionY() < origin->getZone()->getMinY())
			coord.setPositionY(origin->getZone()->getMinY());

		rlock();

		try {
			for (int i = 0; i < size(); ++i) {
				SceneObject* vectorObject = get(i);
				if (vectorObject == NULL)
					continue;

				float objDistance = vectorObject->getDistanceTo(&coord);

				if (objDistance < distance) {
					result = vectorObject;
					distance = objDistance;
				}
			}
		} catch (...) {

		}

		runlock();

		return result;
	}
};

#endif /* MISSIONTARGETMAP_H_ */
