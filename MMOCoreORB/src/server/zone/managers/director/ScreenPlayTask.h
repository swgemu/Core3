/*
 * ScreenPlayTask.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef SCREENPLAYTASK_H_
#define SCREENPLAYTASK_H_

#include "engine/engine.h"
#include "DirectorManager.h"

#include "server/zone/objects/scene/SceneObject.h"

class ScreenPlayTask : public Task {
	ManagedReference<SceneObject*> obj;
	String taskKey;
	String screenPlay;
public:

	ScreenPlayTask(SceneObject* scno, const String& key, const String& playName) {
		obj = scno;
		taskKey = key;
		screenPlay = playName;
	}

	void run() {
		if (obj != NULL) {
			Locker locker(obj.get());
		}

		DirectorManager::instance()->activateEvent(this);
	}

	inline SceneObject* getSceneObject() {
		return obj;
	}

	String getTaskKey() {
		return taskKey;
	}

	String getScreenPlay() {
		return screenPlay;
	}

};

#endif /* SCREENPLAYTASK_H_ */
