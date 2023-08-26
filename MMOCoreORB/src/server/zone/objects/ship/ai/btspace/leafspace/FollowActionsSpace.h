#ifndef FOLLOWACTIONSSPACE_H_
#define FOLLOWACTIONSSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BlackboardDataSpace.h"
#include "server/zone/SpaceZone.h"
#include "templates/faction/Factions.h"
#include "server/zone/managers/spacecombat/SpaceCombatManager.h"
#include "server/zone/managers/spacecollision/SpaceCollisionManager.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace leafspace {

class CalculateAggroMod : public BehaviorSpace {
public:
	CalculateAggroMod(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - CalculateAggroMod  called";
#endif // DEBUG_SHIP_AI

		ManagedReference<ShipObject*> targetShip = nullptr;

		if (agent->peekBlackboard("targetShipProspect")) {
#ifdef DEBUG_SHIP_AI
			if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
				agent->info(true) << agent->getDisplayedName() << " - CalculateAggroMod  readBlackboard";
#endif // DEBUG_SHIP_AI
			targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();
		}

#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - CalculateAggroMod  target check";
#endif // DEBUG_SHIP_AI

		if (targetShip == nullptr)
			return FAILURE;

		Locker clocker(targetShip, agent);

		float minMod = 1.5f; // Math::min(1.f - (tarCreo->getLevel() - agent->getLevel()) / 8.f, 1.5f);
		float mod = Math::max(0.75f, minMod);

		agent->writeBlackboard("aggroMod", mod);

#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - CalculateAggroMod  complete";
#endif // DEBUG_SHIP_AI

		return agent->peekBlackboard("aggroMod") ? SUCCESS : FAILURE;
	}
};

class SetMovementState : public BehaviorSpace {
public:
	SetMovementState(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), state(0) {
		parseArgs(args);
	}

	SetMovementState(const SetMovementState& a) : BehaviorSpace(a), state(a.state) {
	}

	SetMovementState& operator=(const SetMovementState& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);
		state = a.state;
		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<ShipObject*> targetShip = nullptr;

		if (agent->peekBlackboard("targetShipProspect"))
			targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		//agent->info(true) << agent->getDisplayedName() << " set movement state: " << state;

		switch (state) {
		case ShipAiAgent::OBLIVIOUS:
			break;
		case ShipAiAgent::WATCHING: {
			break;
		}
		case ShipAiAgent::FOLLOWING: {
			targetShip = agent->getFollowShipObject().get();

			if (targetShip != nullptr) {
				break;
			}
		}
		case ShipAiAgent::PATROLLING:
			break;
		case ShipAiAgent::ATTACKING: {
			if (targetShip != nullptr) {
				Locker clocker(targetShip, agent);

				agent->setTargetShipObject(targetShip);
			}
			break;
		}
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
			break;
		case ShipAiAgent::EVADING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOW_FORMATION:
		default:
			break;
		};

		agent->setMovementState(state);

		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		state = getArg<int32>()(args, "state");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << state;

		return msg.toString();
	}

private:
	uint32 state;
};

class SetDefenderFromProspect : public BehaviorSpace {
public:
	SetDefenderFromProspect(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	SetDefenderFromProspect(const SetDefenderFromProspect& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetShipProspect"))
			return FAILURE;

		ManagedReference<ShipObject*> targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			agent->eraseBlackboard("targetShipProspect");
			return FAILURE;
		}

		Locker clocker(targetShip, agent);

		agent->setDefender(targetShip);

#ifdef DEBUG_SHIP_AI
		if (agent->peekBlackboard("aiDebug") && agent->readBlackboard("aiDebug") == true)
			agent->info(true) << agent->getDisplayedName() << " - SetDefenderFromProspect";
#endif // DEBUG_SHIP_AI

		return agent->getMainDefender() == targetShip ? SUCCESS : FAILURE;
	}
};

class Evade : public BehaviorSpace {
public:
	Evade(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), evadeDelay(5000) {
		parseArgs(args);
	}

	Evade(const Evade& a) : BehaviorSpace(a), evadeDelay(a.evadeDelay) {
	}

	Evade& operator=(const Evade& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);

		evadeDelay = a.evadeDelay;

		return *this;
	}

	void parseArgs(const LuaObject& args) {
		evadeDelay = getArg<uint64>()(args, "evadeDelay");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		Time* evadeTime = agent->getEvadeDelay();

		if (evadeTime != nullptr && evadeTime->isPast()) {
			evadeTime->updateToCurrentTime();
			evadeTime->addMiliTime(evadeDelay);

			// agent->info(true) << agent->getDisplayedName() << " Evade delay set for " << evadeDelay;
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << " - Evade Delay: " << evadeDelay ;

		return msg.toString();
	}

	private:
	uint64 evadeDelay;
};

