
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
	Reference<Task*> task{nullptr};

	String taskName;

public:
	OrderedTaskExecutioner(TaskOwner* object, Reference<Task*>&& taskToRun) : owner(object), task(std::move(taskToRun)) {
		setCustomTaskQueue(task->getCustomTaskQueue());
	}

	void run() final {
		auto strongReference = owner.get();

		if (strongReference == nullptr)
			return;

		auto pendingTasks = strongReference->getPendingTasks();

		try {
			task->run();
		} catch (const Exception& exc) {
			auto trace = exc.getStackTrace();
			strongReference->error() << "exception in OrderedTaskExecutioner::run: " << exc.getMessage() << "; STACK: " << trace.toStringData();
		} catch (...) {
			StackTrace trace;
			strongReference->error() << "exception in OrderedTaskExecutioner::run: unhandled excetion; STACK: " << trace.toStringData();
		}

		taskName = task->getTaskName();

		const auto remainingTasks = pendingTasks->decrementPendingTasks();

		if (remainingTasks > 0) {
			Reference<Task*> poppedTask;

			while (!(poppedTask = pendingTasks->popNextOrderedTask())) {

			}

			auto nextTask = new OrderedTaskExecutioner<TaskOwner>(strongReference, std::move(poppedTask));
			nextTask->execute();
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
