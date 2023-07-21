/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "server/zone/managers/gcw/observers/ProbotObserver.h"

#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/creature/CreatureObject.h"

int ProbotObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<CreatureObject*> attacker = cast<CreatureObject*>(arg1);

	if (attacker == nullptr || probot == nullptr) {
		return 0;
	}

	if (attacker->isPet()) {
		CreatureObject* owner = attacker->getLinkedCreature().get();

		if (owner == nullptr) {
			return 0;
		}

		attacker = owner;
	}

	if (!attacker->isPlayerCreature()) {
		return 0;
	}

	auto zone = probot->getZone();

	if (zone == nullptr)
		return 0;

	auto planetMan = zone->getPlanetManager();
	auto landingCoordinates = probot->getWorldPosition();

	if (planetMan != nullptr) {
		landingCoordinates = planetMan->getInSightSpawnPoint(attacker, 30, 120, 15);
	}

	Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(attacker, Factions::FACTIONIMPERIAL, 1, "@imperial_presence/contraband_search:containment_team_imperial", landingCoordinates,
		Quaternion(Vector3(0, 1, 0), attacker->getDirection()->getRadians() + 3.14f), LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLEATTACK);

	if (lambdaTask != nullptr)
		lambdaTask->schedule(500);

	probot->showFlyText("imperial_presence/contraband_search", "probot_distress_fly", 255, 0, 0);

	return 1;
}