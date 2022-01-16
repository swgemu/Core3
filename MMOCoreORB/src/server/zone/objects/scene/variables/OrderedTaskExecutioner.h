
/*
 * OrderedTask.h
 *
 *  Created on: Apr 14, 2015
 *      Author: TheAnswer
 */

#ifndef SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_
#define SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_

#include "engine/engine.h"

class PendingTasksMap;

namespace server {
namespace zone {
namespace objects {
namespace scene {

class SceneObject;

namespace variables {

template <class TaskOwner>
class OrderedTaskExecutioner : public Task {
protected:
	WeakReference<TaskOwner*> owner;

	String taskName;

public:
	OrderedTaskExecutioner(TaskOwner* object) : owner(object) {
	}

	void run() final {
		auto strongReference = owner.get();

		if (strongReference == nullptr)
			return;

		auto pendingTasks = strongReference->getPendingTasks();
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
				auto nextTask = new OrderedTaskExecutioner<TaskOwner>(strongReference);
				nextTask->setCustomTaskQueue(nextTask->getCustomTaskQueue());
				nextTask->execute();
			}
		}
	}

	const char* getTaskName() final {
		if (!taskName.isEmpty()) {
			return taskName.toCharArray();
		} else {
			return Task::getTaskName();
		}
	}
};

} // namespace variables
} // namespace scene
} // namespace objects
} // namespace zone
} // namespace server

#endif /* SRC_SERVER_ZONE_OBJECTS_SCENE_VARIABLES_ORDEREDTASKEXECUTIONER_H_ */
