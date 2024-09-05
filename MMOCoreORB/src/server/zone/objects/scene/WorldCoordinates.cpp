/*
 * WorldCoordinate.cpp
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#include "WorldCoordinates.h"
#include "server/zone/objects/cell/CellObject.h"

WorldCoordinates::WorldCoordinates() : Object() {
}

WorldCoordinates::WorldCoordinates(const WorldCoordinates& c) : Object() {
	point = c.point;
	cell = c.cell;
}

WorldCoordinates& WorldCoordinates::operator=(const WorldCoordinates& c) {
	if (this == &c) {
		return *this;
	}

	point = c.point;
	cell = c.cell;

	return *this;
}

WorldCoordinates::WorldCoordinates(SceneObject* obj) : Object() {
	point = obj->getPosition();

	ManagedReference<CellObject*> parent = obj->getParent().get().castTo<CellObject*>();

	if (parent != nullptr && obj != parent) {
		cell = parent;
	}
}

WorldCoordinates::WorldCoordinates(const Vector3& position, CellObject* parent) : Object() {
	point = position;

	if (parent != nullptr) {
		cell = parent;
	}
}

WorldCoordinates::~WorldCoordinates() {
	cell = nullptr;
}

bool WorldCoordinates::toBinaryStream(ObjectOutputStream* stream) {
	point.toBinaryStream(stream);
	cell.toBinaryStream(stream);

	return true;
}

bool WorldCoordinates::parseFromBinaryStream(ObjectInputStream* stream) {
	point.parseFromBinaryStream(stream);
	cell.parseFromBinaryStream(stream);

	return true;
}

Vector3 WorldCoordinates::getWorldPosition() const {
	if (cell == nullptr) {
		return point;
	}

	SceneObject* root = cell->getRootParent();

	if (root == nullptr) {
		return point;
	}

	float rootRad = -root->getDirection()->getRadians();
	float rootCos = cos(rootRad);
	float rootSin = sin(rootRad);

	float localX = point.getX();
	float localY = point.getY();
	float localZ = point.getZ();

	float rotatedX = (localX * rootCos) - (localY * rootSin);
	float rotatedY = (localX * rootSin) + (localY * rootCos);

	float worldX = root->getPositionX() + rotatedX;
	float worldY = root->getPositionY() + rotatedY;
	float worldZ = root->getPositionZ() + localZ;

	return Vector3(worldX, worldY, worldZ);
}


bool WorldCoordinates::isInRange(const WorldCoordinates& obj, float range) const {
	Vector3 thisWorldPos = getWorldPosition();
	Vector3 objWorldPos = obj.getWorldPosition();

	return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
}
