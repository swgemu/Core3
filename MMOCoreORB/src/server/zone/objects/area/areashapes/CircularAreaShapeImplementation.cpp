/*
 * CircularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"

bool CircularAreaShapeImplementation::containsPoint(float x, float y) const {
	Vector3 position;
	position.set(x, 0, y);

	return (areaCenter.squaredDistanceTo(position) <= radius2);
}

bool CircularAreaShapeImplementation::containsPoint(const Vector3& point) const {
	return (areaCenter.squaredDistanceTo(point) <= radius2);
}

Vector3 CircularAreaShapeImplementation::getRandomPosition() const {
	float distance = System::random((int)radius);
	float angle = System::random(360) * Math::DEG2RAD;

	Vector3 position;
	position.set(areaCenter.getX() + distance * Math::cos(angle), 0, areaCenter.getY() + distance * Math::sin(angle));

	return position;
}

Vector3 CircularAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) const {
	Vector3 position;
	bool found = false;
	int retries = 5;

	while (!found && retries-- > 0) {
		float distance = System::random((int)(maxDistance - minDistance)) + minDistance;
		float angle = System::random(360) * Math::DEG2RAD;
		position.set(origin.getX() + distance * Math::cos(angle), 0, origin.getY() + distance * Math::sin(angle));

		found = containsPoint(position);
	}

	if (!found)
		return getRandomPosition();

	return position;
}

bool CircularAreaShapeImplementation::intersectsWith(AreaShape* areaShape) const {
	if (areaShape == nullptr) {
		return false;
	}

	if (areaShape->isCircularAreaShape()) {
		auto circle = dynamic_cast<CircularAreaShape*>(areaShape);
		return intersectsWithCircle(circle);
	} else if (areaShape->isRectangularAreaShape()) {
		auto rectangle = dynamic_cast<RectangularAreaShape*>(areaShape);
		return rectangle->intersectsWith(_this.getReferenceUnsafeStaticCast());
	} else if (areaShape->isRingAreaShape()) {
		auto ring = dynamic_cast<RingAreaShape*>(areaShape);
		return ring->intersectsWith(_this.getReferenceUnsafeStaticCast());
	} else {
		return false;
	}
}

bool CircularAreaShapeImplementation::intersectsWithCircle(CircularAreaShape* circle) const {
	float squaredRadiusSum = radius2 + circle->getRadius2();
	float squaredCenterDistance = areaCenter.squaredDistanceTo(circle->getAreaCenter());

	return (squaredCenterDistance <= squaredRadiusSum);
}

float CircularAreaShapeImplementation::getArea() const {
	return Math::PI * radius2;
}
