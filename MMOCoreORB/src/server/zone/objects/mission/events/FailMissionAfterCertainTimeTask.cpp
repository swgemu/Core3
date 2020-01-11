#include "FailMissionAfterCertainTimeTask.h"

#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/MissionObjective.h"
#include "server/zone/objects/creature/CreatureObject.h"

FailMissionAfterCertainTimeTask::FailMissionAfterCertainTimeTask(MissionObject* object) {
	this->object = object;
}

void FailMissionAfterCertainTimeTask::run() {
	Reference<MissionObject*> objectRef = object.get();

	if (objectRef != nullptr) {
		ManagedReference<MissionObjective*> objectiveRef = objectRef->getMissionObjective();

		if (objectiveRef != nullptr) {
			//Fail mission.
			ManagedReference<CreatureObject*> owner = objectiveRef->getPlayerOwner();
			if (owner != nullptr) {
				Locker locker(owner);

				owner->sendSystemMessage("Mission expired");

				objectiveRef->fail();
			}
			else {
				objectiveRef->fail();
			}
		}
	}
}