/*
 * RectangularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"
#include "engine/util/u3d/Segment.h"
#include "engine/log/Logger.h"

//#define DEBUG_POSITION

bool RectangularAreaShapeImplementation::containsPoint(float x, float y) const {
	// World Spawners are rectangles with no size
	if ((blX == 0) && (urX == 0) && (blY == 0) && (urY == 0)) {
		return true;
	}

	return (x >= blX) && (x <= urX) && (y >= blY) && (y <= urY);
}

bool RectangularAreaShapeImplementation::containsPoint(const Vector3& point) const {
	return containsPoint(point.getX(), point.getY());
}

Vector3 RectangularAreaShapeImplementation::getRandomPosition() const {
	float width = getWidth();
	float height = getHeight();
	int x = System::random(width);
	int y = System::random(height);
	Vector3 position;

	position.set(blX + x, 0, blY + y);

	return position;
}

Vector3 RectangularAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) const {
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
		info(true) << "Checking Position: " << position.toString() << " Bottom Left X = " << blX << " Bottom Left Y = " << blY << " Upper right X = " << urX << " Upper rigth Y = " << urY;
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

bool RectangularAreaShapeImplementation::intersectsWith(AreaShape* areaShape) const {
	if (areaShape->isRingAreaShape()) {
		auto ring = cast<RingAreaShape*>(areaShape);
		Vector3 center = ring->getAreaCenter();

		if (ring->getOuterRadius2() < center.squaredDistanceTo(getClosestPoint(center))) // wholly outside the ring
			return false;
		else if (ring->getInnerRadius2() > center.squaredDistanceTo(getFarthestPoint(center))) // wholly inside the ring's inner circle
			return false;
		else
			return true;
	} else
		return areaShape->containsPoint(getClosestPoint(areaShape->getAreaCenter()));
}

Vector3 RectangularAreaShapeImplementation::getClosestPoint(const Vector3& position) const {
	// Calculate corners.
	Vector3 topLeft, topRight, bottomLeft, bottomRight;
	topLeft.set(blX, 0, urY);
	topRight.set(urX, 0, urY);
	bottomLeft.set(blX, 0, blY);
	bottomRight.set(urX, 0, blY);

	// Find closest point on each side.
	Segment topSegment(topLeft, topRight);
	Segment rightSegment(topRight, bottomRight);
	Segment bottomSegment(bottomRight, bottomLeft);
	Segment leftSegment(bottomLeft, topLeft);

	Vector3 top, right, bottom, left;
	top = topSegment.getClosestPointTo(position);
	right = rightSegment.getClosestPointTo(position);
	bottom = bottomSegment.getClosestPointTo(position);
	left = leftSegment.getClosestPointTo(position);

	// Find the closes of the four side points.
	Vector3 point = top;
	if (point.squaredDistanceTo(position) > right.squaredDistanceTo(position)) {
		point = right;
	}

	if (point.squaredDistanceTo(position) > bottom.squaredDistanceTo(position)) {
		point = bottom;
	}

	if (point.squaredDistanceTo(position) > left.squaredDistanceTo(position)) {
		point = left;
	}

	return point;
}

Vector3 RectangularAreaShapeImplementation::getFarthestPoint(const Vector3& position) const {
	// Calculate corners.
	Vector3 topLeft, topRight, bottomLeft, bottomRight;
	topLeft.set(blX, 0, urY);
	topRight.set(urX, 0, urY);
	bottomLeft.set(blX, 0, blY);
	bottomRight.set(urX, 0, blY);

	// Find the farthest of the four corners.
	Vector3 point = topLeft;
	if (point.squaredDistanceTo(position) < topRight.squaredDistanceTo(position)) {
		point = topRight;
	}
	if (point.squaredDistanceTo(position) < bottomLeft.squaredDistanceTo(position)) {
		point = bottomLeft;
	}
	if (point.squaredDistanceTo(position) < bottomRight.squaredDistanceTo(position)) {
		point = bottomRight;
	}

	return point;
}

float RectangularAreaShapeImplementation::getRadius() const {
	float rad = Math::sqrt(getHeight() * getHeight() + getWidth() * getWidth()) / 2;

	return rad;
}
