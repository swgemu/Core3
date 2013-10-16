/*
 * AreaShapeImplementation.cpp
 *
 *  Created on: Oct 31, 2012
 *      Author: loshult
 */

#include "server/zone/objects/area/areashapes/AreaShape.h"

Vector3 AreaShapeImplementation::getRandomPosition() {
	Vector3 position;
	return position;
}

Vector3 AreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) {
	if (containsPoint(origin)) {
		return origin;
	} else {
		Vector3 position;
		return origin;
	}
}

Vector3 AreaShapeImplementation::getAreaCenter() {
	return areaCenter;
}
