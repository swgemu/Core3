/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CALLARAKYDTASK_H_
#define CALLARAKYDTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/structure/StructureManager.h"

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
		droid = NULL;
	}

	~CallArakydTask() {
		cancel();
	}

	void run() {
		ManagedReference<CreatureObject*> playerRef = player.get();
		ManagedReference<BountyMissionObjective*> objectiveRef = objective.get();

		if (playerRef == NULL || objectiveRef == NULL) {
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
				droid = cast<AiAgent*>(playerRef->getZone()->getCreatureManager()->spawnCreature(String("probot").hashCode(), 0, droidPosition.getX(), droidPosition.getZ(), droidPosition.getY(), 0));
				objectiveRef->setArakydDroid(droid);
				droid->activateLoad("stationary");
				time -= 1;
				reschedule(300 * 1000);
		}
			break;
		case -1:
			objectiveRef->setArakydDroid(NULL);
			if (droid != NULL) {
				Locker clocker(droid, playerRef);
				droid->destroyObjectFromWorld(true);
			}
			break;
		default:
			error("Unknowns state.");
			break;
		}
	}

	Vector3 getLandingCoordinates(CreatureObject* player) {
		Vector3 position = player->getPosition();

		if (player->getZone() == NULL || player->getZone()->getPlanetManager() == NULL) {
			return position;
		}

		PlanetManager* planetManager = player->getZone()->getPlanetManager();

		int distance = 30;
		int angle = 15;

		do {
			for (int i = 0; i < 10; i++) {
				position = player->getWorldCoordinate(distance + System::random(20), angle - System::random(2 * angle));

				if (noInterferingObjects(player, position)) {
					return position;
				}
			}

			distance += 10;
			angle += 5;
		} while (distance <= 120);

		return player->getPosition();
	}

	bool noInterferingObjects(CreatureObject* player, Vector3 position)
	{
		SortedVector<ManagedReference<QuadTreeEntry* > >* closeObjects =  player->getCloseObjects();

		for (int j = 0; j < closeObjects->size(); j++) {
			SceneObject* obj = cast<SceneObject*>(closeObjects->get(j).get());

			SharedObjectTemplate* objectTemplate = obj->getObjectTemplate();

			if (objectTemplate != NULL) {
				float radius = objectTemplate->getNoBuildRadius();

				if (radius > 0) {
					Vector3 objWorldPos = obj->getWorldPosition();

					if (objWorldPos.squaredDistanceTo(position) < radius * radius) {
						return false;
					}
				}

				if (objectTemplate->isSharedStructureObjectTemplate()) {
					if (StructureManager::instance()->isInStructureFootprint(cast<StructureObject*>(obj), position.getX(), position.getY(), 2)) {
						return false;
					}
				}
			}
		}

		return true;
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
