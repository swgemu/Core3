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
	Vector3 top, right, bottom, left;
	top = getClosestPointOnLine(topLeft, topRight, position);
	right = getClosestPointOnLine(topRight, bottomRight, position);
	bottom = getClosestPointOnLine(bottomRight, bottomLeft, position);
	left = getClosestPointOnLine(bottomLeft, topLeft, position);

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

Vector3 RectangularAreaShapeImplementation::getClosestPointOnLine(const Vector3& coordinate1, const Vector3& coordinate2, const Vector3& position) {
	// Calculate line equation. n * y = m * x + c
	// lineVector x = n, y = m, z = c
	Vector3 lineVector = coordinate1 - coordinate2;
	lineVector.setZ(lineVector.getY() * coordinate1.getY() - lineVector.getX() * coordinate1.getX());

	// Calculate the orthogonal line equation. m * y = -n * x + d -> o * y = p * x + d
	// Orthogonal line equationVector equation
	Vector3 orthogonalLineVector;
	orthogonalLineVector.set(lineVector.getY(), 0, -lineVector.getX());
	orthogonalLineVector.setZ(orthogonalLineVector.getY() * position.getY() - orthogonalLineVector.getX() * position.getX());

	// Find the point where the two lines cross each other.
	// Find the x coordinate.
	int x;
	if (lineVector.getY() == 0 || orthogonalLineVector.getY() == 0) {
		x = position.getX();
	} else {
		//n * y = m * x + c -> y = m / n * x + c / n
		//o * y = p * x + d -> y = p / o * x + d / o
		// (m / n + p / o) * x = d / o - c / n - > x = (d / o - c / n) / (m / n + p / o)
		x = ((orthogonalLineVector.getZ() / orthogonalLineVector.getY()) - (lineVector.getZ() / lineVector.getY())) /
				((lineVector.getX() / lineVector.getY()) + (orthogonalLineVector.getX() / orthogonalLineVector.getY()));
	}
	// Calculate the y coordinate.
	int y = (lineVector.getX() * x + lineVector.getZ()) / lineVector.getY();

	// Check if the point is on the line between the coordinates or select the closest one.
	Vector3 point;
	point.set(x, 0, y);
	float lineLength = coordinate1.distanceTo(coordinate2);
	float distance1 = point.distanceTo(coordinate1);
	float distance2 = point.distanceTo(coordinate2);
	if (distance1 < lineLength && distance2 < lineLength) {
		// Point is on the line, finished.
		return point;
	} else {
		// Point is not on the line, return the closest coordinate.
		if (distance1 < distance2) {
			return coordinate1;
		} else {
			return coordinate2;
		}
	}
}
