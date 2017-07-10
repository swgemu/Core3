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
	if (this == &c)
		return *this;

	point = c.point;
	cell = c.cell;

	return *this;
}

WorldCoordinates::WorldCoordinates(SceneObject* obj) : Object() {
	point = obj->getPosition();

	ManagedReference<CellObject*> parent = obj->getParent().get().castTo<CellObject*>();

	if (parent != NULL && obj != parent)
		cell = parent;
}

WorldCoordinates::WorldCoordinates(const Vector3& position, CellObject* parent) : Object() {
	point = position;

	if (parent != NULL)
		cell = parent;
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
	if (cell == NULL)
		return point;

	SceneObject* root = cell->getRootParent();

	if (root == NULL)
		return point;

	float length = Math::sqrt(point.getX() * point.getX() + point.getY() * point.getY());
	float angle = root->getDirection()->getRadians() + atan2(point.getX(), point.getY());

	float posX = root->getPositionX() + (sin(angle) * length);
	float posY = root->getPositionY() + (cos(angle) * length);
	float posZ = root->getPositionZ() + point.getZ();

	Vector3 pos(posX, posY, posZ);

	return pos;
}


bool WorldCoordinates::isInRange(const WorldCoordinates& obj, float range) const {
	Vector3 thisWorldPos = getWorldPosition();
	Vector3 objWorldPos = obj.getWorldPosition();

	return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
}
