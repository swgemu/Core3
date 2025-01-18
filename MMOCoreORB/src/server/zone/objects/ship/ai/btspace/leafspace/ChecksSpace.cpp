#include "ChecksSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "templates/params/ship/ShipFlag.h"

// full template specializations need to go in cpp so they don't get
// defined multiple times.

using namespace server::zone::objects::ship::ai::btspace::leafspace;

template<> bool CheckDestination::check(ShipAiAgent* agent) const {
	return agent->setDestination() > 0;
}

template<> bool CheckHasPatrol::check(ShipAiAgent* agent) const {
	return agent->getPatrolPointSize() > 0;
}

template<> bool CheckMovementState::check(ShipAiAgent* agent) const {
	return agent->getMovementState() == checkVar;
}

template<> bool CheckProspectInRange::check(ShipAiAgent* agent) const {
	ManagedReference<ShipObject*> targetShip = nullptr;

	if (agent->peekBlackboard("targetShipProspect"))
		targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

	if (targetShip == nullptr)
		return false;

	Locker clock(targetShip, agent);

	float aggroMod = 0.5f;

	if (agent->peekBlackboard("aggroMod"))
		aggroMod = agent->readBlackboard("aggroMod").get<float>();

	float radiusMin = agent->getMaxDistance();
	float radiusMax = ShipAiAgent::DEFAULTAGGRORADIUS + radiusMin;
	float radius = Math::linearInterpolate(radiusMin, radiusMax, aggroMod);

#ifdef DEBUG_SHIP_AI
	if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
		agent->info(true) << agent->getDisplayedName() << " - CheckProspectInRange -- AggroRadius = " << radius;
#endif // DEBUG_SHIP_AI

	return agent->isInRange3d(targetShip, radius);
}

template<> bool CheckAggroDelayPast::check(ShipAiAgent* agent) const {
	return agent->isAggroDelayPast();
}

template<> bool CheckHasFollow::check(ShipAiAgent* agent) const {
	return agent->getFollowShipObject().get() != nullptr;
}

template<> bool CheckRetreat::check(ShipAiAgent* agent) const {
	if (agent->isRetreating()) {
		return false;
	}

	uint32 shipBitmask = agent->getShipBitmask();

	if ((shipBitmask & ShipFlag::FIXED_PATROL) || (shipBitmask & ShipFlag::ESCORT)) {
		return false;
	}

	SpacePatrolPoint* homeLocation = agent->getHomeLocation();

	if (homeLocation == nullptr)
		return false;

	return !homeLocation->isInRange(agent, checkVar);
}

template<> bool CheckProspectAggression::check(ShipAiAgent* agent) const {
	ManagedReference<ShipObject*> targetShip = nullptr;

	if (agent->peekBlackboard("targetShipProspect"))
		targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*> >();

	if (targetShip == nullptr)
		return false;

	Locker clock(targetShip, agent);

	// agent->info(true) << "CheckProspectAggression";

	return agent->isAggressiveTo(targetShip);
}

template<> bool CheckRefireRate::check(ShipAiAgent* agent) const {
	uint64 lastFire = (uint64)checkVar;

	if (agent->peekBlackboard("refireInterval")) {
		lastFire += agent->readBlackboard("refireInterval").get<uint64>();
	}

	uint64 timeNow = System::getMiliTime();

	// agent->info(true) << agent->getDisplayedName() <<  " RefireInterval -  Last Fire: " << lastFire << " Time now: " << timeNow;

	return timeNow > lastFire;
}

template<> bool CheckStopEvading::check(ShipAiAgent* agent) const {
	int pointSize = agent->getPatrolPointSize();

	// No evade points set or agents engines are disabled
	if (pointSize <= 0 || (agent->getCurrentSpeed() == 0.f))
		return true;

	ManagedReference<ShipObject*> targetShip = agent->getTargetShipObject();

	if (targetShip != nullptr && targetShip->isShipAiAgent()) {
		Locker clocker(targetShip, agent);

		ShipAiAgent* targetAgent = targetShip->asShipAiAgent();

		// Target Agent is already evading, lets not do it at the same time;
		if (targetAgent != nullptr && targetAgent->getMovementState() == ShipAiAgent::EVADING)
			return true;
	}

	SpacePatrolPoint evadePoint = agent->getFinalPosition();

	bool result = (evadePoint.isEvadePoint() && agent->isInRangePosition(evadePoint.getWorldPosition(), agent->getMaxDistance()));

	return result;
}

