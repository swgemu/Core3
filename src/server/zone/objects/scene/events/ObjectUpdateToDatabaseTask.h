/*
 * ObjectSaveToDatabaseTask.h
 *
 *  Created on: 16/08/2009
 *      Author: victor
 */

#ifndef OBJECTSAVETODATABASETASK_H_
#define OBJECTSAVETODATABASETASK_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
namespace events {

class ObjectUpdateToDatabaseTask : public Task {
	ManagedReference<SceneObject*> object;

public:
	ObjectUpdateToDatabaseTask(SceneObject* object) : Task(300000) {
		ObjectUpdateToDatabaseTask::object = object;
	}

	void run() {
		try {
			Locker locker(object);

			object->clearUpdateToDatabaseTask();
			object->updateToDatabase();
		} catch (Exception& e) {
			object->error(e.getMessage());
		}
	}
};


}
}
}
}
}

using namespace server::zone::objects::scene::events;

#endif /* OBJECTSAVETODATABASETASK_H_ */
