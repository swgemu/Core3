/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/managers/director/PersistentEvent.h"
#include "server/zone/managers/director/ScreenPlayTask.h"

void PersistentEventImplementation::loadTransientTask() {
	if (eventExecuted)
		return;

	// Converting old int variable to uint64
	if (timeStamp != 0 && miliDiff == 0) {
		miliDiff = timeStamp;
		timeStamp = 0;
	}

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime();
	uint64 remTime = (miliDiff + curTime) - currentTime;

	Reference<ScreenPlayTask*> task = new ScreenPlayTask(obj.get(), key, play, args);
	task->setPersistentEvent(_this.getReferenceUnsafeStaticCast());

	if (remTime > 0) { // If there is still time left before it should be triggered, schedule for that amount of time
		task->schedule(remTime);
	} else { // If not, schedule in 1s
		task->schedule(1000);
	}

	screenplayTask = task;
}
