/*
 * ScreenPlayTask.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef SCREENPLAYTASK_H_
#define SCREENPLAYTASK_H_

#include "DirectorManager.h"
#include "server/zone/managers/director/PersistentEvent.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/scene/SceneObject.h"

class ScreenPlayTask : public Task {
	ManagedWeakReference<SceneObject*> obj;
	String taskKey;
	String screenPlay;
	String args;
	Reference<PersistentEvent*> persistentEvent;
public:

	ScreenPlayTask(SceneObject* scno, const String& key, const String& playName, const String& arguments) {
		obj = scno;
		taskKey = key;
		screenPlay = playName;
		args = arguments;
		persistentEvent = NULL;
	}

	void run() {
		ZoneServer* zoneServer = ServerCore::getZoneServer();

		if (zoneServer == NULL || zoneServer->isServerShuttingDown())
			return;

		if (zoneServer->isServerLoading()) {
			schedule(10000);

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

	const String& getTaskKey() const {
		return taskKey;
	}

	const String& getScreenPlay() const {
		return screenPlay;
	}

	const String& getArgs() const {
		return args;
	}

	void setPersistentEvent(PersistentEvent* persistentEvent) {
		this->persistentEvent = persistentEvent;
	}

	Reference<PersistentEvent*>& getPersistentEvent() {
		return persistentEvent;
	}

	const Reference<PersistentEvent*>& getPersistentEvent() const {
		return persistentEvent;
	}

};

#endif /* SCREENPLAYTASK_H_ */
