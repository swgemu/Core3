/*
 * EjectObjectEvent.h
 *
 *  Created on: 05/10/2012
 *      Author: victor
 */

#ifndef EJECTOBJECTEVENT_H_
#define EJECTOBJECTEVENT_H_

#include "engine/engine.h"

class EjectObjectEvent : public Task {
	ManagedReference<SceneObject*> object;
	float x, z, y;

public:
	EjectObjectEvent(SceneObject* obj, float x, float z, float y) {
		object = obj;
		this->x = x, this->y = y, this->z = z;
	}

	void run() {
		Locker locker(object);

		object->teleport(x, z, y);
	}
};


#endif /* EJECTOBJECTEVENT_H_ */
