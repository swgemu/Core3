/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FAILMISSIONAFTERCERTAINTIMETASK_H_
#define FAILMISSIONAFTERCERTAINTIMETASK_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
	class MissionObject;

namespace events {

class FailMissionAfterCertainTimeTask final : public Task {
	WeakReference<MissionObject*> object;

public:
	FailMissionAfterCertainTimeTask(MissionObject* object);
	void run() override;
};

} // namespace events
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::events;

#endif /* FAILMISSIONAFTERCERTAINTIMETASK_H_ */
