/*
 * CircularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "CircularAreaShape.h"

bool CircularAreaShapeImplementation::containsPoint(float x, float y) {
	Vector3 position;
	position.set(x, 0, y);

	return (areaCenter.squaredDistanceTo(position) <= radius2);
}

bool CircularAreaShapeImplementation::containsPoint(const Vector3& point) {
	return (areaCenter.squaredDistanceTo(point) <= radius2);
}

Vector3 CircularAreaShapeImplementation::getRandomPosition() {
	int distance = System::random((int)radius);
	int angle = System::random(360) * Math::DEG2RAD;

	Vector3 position;
	position.set(distance * Math::cos(angle), 0, distance * Math::sin(angle));

	return position;
}

Vector3 CircularAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) {
	int distance = System::random((int)(maxDistance - minDistance)) + minDistance;
	int angle = System::random(360) * Math::DEG2RAD;

	Vector3 position;
	position.set(origin.getX() + distance * Math::cos(angle), 0, origin.getY() + distance * Math::sin(angle));

	return position;
}

bool CircularAreaShapeImplementation::intersectsWith(AreaShape* areaShape) {
	if (areaShape == NULL) {
		return false;
	}

	if (areaShape->isCircularAreaShape()) {
		ManagedReference<CircularAreaShape*> circle = cast<CircularAreaShape*>(areaShape);
		return intersectsWithCircle(circle);
	} else {
		return false;
	}
}

bool CircularAreaShapeImplementation::intersectsWithCircle(CircularAreaShape* circle) {
	float squaredRadiusSum = radius2 + circle->getRadius2();
	float squaredCenterDistance = areaCenter.squaredDistanceTo(circle->getAreaCenter());

	return (squaredCenterDistance <= squaredRadiusSum);
}
