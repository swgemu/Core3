/*
 * RectangularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "server/zone/objects/area/areashapes/RectangularAreaShape.h"
#include "server/zone/objects/area/areashapes/RingAreaShape.h"
#include "engine/util/u3d/Segment.h"

//#define DEBUG_POSITION

bool RectangularAreaShapeImplementation::containsPoint(float x, float y) const {
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
	info(true) << "Rectangle - getRandomPosition called";
#endif // DEBUG_POSITION

	Vector3 position;
	float distance = areaCenter.distanceTo(origin);
	float spawnDistanceDelta = System::random(maxDistance - minDistance);

	if (spawnDistanceDelta < minDistance)
		spawnDistanceDelta = minDistance;

	float dx = origin.getX() - areaCenter.getX();
	float dy = origin.getY() - areaCenter.getY();

#ifdef DEBUG_POSITION
	info(true) << "Rectangle - getRandomPosition -- spawnDistanceDelta = " << spawnDistanceDelta;
#endif // DEBUG_POSITION

	bool found = false;
	int retries = 5;

	while (!found && retries-- > 0) {
		position.setX(origin.getX() + System::random((spawnDistanceDelta * (dx / distance))));
		position.setY(origin.getY() + System::random((spawnDistanceDelta * (dy / distance))));

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
	if (point.distanceTo(position) > right.distanceTo(position)) {
		point = right;
	}

	if (point.distanceTo(position) > bottom.distanceTo(position)) {
		point = bottom;
	}

	if (point.distanceTo(position) > left.distanceTo(position)) {
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
	if (point.distanceTo(position) < topRight.distanceTo(position)) {
		point = topRight;
	}
	if (point.distanceTo(position) < bottomLeft.distanceTo(position)) {
		point = bottomLeft;
	}
	if (point.distanceTo(position) < bottomRight.distanceTo(position)) {
		point = bottomRight;
	}

	return point;
}

float RectangularAreaShapeImplementation::getRadius() const {
	return Math::sqrt(getHeight() * getHeight() + getWidth() * getWidth()) / 2;
}
