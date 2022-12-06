/*
 * CircularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "server/zone/objects/area/areashapes/CircularAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"

//#define DEBUG_POSITION

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
#ifdef DEBUG_POSITION
	info(true) << "Circle - getRandomPosition called";
#endif // DEBUG_POSITION

	Vector3 position;
	bool found = false;
	int retries = 10;

	while (!found && retries-- > 0) {
		float spawnDistanceDelta = System::random(maxDistance - minDistance);
		int randDirection = System::random(360);

		if (spawnDistanceDelta < minDistance)
			spawnDistanceDelta = minDistance;

		float xCalc = Math::cos(randDirection) - spawnDistanceDelta * Math::sin(randDirection);
		float yCalc = Math::sin(randDirection) - spawnDistanceDelta * Math::cos(randDirection);

		position.setX(origin.getX() + xCalc);
		position.setY(origin.getY() + yCalc);

#ifdef DEBUG_POSITION
		info(true) << " X Calc = " << xCalc << " Y Calc = " << yCalc << " Spawn Distance Delta = " << spawnDistanceDelta;
		info(true) << "Checking Position: " << position.toString() << "   Squared Distance: " << areaCenter.squaredDistanceTo(position) << "  Squared Radius = " << radius2;
#endif // DEBUG_POSITION

		found = containsPoint(position);
	}

	if (!found) {
#ifdef DEBUG_POSITION
		info(true) << "Circle - Position not found !!!";
#endif // DEBUG_POSITION

		position.set(0, 0, 0);
		return position;
	}

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
