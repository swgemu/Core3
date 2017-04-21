/*
 * ScreenPlayTask.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef SCREENPLAYTASK_H_
#define SCREENPLAYTASK_H_

#include "server/zone/managers/director/PersistentEvent.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"

#include "server/zone/objects/scene/SceneObject.h"

namespace server {
namespace zone {
namespace managers {
namespace director {

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

	void run();

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

} // namespace director
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::director;

#endif /* SCREENPLAYTASK_H_ */
