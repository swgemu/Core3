#ifndef SCENEOBJECT_H_
#define SCENEOBJECT_H_

#include "engine/engine.h"

class SceneObject : public Mutex {
protected:
	uint64 objectID;
	uint32 objectCRC;

	uint32 movementCounter;

public:
	SceneObject(uint64 oid);

	SceneObject(uint64 oid, uint32 ocrc);

	inline void setPosition(float x, float y, float z) {
	}

	inline uint64 getObjectID() {
		return objectID;
	}

	inline float getPositionX() {
		return 0;
	}

	inline float getPositionY() {
		return 0;
	}

	inline float getPositionZ() {
		return 0;
	}

	inline uint32 getMovementCounter() {
		return movementCounter++;
	}
};

#endif /*SCENEOBJECT_H_*/
