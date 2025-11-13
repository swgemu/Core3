#include "server/zone/managers/ship/tasks/ShipObjectTimerTask.h"

ShipObjectTimerTask::ShipObjectTimerTask(const String& taskQueueName) : Task() {
	setLoggingName("ShipObjectTimerTask_" + taskQueueName);
	setCustomTaskQueue(taskQueueName);

	uint64 timeNow = System::getMiliTime();

	for (int i = 0; i < Timers::SIZE; ++i) {
		timers.add(timeNow);
		deltas.add(0);
	}

	startTime = timeNow;
	iterator = 0;
	priority = Timers::MIN;
	taskCrc = taskQueueName.hashCode();
}

void ShipObjectTimerTask::addShip(ShipObject* ship) {
	if (ship == nullptr || shipSet.contains(ship)) {
		return;
	}

	Locker lock(&mutex);
	queueVector.add(ship);
}

void ShipObjectTimerTask::run() {
	updateTimers();
	updateShips();
	updateAgents();
	updateVectors();

	uint32 interval = getScheduleInterval();
	reschedule(interval);
}

void ShipObjectTimerTask::updateAgents() {
	uint32 deltaMax = getDeltaTime(Timers::MAX);

	for (int i = agentVector.size(); -1 < --i;) {
		auto agent = agentVector.get(i);

		if (!isShipValid(agent)) {
			agentVector.remove(i);
			shipSet.remove(agent);
			continue;
		}

		Locker lock(agent);
		bool lightUpdate = !getAsyncPriority(ITERATOR_MAX, i);

		agent->updateTransform(lightUpdate);
	}
}

void ShipObjectTimerTask::updateShips() {
	uint32 deltaMid = getDeltaTime(Timers::MID);

	for (int i = shipVector.size(); -1 < --i;) {
		auto ship = shipVector.get(i);

		if (!isShipValid(ship)) {
			shipVector.remove(i);
			shipSet.remove(ship);
			continue;
		}

		Locker lock(ship);
		bool lightUpdate = !getAsyncPriority(ITERATOR_MID, i);

		if (!lightUpdate) {
			ship->doRecovery(deltaMid);
		}
	}
}

void ShipObjectTimerTask::updateVectors() {
	if (priority == Timers::MAX) {
		ReadLocker rLock(&mutex);

		auto queueCopy = queueVector;
		queueVector.removeAll();
		rLock.release();

		for (int i = queueCopy.size(); -1 < --i;) {
			auto ship = queueCopy.get(i).get();

			if (!isShipValid(ship) || shipSet.contains(ship)) {
				continue;
			}

			Locker lock(ship);

			if (ship->isShipAiAgent()) {
				auto agent = ship->asShipAiAgent();

				if (agent == nullptr) {
					continue;
				}

				agentVector.add(agent);
				shipSet.add(agent);
			} else {
				shipVector.add(ship);
				shipSet.add(ship);
			}
		}
	}
}

bool ShipObjectTimerTask::isShipValid(ShipObject* ship) const {
	return ship != nullptr && ship->isShipLaunched() && ship->getTimerTaskCrc() == taskCrc;
}
