/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMPLETEMISSIONAFTERCERTAINTIMETASK_H_
#define COMPLETEMISSIONAFTERCERTAINTIMETASK_H_

#include "server/zone/objects/mission/MissionObjective.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace events {

class CompleteMissionAfterCertainTimeTask : public Task {
	ManagedReference<MissionObjective*> objective;

public:
	CompleteMissionAfterCertainTimeTask(MissionObjective* objective) {
		this->objective = objective;
	}

	void run() {
		//Complete mission.
		objective->complete();
	}
};

} // namespace events
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::events;

#endif /* COMPLETEMISSIONAFTERCERTAINTIMETASK_H_ */
