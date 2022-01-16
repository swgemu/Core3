/*
 * OrderedTaskExecutioner.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: TheAnswer

#include "OrderedTaskExecutioner.h"
#include "PendingTasksMap.h"

#include "server/zone/objects/scene/SceneObject.h"

using namespace server::zone::objects::scene::variables;
using namespace server::zone::objects::scene;

OrderedTaskExecutioner::OrderedTaskExecutioner(SceneObject* sceneObject) : sceneObject(sceneObject) {

}

void OrderedTaskExecutioner::run() {
	Reference<SceneObject*> strongReference = sceneObject.get();

	if (strongReference == nullptr)
		return;

	PendingTasksMap* pendingTasks = strongReference->getPendingTasks();
	auto poppedTaskData = pendingTasks->popNextOrderedTask();
	auto& task = poppedTaskData.first;

	if (task != nullptr) {
		try {
			task->run();
		} catch (Exception& exc) {
			strongReference->error("exception in OrderedTaskExecutioner::run");
			strongReference->error(exc.getMessage());

			exc.printStackTrace();
		} catch (...) {
			strongReference->error("uncaught exception in OrderedTaskExecutioner::run");
		}

		taskName = task->getTaskName();

		if (poppedTaskData.second) {
			Reference<OrderedTaskExecutioner*> nextTask = new OrderedTaskExecutioner(strongReference);
			nextTask->setCustomTaskQueue(nextTask->getCustomTaskQueue());
			nextTask->execute();
		}
	}
}

const char* OrderedTaskExecutioner::getTaskName() {
	if (!taskName.isEmpty()) {
		return taskName.toCharArray();
	} else {
		return Task::getTaskName();
	}
}
*/
