/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/managers/resource/InterplanetarySurvey.h"
#include "server/zone/managers/resource/InterplanetarySurveyTask.h"
#include "engine/engine.h"

void InterplanetarySurveyImplementation::notifyLoadFromDatabase() {
	if (executed)
		return;

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime();
	int64 remTime = (timeStamp + curTime) - currentTime;


	Reference<InterplanetarySurveyTask*> task = new InterplanetarySurveyTask(_this.getReferenceUnsafeStaticCast());

	if (remTime > 0) { // If there is still time left before it should be triggered, schedule for that amount of time
		task->schedule(remTime);
	} else { // If not, schedule in 1s
		task->schedule(1000);
	}
}
