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

	if (parentPointer != NULL && parentPointer->isCellObject())
		parent = parentPointer->getObjectID();
	else
		parent = 0;
}

Vector3 ValidatedPosition::getWorldPosition(ZoneServer* zoneServer) {
	if (parent == 0)
		return point;

	Vector3 newWorldPosition;

	ManagedReference<SceneObject*> newParent = zoneServer->getObject(parent);

	if (newParent == NULL)
		return point;

	ManagedReference<SceneObject*> root = newParent->getRootParent();

	float length = Math::sqrt(point.getX() * point.getX() + point.getY() * point.getY());
	float angle = root->getDirection()->getRadians() + atan2(point.getX(), point.getY());

	newWorldPosition.set(root->getPositionX() + (sin(angle) * length), root->getPositionZ() + point.getZ(), root->getPositionY() + (cos(angle) * length));

	return newWorldPosition;
}
