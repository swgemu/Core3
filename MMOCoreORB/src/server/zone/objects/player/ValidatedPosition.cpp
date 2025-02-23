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
	const auto currentPoint = getWorldPosition(object->getZoneServer());

	point = object->getPosition();

	ManagedReference<SceneObject*> parentPointer = object->getParent().get();

	if (parentPointer != nullptr && (parentPointer->isCellObject() || parentPointer->isValidJtlParent())) {
		parent = parentPointer->getObjectID();
	} else {
		parent = 0;
	}

	if (object->isPlayerCreature()) {
		const auto newPosition = object->getWorldPosition();

		float distance = newPosition.distanceTo2d(currentPoint);

		object->info(true) << object->getDisplayedName() << " Calling -- ValidatedPosition::update - To new position: " << newPosition.toString() << " Distance: " << distance << " Old Position: " << currentPoint.toString();

		if (distance > 100.f) {
			object->info(true) << "LARGE DISTANCE FOR ValidatedPosition - Distance: " << distance;

			//E3_ASSERT(((fabs(newPosition.getX() - 100.f) > 2.f) &&  (fabs(newPosition.getY() - 100.f) > 2.f)));
		}
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
