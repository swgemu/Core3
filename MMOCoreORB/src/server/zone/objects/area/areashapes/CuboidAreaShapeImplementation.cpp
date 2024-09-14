/*
 * CuboidAreaShapeImplementation.cpp
 *
 * Created: 12/30/2023
 * Author: Hakry
 */

#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"

// #define DEBUG_POSITION
// #define DEBUG_CUBOID

void CuboidAreaShapeImplementation::setDimensions(float len, float wid, float hght) {
	length = len;
	width = wid;
	height = hght;

	// Set the cuboid contraints
	auto centerPos = getAreaCenter();

	minX = centerPos.getX() - (length / 2);
	maxX = centerPos.getX() + (length / 2);
	minY = centerPos.getY() - (width / 2);
	maxY = centerPos.getY() + (width / 2);
	minZ = centerPos.getZ() - (height / 2);
	maxZ = centerPos.getZ() + (height / 2);
}

bool CuboidAreaShapeImplementation::containsPoint(float x, float z, float y) const {
	bool containsTest = (x > minX && x < maxX) && (y > minY && y < maxY) && (z > minZ && z < maxZ);

#ifdef DEBUG_CUBOID
	StringBuffer msg;

	msg << "containsPoint --- for Cuboid: " << (containsTest ? "TRUE" : "FALSE");
	msg << " Point - X = " << x << " Z = " << z << " Y = " << y;
	msg << " minX = " << minX << " minZ = " << minZ << " minY = " << minY;
	msg << " maxX = " << maxX << " maxZ = " << maxZ << " maxY = " << maxY;

	info(true) << msg.toString();
#endif

	return containsTest;
}

bool CuboidAreaShapeImplementation::containsPoint(const Vector3& point) const {
	return (point.getX() > minX && point.getX() < maxX) && (point.getY() > minY && point.getY() < maxY) && (point.getZ() > minZ && point.getZ() < maxZ);
}

Vector3 CuboidAreaShapeImplementation::getRandomPosition() const {
	Vector3 position = getAreaCenter();

	position.setX(System::random(width) + position.getX());
	position.setY(System::random(length) + position.getY());
	position.setZ(System::random(height) + position.getZ());

	return position;
}

Vector3 CuboidAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) const {
#ifdef DEBUG_POSITION
	info(true) << "Cuboid - getRandomPosition called";
#endif // DEBUG_POSITION

	Vector3 position(areaCenter.getX(), areaCenter.getZ(), areaCenter.getY());
	bool found = false;
	int retries = 10;

	while (!found && retries-- > 0) {
		int halfLength = length / 2;
		int halfWidth = width / 2;
		int halfHeight = height / 2;

		float randLength = System::random(halfLength) * ((System::random(10) < 5) ? -1.f : 1.f);
		float randWidth = System::random(halfWidth) * ((System::random(10) < 5) ? -1.f : 1.f);
		float randHeight = System::random(halfHeight)  * ((System::random(10) < 5) ? -1.f : 1.f);

		position.setX(areaCenter.getX() + randLength);
		position.setY(areaCenter.getY() + randWidth);
		position.setZ(areaCenter.getZ() + randHeight);

		found = containsPoint(position);

#ifdef DEBUG_POSITION
		info(true) << "Cuboid - getRandomPosition -- Retries remaining: " << retries;
#endif // DEBUG_POSITION
	}

	if (!found) {
#ifdef DEBUG_POSITION
		info(true) << "Cuboid - Position not found !!!";
#endif // DEBUG_POSITION

		return areaCenter;
	}

	return position;
}

bool CuboidAreaShapeImplementation::intersectsWith(AreaShape* areaShape) const {
	if (areaShape == nullptr) {
		return false;
	}

	if (areaShape->isSphereAreaShape()) {
		auto sphere = dynamic_cast<SphereAreaShape*>(areaShape);

		if (sphere != nullptr)
			return intersectsWithSphere(sphere);
	} else if (areaShape->isCuboidAreaShape()) {
		auto cuboid = dynamic_cast<CuboidAreaShape*>(areaShape);

		if (cuboid != nullptr)
			return intersectsWithCuboid(cuboid);
	}

	return false;
}

bool CuboidAreaShapeImplementation::intersectsWithCuboid(CuboidAreaShape* cuboid) const {
	//float squaredRadiusSum = radius2 + circle->getRadius2();
	//float squaredCenterDistance = areaCenter.squaredDistanceTo(circle->getAreaCenter());

	return true;;
}

bool CuboidAreaShapeImplementation::intersectsWithSphere(SphereAreaShape* sphere) const {
	//float squaredRadiusSum = radius2 + circle->getRadius2();
	//float squaredCenterDistance = areaCenter.squaredDistanceTo(circle->getAreaCenter());

	return true;;
}

float CuboidAreaShapeImplementation::getRadius() const {
	float rad = (length > width ? length : width);
	return (rad > height ? rad : height);
}

Vector3 CuboidAreaShapeImplementation::getCuboidDimensions() const {
	Vector3 dimensions(length, width, height);

	return dimensions;
}

String CuboidAreaShapeImplementation::getDimensionLog() {
	StringBuffer msg;

	msg << "====== CuboidAreaShape INFO ======\n";
	msg << "Length: " << length << "\n";
	msg << "Width: " << width << "\n";
	msg << "Height: " << height << "\n";

	return msg.toString();
}