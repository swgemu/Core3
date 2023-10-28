/*
	Copyright <SWGEmu>
	See file COPYING for copying conditions.
*/

#ifndef CALLARAKYDTASK_H_
#define CALLARAKYDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/CloseObjectsVector.h"

namespace server {
namespace zone {
namespace objects {
namespace mission {
namespace bountyhunter {
namespace events {

class CallArakydTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> player;
	ManagedWeakReference<BountyMissionObjective*> objective;
	int time;
	Vector3 droidPosition;
	ManagedReference<AiAgent*> droid;

public:
	CallArakydTask(CreatureObject* player, BountyMissionObjective* objective) :
		Logger("FindTargetTask") {
		this->player = player;
		this->objective = objective;
		time = 20;
		droid = nullptr;
	}

	~CallArakydTask() {
	}

	void run() {
		ManagedReference<CreatureObject*> playerRef = player.get();
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (playerRef == nullptr || objectiveRef == nullptr) {
			return;
		}

		Locker locker(playerRef);

		switch (time) {
		case 20:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_launch_prep");
			time -= 15;
			reschedule(15 * 1000);
			break;
		case 3: {
			droidPosition = getLandingCoordinates(playerRef);
			PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/probot_delivery.cef", playerRef->getZone()->getZoneName(), droidPosition.getX(), droidPosition.getZ(), droidPosition.getY(), 0, 0);
			playerRef->sendMessage(effect);
		}
		case 5:
		case 4:
		case 2:
		case 1:
			playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_arrival_" + String::valueOf(time));
			time -= 1;
			reschedule(1 * 1000);
			break;
		case 0: {
				playerRef->sendSystemMessage("@mission/mission_generic:probe_droid_arrival");
				droid = cast<AiAgent*>(playerRef->getZone()->getCreatureManager()->spawnCreature(STRING_HASHCODE("probot"), 0, droidPosition.getX(), droidPosition.getZ(), droidPosition.getY(), 0));

				Locker olocker(objectiveRef);
				objectiveRef->setArakydDroid(droid);
				olocker.release();

				Locker lock(droid);
				droid->addCreatureFlag(CreatureFlag::STATIC);
				droid->setAITemplate();
				time -= 1;
				reschedule(300 * 1000);
		}
			break;
		case -1: {
			Locker olocker2(objectiveRef);
			objectiveRef->setArakydDroid(nullptr);
			olocker2.release();

			if (droid != nullptr) {
				Locker clocker(droid, playerRef);
				droid->destroyObjectFromWorld(true);
			}
		}
			break;
		default:
			error("Unknowns state.");
			break;
		}
	}

	Vector3 getLandingCoordinates(CreatureObject* player) {
		Vector3 position = player->getPosition();
		auto zone = player->getZone();

		if (zone == nullptr) {
			return position;
		}

		auto planetManager = zone->getPlanetManager();

		if (planetManager == nullptr)
			return position;

		return planetManager->getInSightSpawnPoint(player, 30, 120, 15);
	}
};

} // namespace events
} // namespace bountyhunter
} // namespace mission
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::mission::bountyhunter::events;

#endif /* CALLARAKYDTASK_H_ */
