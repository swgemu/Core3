/*
 * PositionUpdateTask.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef POSITIONUPDATETASK_H_
#define POSITIONUPDATETASK_H_

#include "engine/engine.h"
#include "SceneObject.h"

class PositionUpdateTask : public Task {
	ManagedReference<SceneObject*> object;
	ManagedReference<QuadTreeEntry*> entry;
public:
	PositionUpdateTask(SceneObject* obj, QuadTreeEntry* ent) {
		object = obj;
		entry = ent;
	}

	void run() {
		Locker locker(object);

		Locker clocker(entry, object);

		object->notifyObservers(ObserverEventType::OBJECTINRANGEMOVED, entry);
	}
};


#endif /* POSITIONUPDATETASK_H_ */
