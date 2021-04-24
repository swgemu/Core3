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

	auto landingCoordinates = probot->getWorldPosition();
	if (probot->getZone() != nullptr || probot->getZone()->getPlanetManager() != nullptr) {
		landingCoordinates = probot->getZone()->getPlanetManager()->getInSightSpawnPoint(attacker, 30, 120, 15);
	}

	float dx = attacker->getWorldPositionX() - landingCoordinates.getX();
	float dy = attacker->getWorldPositionY() - landingCoordinates.getY();
	float directionangle = atan2(dy, dx);
	float radangle = M_PI / 2 - directionangle;

	Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(
		attacker, Factions::FACTIONIMPERIAL, 1, "@imperial_presence/contraband_search:containment_team_imperial", landingCoordinates,
		radangle, LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLEATTACK);
	lambdaTask->schedule(1);

	probot->showFlyText("imperial_presence/contraband_search", "probot_distress_fly", 255, 0, 0);

	return 1;
}