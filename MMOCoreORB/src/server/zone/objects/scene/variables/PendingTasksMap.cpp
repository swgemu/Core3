/*
 * PendingTasksMap.cpp
 *
 *  Created on: Apr 14, 2015
 *      Author: TheAnswer
 */

#include "server/zone/objects/scene/SceneObject.h"

#include "OrderedTaskExecutioner.h"

using namespace server::zone::objects::scene::variables;
using namespace server::zone::objects::scene;

PendingTasksMap::PendingTasksMap() : taskMap(1, 1), orderedTasks(1, 1) {
	taskMap.setNoDuplicateInsertPlan();
	taskMap.setNullValue(NULL);
}

PendingTasksMap::PendingTasksMap(const PendingTasksMap& p) : Object(), taskMap(p.taskMap), orderedTasks(p.orderedTasks) {
	taskMap.setNoDuplicateInsertPlan();
	taskMap.setNullValue(NULL);
}

int PendingTasksMap::put(const String& name, Task* task) {
	Locker guard(&mutex);

	return taskMap.put(name, task);
}

void PendingTasksMap::drop(const String& name) {
	Locker guard(&mutex);

	taskMap.drop(name);
}

bool PendingTasksMap::contains(const String& name) {
	Locker guard(&mutex);

	return taskMap.contains(name);
}

Reference<Task*> PendingTasksMap::get(const String& name) {
	Locker guard(&mutex);

	return taskMap.get(name);
}

void PendingTasksMap::putOrdered(Task* task, server::zone::objects::scene::SceneObject* sceneObject) {
	Locker guard(&mutex);

	orderedTasks.add(task);

	if (orderedTasks.size() == 1) {
		OrderedTaskExecutioner* newTask = new OrderedTaskExecutioner(sceneObject);
		newTask->setCustomTaskQueue(task->getCustomTaskQueue());
		newTask->execute();
	}
}

int PendingTasksMap::getOrderedTasksSize() {
	return orderedTasks.size();
}

bool PendingTasksMap::runMoreOrderedTasks(server::zone::objects::scene::SceneObject* sceneObject) {
	Locker guard(&mutex);

	orderedTasks.remove(0);

	if (orderedTasks.size() > 0) {
		auto nextTask = orderedTasks.get(0);

		Reference<OrderedTaskExecutioner*> task = new OrderedTaskExecutioner(sceneObject);
		task->setCustomTaskQueue(nextTask->getCustomTaskQueue());
		task->execute();

		return true;
	}

	return false;
}

Reference<Task*> PendingTasksMap::getNextOrderedTask() {
	Locker guard(&mutex);

	Reference<Task*> task;

	if (orderedTasks.size() != 0) {
		task = orderedTasks.get(0);
	}

	return task;
}


