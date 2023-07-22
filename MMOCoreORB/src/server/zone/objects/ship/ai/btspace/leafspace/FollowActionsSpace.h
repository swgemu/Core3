#ifndef FOLLOWACTIONSSPACE_H_
#define FOLLOWACTIONSSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BlackboardDataSpace.h"
#include "server/zone/SpaceZone.h"
#include "templates/faction/Factions.h"
#include "server/zone/managers/spacecombat/SpaceCombatManager.h"

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

		if (targetShip == nullptr /*&& !(agent->getShipBitmask() & ShipFlag::FOLLOW) && (state == ShipAiAgent::WATCHING || state == ShipAiAgent::FOLLOWING)*/) {
			return FAILURE;
		}

		//agent->info(true) << agent->getDisplayedName() << " set movement state: " << state;

		switch (state) {
		case ShipAiAgent::OBLIVIOUS:
			break;
		case ShipAiAgent::WATCHING: {
			break;
		}
		case ShipAiAgent::FOLLOWING: {
			if (targetShip != nullptr) {
				Locker clocker(targetShip, agent);

				agent->setFollowShipObject(targetShip);
			}
			break;
		}
		case ShipAiAgent::PATROLLING:
		case ShipAiAgent::ATTACKING: {
			if (targetShip != nullptr) {
				Locker clocker(targetShip, agent);

				agent->setTargetShipObject(targetShip);
			}
			break;
		}
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
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
	Evade(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), minEvadeChance(0.015), maxEvadeChance(0.05) {
		parseArgs(args);
	}

	Evade(const Evade& a) : BehaviorSpace(a), minEvadeChance(a.minEvadeChance), maxEvadeChance(a.maxEvadeChance) {
	}

	Evade& operator=(const Evade& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);

		minEvadeChance = a.minEvadeChance;
		maxEvadeChance = a.maxEvadeChance;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		minEvadeChance = getArg<float>()(args, "minEvadeChance");
		maxEvadeChance = getArg<float>()(args, "maxEvadeChance");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (agent->getMovementState() == ShipAiAgent::EVADING)
			return SUCCESS;


		// TODO: add evade

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}

	private:
	float minEvadeChance;
	float maxEvadeChance;
};

class EngageTarget : public BehaviorSpace {
public:
	EngageTarget(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), refireMax(1.0f) {
		parseArgs(args);
	}

	EngageTarget(const EngageTarget& a) : BehaviorSpace(a), refireMax(a.refireMax) {
	}

	EngageTarget& operator=(const EngageTarget& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);

		refireMax = a.refireMax;

		return *this;
	}

	void parseArgs(const LuaObject& args) {
		refireMax = getArg<float>()(args, "refireMax");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetShipProspect"))
			return FAILURE;

		ManagedReference<ShipObject*> targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			agent->eraseBlackboard("targetShipProspect");
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
		Vector3 currentDirectionVec = agent->getCurrentDirectionVector();

		Vector3 rayStart = currentPosition;
		Vector3 rayEnd = (currentDirectionVec * 500.f) + currentPosition;
		Vector3 direction = rayEnd - rayStart;

		Vector3 difference = targetShip->getPosition() - rayStart;
		float collisionDistance = agent->getPointIntersection(direction, difference, targetShip->getBoundingRadius() * 2.f, 500);

		if (collisionDistance == FLT_MAX) {
			return FAILURE;
		}

		uint64 timeNow = System::getMiliTime();

		auto projectile = ShipProjectile(agent, 0, projectileType, 0, currentPosition, currentDirectionVec * 7800.f, 500, 500, 1.f, timeNow);
		SpaceCombatManager::instance()->addProjectile(agent, projectile);

		agent->writeBlackboard("refireInterval", timeNow);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}

	private:
	float refireMax;
};

} // namespace leafspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // FOLLOWACTIONSSPACE_H_
