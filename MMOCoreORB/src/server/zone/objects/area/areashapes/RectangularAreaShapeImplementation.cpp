/*
 * CircularAreaShapeImplementation.cpp
 *
 *  Created on: 31/10/2012
 *      Author: loshult
 */

#include "RectangularAreaShape.h"
#include "engine/util/u3d/Segment.h"

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
	int x = System::random(width) - width / 2;
	int y = System::random(height) - height / 2;
	Vector3 position;

	position.set(areaCenter.getX() + x, 0, areaCenter.getY() + y);

	return position;
}

Vector3 RectangularAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) {
	bool found = false;
	Vector3 position;

	while (!found) {
		int distance = System::random((int)(maxDistance - minDistance)) + minDistance;
		int angle = System::random(360) * Math::DEG2RAD;
		position.set(origin.getX() + distance * Math::cos(angle), 0, origin.getY() + distance * Math::sin(angle));

		found = containsPoint(position);
	}

	return position;
}

bool RectangularAreaShapeImplementation::intersectsWith(AreaShape* areaShape) {
	return areaShape->containsPoint(getClosestPoint(areaShape->getAreaCenter()));
}

Vector3 RectangularAreaShapeImplementation::getClosestPoint(const Vector3& position) {
	// Calculate corners.
	Vector3 topLeft, topRight, bottomLeft, bottomRight;
	topLeft.set(areaCenter.getX() - width / 2, 0, areaCenter.getY() - height / 2);
	topRight.set(areaCenter.getX() + width / 2, 0, areaCenter.getY() - height / 2);
	bottomLeft.set(areaCenter.getX() - width / 2, 0, areaCenter.getY() + height / 2);
	bottomRight.set(areaCenter.getX() + width / 2, 0, areaCenter.getY() + height / 2);

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
