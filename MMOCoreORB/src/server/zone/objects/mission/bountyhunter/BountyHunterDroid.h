/*
 * BountyHunterDroid.h
 *
 *  Created on: Jan 20, 2012
 *      Author: loshult
 */

#ifndef BOUNTYHUNTERDROID_H_
#define BOUNTYHUNTERDROID_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/log/Logger.h"
#include "server/zone/objects/mission/bountyhunter/events/FindTargetTask.h"
#include "server/zone/objects/mission/bountyhunter/events/CallArakydTask.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {

/**
 * Class implementing the functionality of the bounty hunter droids.
 */
class BountyHunterDroid : public Logger, public Object {
public:

	enum {
		CALLDROID,
		TRANSMITBIOLOGICALSIGNATURE,
		FINDTARGET,
		FINDANDTRACKTARGET
	};

	BountyHunterDroid() :
		Logger("BountyHunterDroid") {
	}

	Reference<Task*> performAction(int action, SceneObject* droidObject, CreatureObject* player, MissionObject* mission);

private:
	Reference<FindTargetTask*> findTarget(SceneObject* sceneObject, CreatureObject* player, MissionObject* mission, bool track);

	Reference<CallArakydTask*> callArakydDroid(SceneObject* droidObject, CreatureObject* player, MissionObject* mission);

	Reference<FindTargetTask*> transmitBiologicalSignature(SceneObject* sceneObject, CreatureObject* player, MissionObject* mission);
};

} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter;

#endif /* BOUNTYHUNTERDROID_H_ */
