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

#include "server/zone/objects/creature/CreatureObject.h"

class ScreenPlayTask : public Task {
	ManagedReference<CreatureObject*> creature;
	String taskKey;
	String screenPlay;
public:

	ScreenPlayTask(CreatureObject* creo, const String& key, const String& playName) {
		creature = creo;
		taskKey = key;
		screenPlay = playName;
	}

	void run() {
		Locker locker(creature.get());

		DirectorManager::instance()->activateEvent(this);
	}

	inline CreatureObject* getCreatureObject() {
		return creature;
	}

	String getTaskKey() {
		return taskKey;
	}

	String getScreenPlay() {
		return screenPlay;
	}

};

#endif /* SCREENPLAYTASK_H_ */
