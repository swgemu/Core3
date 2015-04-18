/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FAILMISSIONAFTERCERTAINTIMETASK_H_
#define FAILMISSIONAFTERCERTAINTIMETASK_H_

#include "server/zone/objects/mission/MissionObjective.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace events {

class FailMissionAfterCertainTimeTask : public Task {
	ManagedWeakReference<MissionObjective*> objective;

public:
	FailMissionAfterCertainTimeTask(MissionObjective* objective) {
		this->objective = objective;
	}

	void run() {
		ManagedReference<MissionObjective*> objectiveRef = objective.get();

		if (objectiveRef != NULL) {
			//Fail mission.
			ManagedReference<CreatureObject*> owner = objectiveRef->getPlayerOwner();
			if (owner != NULL) {
				Locker locker(owner);

				owner->sendSystemMessage("Mission expired");

				objectiveRef->fail();
			} else
				objectiveRef->fail();

		}
	}
};

} // namespace events
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::events;

#endif /* FAILMISSIONAFTERCERTAINTIMETASK_H_ */