template<> bool CheckTargetIsValid::check(ShipAiAgent* agent) const {
	ManagedReference<ShipObject*> targetShip = nullptr;

	if (agent->peekBlackboard("targetShipProspect"))
		targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*> >();

	if (targetShip == nullptr)
		return false;

	Locker clock(targetShip, agent);

	// agent->info(true) << agent->getDisplayedName() << " CheckTargetIsValid - Target: " << targetShip->getDisplayedName();

	return agent->validateTarget(targetShip);
}

template<> bool CheckEnginesDisabled::check(ShipAiAgent* agent) const {
	auto componentOptMap = agent->getComponentOptionsMap();

	if (componentOptMap == nullptr)
		return false;

	uint32 flags = componentOptMap->get(Components::ENGINE);

	return (flags & ShipComponentFlag::DISABLED) || (flags & ShipComponentFlag::DEMOLISHED);
}

template<> bool CheckEvadeChance::check(ShipAiAgent* agent) const {
	// Agent engines are disabled, no evading
	if (agent->getCurrentSpeed() == 0.f) {
		return false;
	}

	// Don't immediately evade again
	if (!agent->isEvadeDelayPast()) {
		return false;
	}

	ManagedReference<ShipObject*> targetShip = agent->getTargetShipObject();

	if (targetShip == nullptr) {
		return false;
	}

	Locker clocker(targetShip, agent);

	const Vector3& targetPosition = targetShip->getWorldPosition();
	const Vector3& agentPosition = agent->getWorldPosition();
	const Vector3& homePosition = agent->getHomePosition();

	float attackDistanceMin = agent->getMaxDistance();
	float attackDistanceMax = ShipAiAgent::MAX_ATTACK_DISTANCE + attackDistanceMin;

	float homeDistanceSqr = homePosition.squaredDistanceTo(targetPosition);
	// evade if target distance to home position exceeds max attack distance
	if (homeDistanceSqr > Math::sqr(attackDistanceMax)) {
		return true;
	}

	float targetDistanceSqr = agentPosition.squaredDistanceTo(targetPosition);
	// evade if target distance to agent is less than 1/sec to collision
	if (targetDistanceSqr < Math::sqr(attackDistanceMin)) {
		return true;
	}

	if (targetShip->isShipAiAgent()) {
		ShipAiAgent* targetAgent = targetShip->asShipAiAgent();

		if (targetAgent != nullptr) {
			// do not evade if target is static or already evading
			if (targetAgent->getCurrentSpeed() <= 1.f || targetAgent->getMovementState() == ShipAiAgent::EVADING) {
				return false;
			}

			// if target is attacking agent, roll for who breaks off the attack first.
			if (targetAgent->getMovementState() == ShipAiAgent::ATTACKING && targetAgent->getTargetShipObject() == agent) {
				return System::random(1000) < ShipAiAgent::BEHAVIORINTERVAL;
			}
		}
	}

	return false;
}

template<> bool CheckProspectLOS::check(ShipAiAgent* agent) const {
	ManagedReference<ShipObject*> targetShip = nullptr;

	if (agent->peekBlackboard("targetShipProspect"))
		targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*> >();

	if (targetShip == nullptr)
		return false;

	Locker locker(targetShip, agent);

	return agent->checkLineOfSight(targetShip);
}

template<> bool CheckWeapons::check(ShipAiAgent* agent) const {
	auto componentMap = agent->getShipComponentMap();
	auto componentOptionsMap = agent->getComponentOptionsMap();

	if (componentMap == nullptr || componentOptionsMap == nullptr) {
		return false;
	}

	int validWeapons = 0;

	for (uint32 slot = Components::WEAPON_START; slot <= Components::CAPITALSLOTMAX; ++slot) {
		uint32 crc = componentMap->get(slot);

		if (crc == 0) {
			continue;
		}

		int hitpoints = agent->getCurrentHitpointsMap()->get(slot);

		if (hitpoints <= 0.f) {
			continue;
		}

		int flags = componentOptionsMap->get(slot);

		if (flags & ShipComponentFlag::DISABLED) {
			continue;
		}

		validWeapons++;
	}

	return validWeapons > 0;
}
