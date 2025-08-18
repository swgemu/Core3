#ifndef SHIPOBJECTTIMERTASK_H_
#define SHIPOBJECTTIMERTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

namespace server {
	namespace zone {
		namespace managers {
			namespace ship {
				class ShipManager;
			}
		}
	}
}

class ShipObjectTimerTask : public Task, public Logger {
	public:
		enum Timers : int {
			MIN = 0,
			MID = 1,
			MAX = 2,
			SIZE = 3
		};

		enum Intervals : int {
			TIME_MIN = 200,
			TIME_MID = 1000,
			TIME_MAX = 2000,
			TIME_SLEEP = 5000
		};

		static const int ITERATOR_MID = TIME_MID / TIME_MIN;
		static const int ITERATOR_MAX = TIME_MAX / TIME_MIN;
		static const int SCHEDULE_MIN = TIME_MIN * 0.5f;
		static const int SCHEDULE_MAX = TIME_MIN * 1.5f;

	protected:
		Reference<ShipManager*> shipManagerRef;

		Vector<ManagedReference<ShipObject*>> shipVector;
		Vector<ManagedReference<ShipAiAgent*>> agentVector;
		Vector<ManagedWeakReference<ShipObject*>> queueVector;

		Vector<uint64> timers;
		Vector<uint32> deltas;

		uint64 startTime;
		uint32 iterator;
		uint32 priority;

	public:
		ShipObjectTimerTask(ShipManager* shipManager);

		void run();

	private:
		void updateTimers() {
			uint64 timeNow = System::getMiliTime();
			iterator = (iterator + 1) % ITERATOR_MAX;

			deltas.set(MIN, timeNow - timers.get(MIN));
			timers.set(MIN, timeNow);
			priority = MIN;

			if ((iterator % ITERATOR_MID) == 0) {
				deltas.set(MID, timeNow - timers.get(MID));
				timers.set(MID, timeNow);
				priority = MID;
			}

			if ((iterator % ITERATOR_MAX) == 0) {
				deltas.set(MAX, timeNow - timers.get(MAX));
				timers.set(MAX, timeNow);
				priority = MAX;
			}
		}

		uint32 getDeltaTime(int index) const {
			return deltas.get(index);
		}

		bool getAsyncPriority(int iteratorMax, int index) const {
			return (index % iteratorMax) == iterator;
		}

		uint32 getScheduleInterval() {
			uint64 latency = (System::getMiliTime() - startTime) % TIME_MIN;
			uint32 interval = TIME_MIN - latency;

			return Math::clamp((uint32)(SCHEDULE_MIN), interval, (uint32)(SCHEDULE_MAX));
		}

		void updateAgents();

		void updateShips();

		int updateVectors();

		String toDebugString(const String& message) const {
			StringBuffer msg;

			msg << message << endl
				<< "iterator:    " << iterator << endl
				<< "deltaMin:    " << deltas.get(MIN) << endl
				<< "deltaMid:    " << deltas.get(MID) << endl
				<< "deltaMax:    " << deltas.get(MAX) << endl
				<< "shipVector:  " << shipVector.size() << endl
				<< "agentVector: " << agentVector.size() << endl
				<< "queueVector: " << queueVector.size() << endl
				<< "totalTime:   " << (System::getMiliTime() - startTime);

			return msg.toString();
		}
	};

#endif // SHIPOBJECTTIMERTASK_H_
