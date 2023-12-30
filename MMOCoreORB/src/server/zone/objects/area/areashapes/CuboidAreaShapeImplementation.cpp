/*
 * CuboidAreaShapeImplementation.cpp
 *
 * Created: 12/30/2023
 * Author: Hakry
 */

#include "server/zone/objects/area/areashapes/CuboidAreaShape.h"
#include "server/zone/objects/area/areashapes/SphereAreaShape.h"

//#define DEBUG_POSITION

bool CuboidAreaShapeImplementation::containsPoint(const Vector3& point) const {
	//return (areaCenter.squaredDistanceTo(point) <= radius2);

	return false;
}

Vector3 CuboidAreaShapeImplementation::getRandomPosition() const {
	//float distance = System::random((int)radius);
	//float angle = System::random(360) * Math::DEG2RAD;

	Vector3 position;
	//position.set(areaCenter.getX() + distance * Math::cos(angle), 0, areaCenter.getY() + distance * Math::sin(angle));

	return position;
}

Vector3 CuboidAreaShapeImplementation::getRandomPosition(const Vector3& origin, float minDistance, float maxDistance) const {
#ifdef DEBUG_POSITION
	info(true) << "Cuboid - getRandomPosition called";
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
		info(true) << "Cuboid - Position not found !!!";
#endif // DEBUG_POSITION

		position.set(0, 0, 0);
		return position;
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
