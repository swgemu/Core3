#include "SceneObject.h"

SceneObject::SceneObject(uint64 oid) {
	objectID = oid;

	movementCounter = 0;
}

SceneObject::SceneObject(uint64 oid, uint32 ocrc) {
	objectID = oid;
	objectCRC = ocrc;

	movementCounter = 0;

	//status = 0;
}
