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
#include "server/zone/objects/ship/ShipComponentFlag.h"


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

		// agent->info(true) << agent->getDisplayedName() << " set movement state: " << state;

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

		// agent->info(true) << " DEFENDER SET FROM targetShipProspect ---  " << targetShip->getDisplayedName();

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

		// agent->info(true) << agent->getDisplayedName() << " Evade Success -- Evade Delay: " << evadeDelay;

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

class EngageSingleTarget : public BehaviorSpace {
public:
	EngageSingleTarget(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	EngageSingleTarget(const EngageSingleTarget& a) : BehaviorSpace(a) {
	}

	EngageSingleTarget& operator=(const EngageSingleTarget& a) {
		if (this == &a) {
			return *this;
		}

		BehaviorSpace::operator=(a);

		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetShipProspect")) {
			return FAILURE;
		}

		ManagedReference<ShipObject*> targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			return FAILURE;
		}

		Vector<uint32> weaponsIndex;

		// Create Index for possible weapons to attack with
		for (uint32 slot = Components::WEAPON_START; slot <= Components::CAPITALSLOTMAX; ++slot) {
			uint32 crc = agent->getShipComponentMap()->get(slot);

			if (crc == 0) {
				continue;
			}

			int hitpoints = agent->getCurrentHitpointsMap()->get(slot);

			if (hitpoints <= 0.f) {
				continue;
			}

			int flags = agent->getComponentOptionsMap()->get(slot);

			if (flags & ShipComponentFlag::DISABLED) {
				continue;
			}

			weaponsIndex.add(slot);
		}

		Locker clock(targetShip, agent);

		// Fire the weapons at the current target ship
		for (int i = 0; i < weaponsIndex.size(); i++) {
			//int key = System::random(i);
			int slot = weaponsIndex.get(i);

			if (!agent->fireWeaponAtTarget(targetShip, slot, Components::CHASSIS)) {
				continue;
			}
		}

		uint64 timeNow = System::getMiliTime();
		agent->writeBlackboard("refireInterval", timeNow);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class EngageTurrets : public BehaviorSpace {
public:
	EngageTurrets(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	EngageTurrets(const EngageTurrets& a) : BehaviorSpace(a) {
	}

	EngageTurrets& operator=(const EngageTurrets& a) {
		if (this == &a) {
			return *this;
		}

		BehaviorSpace::operator=(a);

		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetShipProspect")) {
			return FAILURE;
		}

		ManagedReference<ShipObject*> targetShip = agent->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			return FAILURE;
		}

		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return FAILURE;
		}

		auto targetVector = agent->getTargetVector();

		if (targetVector == nullptr || targetVector->size() == 0) {
			return FAILURE;
		}

		Vector<uint32> weaponsIndex;

		int weaponsFiredMax = 10;
		int weaponsFired = 0;

		for (uint32 slot = Components::WEAPON_START; slot <= Components::CAPITALSLOTMAX; ++slot) {
			uint32 crc = agent->getShipComponentMap()->get(slot);

			if (crc == 0) {
				continue;
			}

			int hitpoints = agent->getCurrentHitpointsMap()->get(slot);

			if (hitpoints <= 0.f) {
				continue;
			}

			int flags = agent->getComponentOptionsMap()->get(slot);

			if (flags & ShipComponentFlag::DISABLED) {
				continue;
			}

			weaponsIndex.add(slot);
		}

		Vector<ManagedReference<ShipObject*>> targetVectorCopy;
		targetVector->safeCopyTo(targetVectorCopy);

		for (int i = 0; i < targetVectorCopy.size(); ++i) {
			auto targetEntry = targetVectorCopy.get(i);

			if (targetEntry == nullptr || !targetEntry->isAttackableBy(agent)) {
				continue;
			}

			Locker cLock(targetEntry, agent);

			Vector<uint32> weaponsCopy = weaponsIndex;

			for (int ii = weaponsCopy.size(); -1 < --ii;) {
				int key = System::random(ii);
				int slot = weaponsCopy.get(key);

				weaponsCopy.remove(key);

				auto turretData = shipManager->getShipTurretData(agent->getShipChassisName(), slot - Components::WEAPON_START);

				if (turretData != nullptr) {
					if (agent->fireTurretAtTarget(targetEntry, slot, Components::CHASSIS)) {
						weaponsIndex.remove(key);
						weaponsFired += 1;
					}
				} else {
					if (agent->fireWeaponAtTarget(targetEntry, slot, Components::CHASSIS)) {
						weaponsIndex.remove(key);
						weaponsFired += 1;
					}
				}

				if (weaponsIndex.size() == 0 || weaponsFired >= weaponsFiredMax) {
					break;
				}
			}

			if (weaponsIndex.size() == 0 || weaponsFired >= weaponsFiredMax) {
				break;
			}
		}

		uint64 timeNow = System::getMiliTime();
		agent->writeBlackboard("refireInterval", timeNow);

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
		agent->eraseBlackboard("targetShipProspect");

		ManagedReference<TangibleObject*> topThreat = agent->getThreatMap()->getHighestThreatAttacker();

		// Make sure top threat is not null and is a ship
		if (topThreat == nullptr || !topThreat->isShipObject()) {
			return FAILURE;
		}

		ManagedReference<ShipObject*> targetShip = topThreat->asShipObject();

		if (targetShip == nullptr)
			return FAILURE;

		Locker lock(targetShip, agent);

		// agent->info(true) << " NEW THREAT SET ---  Top Threat setting targetShipProspect: " << targetShip->getDisplayedName();

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
