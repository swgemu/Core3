/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FAILMISSIONAFTERCERTAINTIMETASK_H_
#define FAILMISSIONAFTERCERTAINTIMETASK_H_

#include "server/zone/objects/mission/MissionObject.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace events {

class FailMissionAfterCertainTimeTask : public Task {
	ManagedWeakReference<MissionObject*> object;

public:
	FailMissionAfterCertainTimeTask(MissionObject* object) {
		this->object = object;
	}

	void run() {
		ManagedReference<MissionObject*> objectRef = object.get();

		if (objectRef != NULL) {
			ManagedReference<MissionObjective*> objectiveRef = objectRef->getMissionObjective();

			if (objectiveRef != NULL) {
				//Fail mission.
				ManagedReference<CreatureObject*> owner = objectiveRef->getPlayerOwner();
				if (owner != NULL) {
					Locker locker(owner);

					owner->sendSystemMessage("Mission expired");

					objectiveRef->fail();
				} else {
					objectiveRef->fail();
				}
			}
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