class EngageTarget : public BehaviorSpace {
public:
	EngageTarget(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	EngageTarget(const EngageTarget& a) : BehaviorSpace(a) {
	}

	EngageTarget& operator=(const EngageTarget& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);

		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetShipProspect"))
			return FAILURE;

		ManagedReference<ShipObject*> targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			return FAILURE;
		}

		auto componentMap = agent->getShipComponentMap();
		auto hitpointsMap = agent->getCurrentHitpointsMap();

		if (componentMap == nullptr || hitpointsMap == nullptr) {
			return FAILURE;
		}

		if (componentMap->get(Components::WEAPON_START) == 0 || hitpointsMap->get(Components::WEAPON_START) == 0)
			return FAILURE;

		int projectileType = ShipAiAgent::NEUTRAL_PROJECTILE;
		uint32 faction = agent->getFaction();

		if (faction == Factions::FACTIONIMPERIAL) {
			projectileType = ShipAiAgent::IMPERIAL_PROJECTILE;
		} else if (faction == Factions::FACTIONREBEL) {
			projectileType = ShipAiAgent::REBEL_PROJECTILE;
		}

		Locker clock(targetShip, agent);

		Vector3 currentPosition = agent->getPosition();
		Vector3 targetPosition = targetShip->getPosition();

		Vector3 currentDirectionVec = agent->getCurrentDirectionVector();

		Vector3 rayStart = currentPosition;
		Vector3 rayEnd = (currentDirectionVec * 1500.f) + currentPosition;
		Vector3 direction = rayEnd - rayStart;

		Vector3 difference = targetPosition - rayStart;
		float collisionDistance = SpaceCollisionManager::getPointIntersection(direction, difference, targetShip->getBoundingRadius() * 5.f, 1500.f);

		if (collisionDistance == FLT_MAX) {
			return FAILURE;
		}

		agent->eraseBlackboard("refireInterval");

		uint64 timeNow = System::getMiliTime();
		agent->writeBlackboard("refireInterval", timeNow);

		auto projectile = new ShipProjectile(agent, 0, projectileType, 0, currentPosition, currentDirectionVec * 7800.f, 500, 500, 1.f, timeNow);
		SpaceCombatManager::instance()->addProjectile(agent, projectile);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class GetProspectFromThreatMap : public BehaviorSpace {
public:
	GetProspectFromThreatMap(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	GetProspectFromThreatMap(const GetProspectFromThreatMap& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<ShipObject*> targetShip = nullptr;

		if (agent->peekBlackboard("targetShipProspect")) {
			targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();
		}

		auto agentMap = agent->getThreatMap();

		if (agentMap == nullptr) {
			return FAILURE;
		}

		ManagedReference<TangibleObject*> topThreat = agentMap->getHighestThreatAttacker();

		// Make sure top threat is not null and is a ship
		if (topThreat == nullptr || !topThreat->isShipObject()) {
			return FAILURE;
		}

		uint64 topThreatID = topThreat->getObjectID();

		// Do not agent as their own target
		if (topThreatID == agent->getObjectID()) {
			return FAILURE;
		}

		// Return success if the top threat is already their current target
		if (targetShip != nullptr && topThreatID == targetShip->getObjectID()) {
			auto aggroDelay = agent->getAggroDelay();

			if (aggroDelay != nullptr)
				aggroDelay->updateToCurrentTime();

			return SUCCESS;

		}

		targetShip = topThreat->asShipObject();

		if (targetShip == nullptr) {
			return FAILURE;
		}

		agent->eraseBlackboard("targetShipProspect");
		agent->writeBlackboard("targetShipProspect", targetShip);

		return SUCCESS;
	}
};

class GetProspectFromDefenders : public BehaviorSpace {
public:
	GetProspectFromDefenders(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	GetProspectFromDefenders(const GetProspectFromDefenders& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> defender = agent->getMainDefender();

		if (defender == nullptr || !defender->isShipObject())
			return FAILURE;

		ManagedReference<ShipObject*> defenderShip = defender->asShipObject();

		if (defenderShip == nullptr)
			return FAILURE;

		ManagedReference<ShipObject*> targetShip = nullptr;

		if (agent->peekBlackboard("targetShipProspect")) {
			targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

			if (targetShip != nullptr && targetShip->getObjectID() == defenderShip->getObjectID())
				return SUCCESS;
		}

		Locker clocker(defenderShip, agent);

		agent->eraseBlackboard("targetShipProspect");
		agent->writeBlackboard("targetShipProspect", defenderShip);

		return SUCCESS;
	}
};

} // namespace leafspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // FOLLOWACTIONSSPACE_H_
