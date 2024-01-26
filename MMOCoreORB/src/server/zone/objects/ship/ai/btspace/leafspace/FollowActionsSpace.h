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

	BehaviorSpace::Status execute(ShipAiAgent* ship, unsigned int startIdx = 0) const {
		if (!ship->peekBlackboard("targetShipProspect"))
			return FAILURE;

		ManagedReference<ShipObject*> targetShip = ship->readBlackboard("targetShipProspect").get<ManagedReference<ShipObject*>>();

		if (targetShip == nullptr) {
			return FAILURE;
		}

		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return FAILURE;
		}

		auto combatManager = SpaceCombatManager::instance();

		if (combatManager == nullptr) {
			return FAILURE;
		}

		auto collisionData = shipManager->getCollisionData(ship);

		if (collisionData == nullptr) {
			return FAILURE;
		}

		auto appearanceData = shipManager->getAppearanceData(ship->getShipChassisName());

		if (appearanceData == nullptr) {
			return FAILURE;
		}

		auto targetVector = ship->getTargetVector();

		if (targetVector == nullptr || targetVector->size() == 0) {
			return FAILURE;
		}

		Vector<ManagedReference<ShipObject*>> targetVectorCopy;
		targetVector->safeCopyTo(targetVectorCopy);

		Vector<uint32> weaponsIndex;

		int weaponsFiredMax = 10;
		int weaponsFired = 0;

		for (uint32 slot = Components::WEAPON_START; slot <= Components::CAPITALSLOTMAX; ++slot) {
			uint32 crc = ship->getShipComponentMap()->get(slot);

			if (crc == 0) {
				continue;
			}

			int hitpoints = ship->getCurrentHitpointsMap()->get(slot);

			if (hitpoints <= 0.f) {
				continue;
			}

			int flags = ship->getComponentOptionsMap()->get(slot);

			if (flags & ShipComponentFlag::DISABLED) {
				continue;
			}

			weaponsIndex.add(slot);
		}

		for (int i = 0; i < targetVectorCopy.size(); ++i) {
			auto target = targetVectorCopy.get(i);

			if (target == nullptr || !target->isAttackableBy(ship)) {
				continue;
			}

			Locker cLock(target, ship);

			Vector<uint32> weaponsCopy = weaponsIndex;

			for (int ii = weaponsCopy.size(); -1 < --ii;) {
				int key = System::random(ii);
				int index = weaponsCopy.get(key);

				weaponsCopy.remove(key);

				auto crc = ship->getShipComponentMap()->get(index);

				if (crc == 0) {
					continue;
				}

				auto projectileData = shipManager->getProjectileData(crc);

				if (projectileData == nullptr) {
					continue;
				}

				auto turretData = shipManager->getShipTurretData(ship->getShipChassisName(), index - Components::WEAPON_START);

				if (turretData != nullptr) {
					const auto& slotName = Components::shipComponentSlotToString(index);
					const auto& hardpoints = collisionData->getHardpoints(slotName);
					const auto& hardpoint = hardpoints.get(crc);

					if (hardpoint.getAppearanceName() == "") {
						continue;
					}

					const Matrix4& shipRotation = *ship->getRotationMatrix();
					const Vector3& shipPosition = ship->getPosition();
					const Vector3& targetPosition = ship->getInterceptPosition(target, projectileData->getSpeed(), System::random(Components::FIGHTERSLOTMAX));
					const Vector3& hardpointPosition = hardpoint.getSphere().getCenter();

					Vector3 turretGlobal = (hardpointPosition * shipRotation);
					turretGlobal = Vector3(turretGlobal.getX(), turretGlobal.getZ(), turretGlobal.getY()) + shipPosition;

					Vector3 targetGlobal = targetPosition - turretGlobal;

					if (targetGlobal.squaredLength() > projectileData->getRange() * projectileData->getRange()) {
						continue;
					}

					Vector3 targetLocal = targetGlobal;
					targetLocal = Vector3(targetLocal.getX(), targetLocal.getZ(), targetLocal.getY()) * shipRotation;

					const Matrix4* hardpointRotation = hardpoint.getRotation();

					if (hardpointRotation != nullptr) {
						targetLocal = targetLocal * *hardpointRotation;
					}

					float yaw = atan2(targetLocal.getX(), targetLocal.getZ());
					float pitch = atan2(-targetLocal.getY(), Math::sqrt(Math::sqr(targetLocal.getX()) + Math::sqr(targetLocal.getZ())));

					float maxPitch = turretData->getMaxPitch() * Math::DEG2RAD;
					float minPitch = turretData->getMinPitch() * Math::DEG2RAD;
					float maxYaw = turretData->getMaxYaw() * Math::DEG2RAD;
					float minYaw = turretData->getMinYaw() * Math::DEG2RAD;

					if (yaw < minYaw || yaw > maxYaw) {
						continue;
					}

					if (pitch < minPitch || pitch > maxPitch) {
						continue;
					}

					float accuracy = 0.05f;

					float randomX = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);
					float randomY = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);
					float randomZ = 1.f + ((System::frandom(2.f) - 1.f) * accuracy);

					targetGlobal *= Vector3(randomX, randomY, randomZ);

					if (targetGlobal != Vector3::ZERO) {
						targetGlobal.normalize();
					}

					auto projectile = new ShipProjectile(ship, index - Components::WEAPON_START, projectileData->getIndex(), 0, turretGlobal, targetGlobal * 7800.f, 500, 500, 1.f, System::getMiliTime());
					projectile->readProjectileData(projectileData);
					combatManager->addProjectile(ship, projectile);

					weaponsIndex.remove(key);
					weaponsFired += 1;
				} else {
					Vector3 difference = target->getPosition() - ship->getPosition();
					Vector3 direction = ship->getCurrentDirectionVector();

					float radius = Math::max(32.f, targetShip->getBoundingRadius());
					float range = Math::max(512.f, projectileData->getRange());
					float collisionDistance = SpaceCollisionManager::getPointIntersection(direction * range, difference, radius, range);

					if (collisionDistance == SpaceCollisionManager::MISS) {
						break;
					}

					if (projectileData->isMissile()) {
						weaponsIndex.remove(key);
						continue;
					} else if (projectileData->isCountermeasure()) {
						weaponsIndex.remove(key);
						continue;
					} else {
						auto projectile = new ShipProjectile(ship, index - Components::WEAPON_START, projectileData->getIndex(), 0, ship->getPosition(), direction * 7800.f, 500, 500, 1.f, System::getMiliTime());
						projectile->readProjectileData(projectileData);
						combatManager->addProjectile(ship, projectile);
					}

					weaponsIndex.remove(key);
					weaponsFired += 1;
				}

				if (weaponsIndex.size() == 0 || weaponsFired >= weaponsFiredMax) {
					break;
				}
			}

			if (weaponsIndex.size() == 0 || weaponsFired >= weaponsFiredMax) {
				break;
			}
		}

		ship->eraseBlackboard("refireInterval");

		uint64 timeNow = System::getMiliTime();
		ship->writeBlackboard("refireInterval", timeNow);

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
