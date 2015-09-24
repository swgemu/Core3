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
#include "server/zone/managers/director/PersistentEvent.h"

#include "server/zone/objects/scene/SceneObject.h"

class ScreenPlayTask : public Task {
	ManagedWeakReference<SceneObject*> obj;
	String taskKey;
	String screenPlay;
	Reference<PersistentEvent*> persistentEvent;
public:

	ScreenPlayTask(SceneObject* scno, const String& key, const String& playName) {
		obj = scno;
		taskKey = key;
		screenPlay = playName;
		persistentEvent = NULL;
	}

	void run() {
		ZoneServer* zoneServer = ServerCore::getZoneServer();

		if (zoneServer != NULL && zoneServer->isServerLoading()) {
			schedule(1000);

			return;
		}

		ManagedReference<SceneObject*> obj = this->obj.get();

		if (obj != NULL) {
			Locker locker(obj);

			DirectorManager::instance()->activateEvent(this);
		} else {
			DirectorManager::instance()->activateEvent(this);
		}
	}

	ManagedReference<SceneObject*> getSceneObject() {
		return obj.get();
	}

	String getTaskKey() {
		return taskKey;
	}

	String getScreenPlay() {
		return screenPlay;
	}

	void setPersistentEvent(PersistentEvent* persistentEvent) {
		this->persistentEvent = persistentEvent;
	}

	Reference<PersistentEvent*> getPersistentEvent() {
		return persistentEvent;
	}

};

#endif /* SCREENPLAYTASK_H_ */
