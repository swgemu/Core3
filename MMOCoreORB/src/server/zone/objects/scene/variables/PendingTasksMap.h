/*
 * PendingTasksMap.h
 *
 *  Created on: 04/05/2010
 *      Author: victor
 */

#ifndef PENDINGTASKSMAP_H_
#define PENDINGTASKSMAP_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}
}
}
}


class PendingTasksMap : public Object {
protected:
	Mutex mutex;

	VectorMap<String, Reference<Task*> > taskMap;

	ArrayList<Reference<Task*> > orderedTasks;

public:
	PendingTasksMap();

	PendingTasksMap(const PendingTasksMap& p);

	int put(const String& name, Task* task);

	void drop(const String& name);

	bool contains(const String& name);

	Reference<Task*> get(const String& name);

	void putOrdered(Task* task, server::zone::objects::scene::SceneObject* sceneObject);

	int getOrderedTasksSize();

	bool runMoreOrderedTasks(server::zone::objects::scene::SceneObject* sceneObject);

	Reference<Task*> getNextOrderedTask();
};

#endif /* PENDINGTASKSMAP_H_ */
