
#include "server/zone/objects/area/areashapes/RingAreaShape.h"
#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/CircularAreaShape.h"

bool RingAreaShapeImplementation::containsPoint(float x, float y) const {
	Vector3 position;
	position.set(x, 0, y);

	return ((areaCenter.squaredDistanceTo(position) <= outerRadius2) && (areaCenter.squaredDistanceTo(position) >= innerRadius2));
}

bool RingAreaShapeImplementation::containsPoint(const Vector3& point) const {
	return ((areaCenter.squaredDistanceTo(point) <= outerRadius2) && (areaCenter.squaredDistanceTo(point) >= innerRadius2));
}

Vector3 RingAreaShapeImplementation::getRandomPosition() const {
	float distance = System::random((int)(outerRadius - innerRadius)) + innerRadius;
	float angle = System::random(360) * Math::DEG2RAD;

	Vector3 position;
	position.set(areaCenter.getX() + distance * Math::cos(angle), 0, areaCenter.getY() + distance * Math::sin(angle));

	return position;
}

Vector3 RingAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) const {
#ifdef DEBUG_POSITION
	info(true) << "getRandomPosition called";
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
		info(true) << "Checking Position: " << position.toString();
#endif // DEBUG_POSITION

		found = containsPoint(position);
	}

	if (!found) {
#ifdef DEBUG_POSITION
		info(true) << "Rectangle - Position not found!!!";
#endif // DEBUG_POSITION

		position.set(0, 0, 0);
		return position;
	}

	return position;
}

bool RingAreaShapeImplementation::intersectsWith(AreaShape* areaShape) const {
	if (areaShape == nullptr) {
		return false;
	}

	if (areaShape->isRectangularAreaShape()) {
		auto rectangle = cast<RectangularAreaShape*>(areaShape);
		return rectangle->intersectsWith(_this.getReferenceUnsafeStaticCast());
	} else if (areaShape->isCircularAreaShape()) {
		auto circle = cast<CircularAreaShape*>(areaShape);
		return intersectsWithCircle(circle);
	} else if (areaShape->isRingAreaShape()) {
		auto ring = cast<RingAreaShape*>(areaShape);
		return intersectsWithRing(ring);
	} else {
		return false;
	}
}

bool RingAreaShapeImplementation::intersectsWithCircle(CircularAreaShape* circle) const {
	float squaredCenterDistance = areaCenter.squaredDistanceTo(circle->getAreaCenter());

	if (squaredCenterDistance > outerRadius2) { // circle center is outside the outer ring
		if (squaredCenterDistance > (outerRadius2 + circle->getRadius2())) // circle does not overlap
			return false;
	} else if (squaredCenterDistance < innerRadius2) { // circle center is inside the inner ring
		if ((squaredCenterDistance + circle->getRadius2()) < innerRadius2) // circle is wholly within ring's inner circle
			return false;
	}

	return true;
}

bool RingAreaShapeImplementation::intersectsWithRing(RingAreaShape* ring) const {
	float squaredCenterDistance = areaCenter.squaredDistanceTo(ring->getAreaCenter());

	if (squaredCenterDistance > outerRadius2) { // ring center is outside the outer ring
		if (squaredCenterDistance > (outerRadius2 + ring->getOuterRadius2())) // ring outer edges are away from each other
			return false;
		else if ((squaredCenterDistance + outerRadius2) < ring->getInnerRadius2()) // ring's inner circle wholly encompasses this ring
			return false;
	} else if (squaredCenterDistance < innerRadius2) { // ring center is inside the inner ring
		if ((squaredCenterDistance + ring->getOuterRadius2()) < innerRadius2) // ring is wholly encompassed in inner ring
			return false;
		else if((squaredCenterDistance + outerRadius2) < ring->getInnerRadius2()) // ring's inner circle wholly encompasses this ring
			return false;
	}

	return true;
}

float RingAreaShapeImplementation::getArea() const {
	return (Math::PI * outerRadius2 - Math::PI * innerRadius2);
}
