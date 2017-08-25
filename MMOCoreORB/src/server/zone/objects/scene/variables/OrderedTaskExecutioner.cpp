/*
 * OrderedTaskExecutioner.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: TheAnswer
 */

#include "OrderedTaskExecutioner.h"
#include "PendingTasksMap.h"

#include "server/zone/objects/scene/SceneObject.h"

using namespace server::zone::objects::scene::variables;
using namespace server::zone::objects::scene;

OrderedTaskExecutioner::OrderedTaskExecutioner(SceneObject* sceneObject) : sceneObject(sceneObject), taskName(nullptr) {

}

void OrderedTaskExecutioner::run() {
	Reference<SceneObject*> strongReference = sceneObject.get();

	if (strongReference == NULL)
		return;

	//no lock on getPendingTasks() is safe due to using the container lock

	PendingTasksMap* pendingTasks = strongReference->getPendingTasks();

	Reference<Task*> task = pendingTasks->getNextOrderedTask();

	if (task != NULL) {
		try {
			task->run();
		} catch (Exception& exc) {
			strongReference->error("exception in OrderedTaskExecutioner::run");
			strongReference->error(exc.getMessage());

			exc.printStackTrace();
		} catch (...) {
			strongReference->error("uncaught exception in OrderedTaskExecutioner::run");
		}

		pendingTasks->runMoreOrderedTasks(strongReference);

		taskName = task->getTaskName();
	}
}

const char* OrderedTaskExecutioner::getTaskName() {
	if (taskName) {
		return taskName;
	} else {
		return Task::getTaskName();
	}
}
