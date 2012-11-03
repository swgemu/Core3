/*
 * CircularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "RectangularAreaShape.h"

bool RectangularAreaShapeImplementation::containsPoint(float x, float y) {
	if ((x >= (areaCenter.getX() - width / 2)) && (x <= (areaCenter.getX() + width / 2)) &&
		(y >= (areaCenter.getY() - height / 2)) && (y <= (areaCenter.getY() + height / 2))) {
		return true;
	} else {
		return false;
	}
}

bool RectangularAreaShapeImplementation::containsPoint(const Vector3& point) {
	return containsPoint(point.getX(), point.getY());
}

Vector3 RectangularAreaShapeImplementation::getRandomPosition() {
	Vector3 position;
	return position;
}

Vector3 RectangularAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) {
	Vector3 position;
	return position;
}

bool RectangularAreaShapeImplementation::intersectsWith(AreaShape* areaShape) {
	return false;
}

bool RectangularAreaShapeImplementation::intersectsWithCircle(CircularAreaShape* circle) {
	return false;
}
