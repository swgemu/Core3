#include "server/zone/Zone.h"
#include "server/ServerCore.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/managers/ship/tasks/ShipObjectTimerTask.h"

ShipObjectTimerTask::ShipObjectTimerTask(ShipManager* shipManager) : Task() {
	setLoggingName("ShipObjectTimerTask ");
	shipManagerRef = shipManager;

	uint64 timeNow = System::getMiliTime();

	for (int i = 0; i < Timers::SIZE; ++i) {
		timers.add(timeNow);
		deltas.add(0);
	}

	startTime = timeNow;
	iterator = 0;
	priority = Timers::MIN;
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

		if (agent == nullptr || !agent->isShipLaunched()) {
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

		if (ship == nullptr || !ship->isShipLaunched()) {
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
		auto shipManager = shipManagerRef.get();

		if (shipManager == nullptr) {
			return;
		}

		auto shipMap = shipManager->getShipUniqueIdMap();

		if (shipMap == nullptr) {
			return;
		}

		shipMap->safeCopyTo(queueVector);
		agentVector.removeAll();
		shipVector.removeAll();

		for (int i = queueVector.size(); -1 < --i;) {
			auto ship = queueVector.get(i).get();

			if (ship == nullptr || !ship->isShipLaunched()) {
				continue;
			}

			Locker lock(ship);

			if (ship->isShipAiAgent()) {
				auto agent = ship->asShipAiAgent();

				if (agent == nullptr) {
					continue;
				}

				agentVector.add(agent);
			} else {
				shipVector.add(std::move(ship));
			}
		}

		queueVector.removeAll();
	}
}
