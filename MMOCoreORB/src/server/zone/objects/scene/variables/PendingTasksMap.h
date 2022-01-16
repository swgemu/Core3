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

namespace variables {

template <class TaskOwner>
class OrderedTaskExecutioner;
}
}
} // namespace objects
} // namespace zone
} // namespace server

class PendingTasksMap : public Object {
protected:
	mutable Mutex mutex;

	VectorMap<String, Reference<Task*>> taskMap;

	typedef boost::lockfree::queue<Task*, boost::lockfree::fixed_sized<false>> TaskQueue;
	TaskQueue pendingTasks{};
	AtomicLong pendingTasksSize{};

public:
	PendingTasksMap();
	~PendingTasksMap();

	int put(const String& name, Task* task);

	void drop(const String& name);

	bool contains(const String& name);

	Reference<Task*> get(const String& name) const;

	uint64 decrementPendingTasks() {
		return pendingTasksSize.decrement();
	}

	template <class Owner>
	void putOrdered(Task* task, Owner* owner) {
		task->acquire();
		const auto values = pendingTasksSize.increment();

		if (values == 1) {
			Reference<Task*> strongReference;
		        strongReference.initializeWithoutAcquire(task);

			auto newTask = new server::zone::objects::scene::variables::OrderedTaskExecutioner<Owner>(owner, std::move(strongReference));
			newTask->execute();
		} else {
			const bool result = pendingTasks.push(task);
			E3_ASSERT(result);
		}

	}

	Reference<Task*> popNextOrderedTask();
};

#endif /* PENDINGTASKSMAP_H_ */
