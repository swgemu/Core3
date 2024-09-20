/*
 * ValidatedPosition.cpp
 *
 *  Created on: 27/11/2010
 *      Author: victor
 */

#include "ValidatedPosition.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"

void ValidatedPosition::update(SceneObject* object) {
	point = object->getPosition();

	ManagedReference<SceneObject*> parentPointer = object->getParent().get();

	if (parentPointer != nullptr && (parentPointer->isCellObject() || parentPointer->isValidJtlParent())) {
		parent = parentPointer->getObjectID();
	} else {
		parent = 0;
	}
}

Vector3 ValidatedPosition::getWorldPosition(ZoneServer* zoneServer) {
	if (parent == 0) {
		return point;
	}

	ManagedReference<SceneObject*> newParent = zoneServer->getObject(parent);

	if (newParent == nullptr) {
		return point;
	}

	ManagedReference<SceneObject*> root = newParent->getRootParent();

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
