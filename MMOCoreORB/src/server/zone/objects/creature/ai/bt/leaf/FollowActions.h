#ifndef FOLLOWACTIONS_H_
#define FOLLOWACTIONS_H_

#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/gcw/observers/SquadObserver.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/creature/events/DroidHarvestTask.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {

class GetProspectFromThreatMap : public Behavior {
public:
	GetProspectFromThreatMap(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	GetProspectFromThreatMap(const GetProspectFromThreatMap& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->eraseBlackboard("targetProspect");

		ManagedReference<SceneObject*> tar = agent->getThreatMap()->getHighestThreatAttacker();
		if (tar == nullptr)
			return FAILURE;

		Locker clocker(tar, agent);

		agent->writeBlackboard("targetProspect", tar);

		return SUCCESS;
	}
};

class GetProspectFromDefenders : public Behavior {
public:
	GetProspectFromDefenders(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	GetProspectFromDefenders(const GetProspectFromDefenders& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->eraseBlackboard("targetProspect");

		ManagedReference<SceneObject*> tar = agent->getMainDefender();
		if (tar == nullptr)
			return FAILURE;

		Locker clocker(tar, agent);

		agent->writeBlackboard("targetProspect", tar);

		return SUCCESS;
	}
};

class GetProspectFromTarget : public Behavior {
public:
	GetProspectFromTarget(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	GetProspectFromTarget(const GetProspectFromTarget& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> followCopy = agent->getFollowObject();

		if (followCopy == nullptr || !followCopy->isCreatureObject()) {
			return FAILURE;
		}

		Locker fLocker(followCopy, agent);

		if (agent->hasDefender(followCopy)) {
			return SUCCESS;
		}

		ManagedReference<CreatureObject*> followCreo = followCopy->asCreatureObject();

		if (followCreo == nullptr || !followCreo->isInCombat())
			return FAILURE;

		ManagedReference<SceneObject*> target = agent->getTargetFromTargetsMap(followCreo);

		if (target == nullptr) {
			return FAILURE;
		}

		Locker clocker(target, agent);

		agent->sendReactionChat(target, ReactionManager::ALLY);

		agent->writeBlackboard("targetProspect", target);

		return SUCCESS;
	}
};

class GetProspectFromCommand : public Behavior {
public:
	GetProspectFromCommand(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	GetProspectFromCommand(const GetProspectFromCommand& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr || !agent->isPet())
			return FAILURE;

		agent->eraseBlackboard("targetProspect");

		Reference<PetControlDevice*> cd = agent->getControlDevice().castTo<PetControlDevice*>();
		if (cd == nullptr)
			return FAILURE;

		ManagedReference<SceneObject*> tar = cd->getLastCommandTarget().get();
		if (tar == nullptr)
			return FAILURE;

		Locker clocker(tar, agent);

		agent->writeBlackboard("targetProspect", tar);

		return SUCCESS;
	}
};

class RestoreFollow : public Behavior {
public:
	RestoreFollow(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	RestoreFollow(const RestoreFollow& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->restoreFollowObject();
		return agent->getFollowObject() != nullptr ? SUCCESS : FAILURE;
	}
};

class DropProspectFromDefenders : public Behavior {
public:
	DropProspectFromDefenders(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	DropProspectFromDefenders(const DropProspectFromDefenders& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect"))
			return SUCCESS;

		ManagedReference<SceneObject*> tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();
		if (tar == nullptr) {
			agent->eraseBlackboard("targetProspect");
			return SUCCESS;
		}

		Locker clocker(tar, agent);

		agent->removeDefender(tar);
		agent->eraseBlackboard("targetProspect");

		return agent->hasDefender(tar) ? FAILURE : SUCCESS;
	}
};

class SetDefenderFromProspect : public Behavior {
public:
	SetDefenderFromProspect(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	SetDefenderFromProspect(const SetDefenderFromProspect& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect"))
			return FAILURE;

		ManagedReference<SceneObject*> tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();
		if (tar == nullptr) {
			agent->eraseBlackboard("targetProspect");
			return FAILURE;
		}

		Locker clocker(tar, agent);

		agent->setDefender(tar);

		return agent->getMainDefender() == tar ? SUCCESS : FAILURE;
	}
};

class KillProspect : public Behavior {
public:
	KillProspect(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	KillProspect(const KillProspect& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect")) {
			return FAILURE;
		}

		ManagedReference<SceneObject*> tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == nullptr) {
			agent->eraseBlackboard("targetProspect");
			return FAILURE;
		}

		Locker clocker(tar, agent);

		return agent->killPlayer(tar) ? SUCCESS : FAILURE;
	}
};

class UpdateRangeToFollow : public Behavior {
public:
	UpdateRangeToFollow(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	UpdateRangeToFollow(const UpdateRangeToFollow& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();
		if (followCopy == nullptr)
			return FAILURE;

		Locker clocker(followCopy, agent);

		float dist = agent->getDistanceTo(followCopy) - followCopy->getTemplateRadius() - agent->getTemplateRadius();
		agent->writeBlackboard("followRange", BlackboardData(dist));

		return SUCCESS;
	}
};

class SetMovementState : public Behavior {
public:
	SetMovementState(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), state(0) {
		parseArgs(args);
	}

	SetMovementState(const SetMovementState& a)
			: Behavior(a), state(a.state) {
	}

	SetMovementState& operator=(const SetMovementState& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		state = a.state;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> tar = nullptr;
		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == nullptr && !(agent->getCreatureBitmask() & CreatureFlag::FOLLOW) && (state == AiAgent::WATCHING || state == AiAgent::STALKING || state == AiAgent::FOLLOWING)) {
			agent->setFollowObject(nullptr);
			return FAILURE;
		}

		switch (state) {
		case AiAgent::OBLIVIOUS:
			agent->setOblivious();
			break;
		case AiAgent::WATCHING: {
			if (tar != nullptr) {
				Locker clocker(tar, agent);
				agent->setWatchObject(tar);
			}
			break;
		}
		case AiAgent::STALKING: {
			if (tar != nullptr) {
				Locker clocker(tar, agent);
				agent->setStalkObject(tar);
			}
			break;
		}
		case AiAgent::FOLLOWING:
			break;
		case AiAgent::PATROLLING:
		case AiAgent::FLEEING:
		case AiAgent::LEASHING:
		default:
			agent->setMovementState(state);
			break;
		};

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

class CalculateAggroMod : public Behavior {
public:
	CalculateAggroMod(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> tar = nullptr;
		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == nullptr || !tar->isCreatureObject())
			return FAILURE;

		CreatureObject* tarCreo = tar->asCreatureObject();

		if (tarCreo == nullptr)
			return FAILURE;

		Locker clocker(tarCreo, agent);

		float minMod = Math::min(1.f - (tarCreo->getLevel() - agent->getLevel()) / 8.f, 1.5f);
		float mod = Math::max(0.75f, minMod);
		agent->writeBlackboard("aggroMod", mod);

		return agent->peekBlackboard("aggroMod") ? SUCCESS : FAILURE;
	}
};

class RunAway : public Behavior {
public:
	RunAway(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), dist(0.f) {
		parseArgs(args);
	}

	RunAway(const RunAway& b)
			: Behavior(b), dist(b.dist) {
	}

	RunAway& operator=(const RunAway& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		dist = b.dist;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr || !agent->isMonster() || agent->getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
			return FAILURE;

		ManagedReference<SceneObject*> tar = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == nullptr || !tar->isCreatureObject())
			return FAILURE;

		Locker clocker(tar, agent);

		float aggroMod = 1.f;

		if (agent->peekBlackboard("aggroMod"))
			aggroMod = agent->readBlackboard("aggroMod").get<float>();

		int radius = agent->getAggroRadius();

		if (radius == 0)
			radius = AiAgent::DEFAULTAGGRORADIUS;

		float distance = Math::max(dist, dist - radius * aggroMod);

		agent->writeBlackboard("fleeRange", distance);
		agent->runAway(tar->asCreatureObject(), distance, false);
		agent->showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);

		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		dist = getArg<float>()(args, "dist");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << dist;

		return msg.toString();
	}

private:
	float dist;
};

class Evade : public Behavior {
public:
	Evade(const String& className, const uint32 id, const LuaObject& args)
		: Behavior(className, id, args), minEvadeChance(0.015), maxEvadeChance(0.05) {
			parseArgs(args);
	}

	Evade(const Evade& a)
			: Behavior(a), minEvadeChance(a.minEvadeChance), maxEvadeChance(a.maxEvadeChance) {
	}

	Evade& operator=(const Evade& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		minEvadeChance = a.minEvadeChance;
		maxEvadeChance = a.maxEvadeChance;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		minEvadeChance = getArg<float>()(args, "minEvadeChance");
		maxEvadeChance = getArg<float>()(args, "maxEvadeChance");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->isInCombat() || agent->isPet())
			return FAILURE;

		if (agent->getMovementState() == AiAgent::EVADING)
			return SUCCESS;

		Zone* zone = agent->getZoneUnsafe();

		if (zone == nullptr)
			return FAILURE;

		// TODO: Change when we can do interior pathing
		if (agent->getParentID() != 0)
			return FAILURE;

		float minDist = 15.f;
		float maxDist = 20.f;

		float minChance = minEvadeChance;
		float maxChance = maxEvadeChance;

		float primaryRange = 0;
		float secondaryRange = 0;

		if (agent->getPrimaryWeapon() != nullptr)
			primaryRange = agent->getPrimaryWeapon()->getMaxRange();

		if (agent->getSecondaryWeapon() != nullptr)
			secondaryRange = agent->getSecondaryWeapon()->getMaxRange();

		// No need to evade if creature is melee only
		if (primaryRange < 10.f && secondaryRange < 10.f)
			return FAILURE;

		// Current weapon is melee. We do not need to evade when melee
		if (agent->getWeapon() != nullptr) {
			float idealRange = agent->getWeapon()->getIdealRange();

			if (idealRange < 10.f) {
				return FAILURE;
			}
		}

		ManagedReference<SceneObject*> tar = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >();

		if (tar == nullptr || !tar->isCreatureObject())
			return FAILURE;

		CreatureObject* tarCreo = tar->asCreatureObject();

		if (tarCreo == nullptr)
			return FAILURE;

		Locker clocker(tarCreo, agent);

		if (tarCreo->isPlayerCreature()) {
			float playerWeaponRange = 0;

			if (tarCreo->getWeapon() != nullptr)
				playerWeaponRange = tarCreo->getWeapon()->getMaxRange();

			if (playerWeaponRange < 10.f) {
				minDist = 5.f;

				if (System::random(100) < 30)
					maxDist = playerWeaponRange + 5;
				else
					maxDist = playerWeaponRange - 1;

				if (minDist > maxDist)
					minDist = maxDist;
			}
		}

		if (minChance > maxChance)
			minChance = maxChance;

		float finalChance = maxChance;
		float chanceDiff = maxChance - minChance;
		float diffModifier = chanceDiff * (agent->getHAM(CreatureAttribute::HEALTH) / agent->getMaxHAM(CreatureAttribute::HEALTH));
		finalChance -= chanceDiff * diffModifier;
		finalChance *= 100;

		int randRoll = System::random(100);

		if (finalChance < 100 && randRoll > finalChance)
			return FAILURE;

		float distance = minDist + System::random(maxDist - minDist);
		float angle = System::random(360) * Math::DEG2RAD;

		float newX = tarCreo->getPositionX() + (cos(angle) * distance);
		float newY = tarCreo->getPositionY() + (sin(angle) * distance);

		float newZ = zone->getHeight(newX, newY);

		Vector3 position = Vector3(newX, newY, newZ);

		if (CollisionManager::checkSphereCollision(position, 5, zone))
			return FAILURE;

		agent->setMovementState(AiAgent::EVADING);
		agent->setNextPosition(position.getX(), position.getZ(), position.getY(), agent->getParent().get().castTo<CellObject*>());

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

class StalkProspect : public Behavior {
public:
	StalkProspect(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	StalkProspect(const StalkProspect& a) : Behavior(a) {
	}
	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		Time* alert = agent->getAlertedTime();

		if (alert == nullptr || !alert->isPast())
			return FAILURE;

		ManagedReference<SceneObject*> tar = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			tar = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

		if (tar == nullptr)
			return FAILURE;

		int stalkRad = agent->getAggroRadius();

		if (stalkRad == 0)
			stalkRad = AiAgent::DEFAULTAGGRORADIUS;

		float aggroMod = agent->readBlackboard("aggroMod").get<float>();
		stalkRad *= aggroMod * 2;
		agent->writeBlackboard("stalkRadius", stalkRad);

		Locker clocker(tar, agent);

		if (!tar->isInRange(agent, stalkRad)) {
			return FAILURE;
		}

		if (!agent->stalkProspect(tar))
			return FAILURE;

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class Flee : public Behavior {
public:
	Flee(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), delay(0) {
		parseArgs(args);
	}

	Flee(const Flee& a) : Behavior(a), delay(a.delay) {
	}

	Flee& operator=(const Flee& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		delay = a.delay;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		delay = getArg<float>()(args, "delay");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

		if (target != nullptr && target->isCreatureObject()) {
			CreatureObject* targetCreo = target->asCreatureObject();
			Time* fleeDelay = agent->getFleeDelay();

			if (targetCreo != nullptr && fleeDelay != nullptr) {
				Locker clocker(targetCreo, agent);

				fleeDelay->updateToCurrentTime();
				fleeDelay->addMiliTime(delay * 1000);

				if (!agent->isInRange(target, 40.f))
					return FAILURE;

				float distance = System::random(20) + 25;

				agent->clearQueueActions(true);
				agent->writeBlackboard("fleeRange", distance);

				agent->runAway(targetCreo, distance, false);
				return SUCCESS;
			}
		}

		return FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}

	private:
	int delay;
};

class PetReturn : public Behavior {
public:
	PetReturn(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	PetReturn(const PetReturn& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr || !agent->isPet())
			return FAILURE;

		Reference<PetControlDevice*> controlDevice = agent->getControlDevice().castTo<PetControlDevice*>();

		if (controlDevice == nullptr)
			return FAILURE;

		ManagedReference<SceneObject*> newFollow = controlDevice->getLastCommander();

		uint32 lastCommand = controlDevice->getLastCommand();

		if (lastCommand == PetManager::PATROL) {
			Locker clocker(controlDevice, agent);

			if (controlDevice->getPatrolPointSize() == 0)
				return FAILURE;

			Locker dlocker(controlDevice, agent);
			controlDevice->setLastCommandTarget(nullptr);

			agent->setFollowObject(nullptr);
			agent->setMovementState(AiAgent::PATROLLING);
			agent->clearSavedPatrolPoints();

			for (int i = 0; i < controlDevice->getPatrolPointSize(); i++) {
				PatrolPoint point = controlDevice->getPatrolPoint(i);
				agent->addPatrolPoint(point);
			}

			return SUCCESS;
		} else if (lastCommand == PetManager::GUARD || lastCommand == PetManager::FOLLOWOTHER) {
			newFollow = controlDevice->getLastCommandTarget();
		} else {
			newFollow = agent->getLinkedCreature().get();
		}

		if (newFollow == nullptr) {
			return FAILURE;
		}

		Locker dlocker(controlDevice, agent);
		controlDevice->setLastCommandTarget(newFollow);

		Locker flocker(newFollow, agent);
		agent->setFollowObject(newFollow);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class FollowSquadLeader : public Behavior {
public:
	FollowSquadLeader(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	FollowSquadLeader(const FollowSquadLeader& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr)
			return FAILURE;

		ManagedReference<SquadObserver*> squadObserver = nullptr;
		SortedVector<ManagedReference<Observer*>> observers = agent->getObservers(ObserverEventType::SQUAD);

		for (int i = 0; i < observers.size(); i++) {
			squadObserver = cast<SquadObserver*>(observers.get(i).get());
			if (squadObserver != nullptr)
				break;
		}

		if (squadObserver == nullptr)
			return FAILURE;

		AiAgent* squadLeader = squadObserver->getMember(0);

		if (squadLeader == nullptr || squadLeader == agent)
			return FAILURE;

		ManagedReference<SceneObject*> followCopy = agent->getFollowObject().get();

		if (followCopy != nullptr && followCopy == squadLeader) {
			return FAILURE;
		}

		Locker clocker(squadLeader, agent);

		agent->addCreatureFlag(CreatureFlag::FOLLOW);
		agent->setFollowObject(squadLeader);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class GetHealTarget : public Behavior {
public:
	GetHealTarget(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), range(0.f) {
		parseArgs(args);
	}

	GetHealTarget(const GetHealTarget& a) : Behavior(a), range(a.range){
	}

	GetHealTarget& operator=(const GetHealTarget& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		range = a.range;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

		if (target == nullptr || !target->isCreatureObject())
			return FAILURE;

		ManagedReference<CreatureObject*> targetCreo = target->asCreatureObject();

		if (targetCreo != nullptr) {
			const DeltaVector<ManagedReference<SceneObject*>>* defenderList = targetCreo->getDefenderList();

			if (defenderList != nullptr && defenderList->size() > 0) {
				int healTar = System::random(defenderList->size() - 1);

				ManagedReference<SceneObject*> healTarget = defenderList->get(healTar);

				if (healTarget == nullptr || !healTarget->isCreatureObject())
					return FAILURE;

				ManagedReference<CreatureObject*> healCreo = healTarget->asCreatureObject();

				if (healCreo == nullptr || healCreo->isDead())
					return FAILURE;

				if (healCreo == agent) {
					agent->writeBlackboard("healTarget", healCreo);
					return SUCCESS;
				}

				Locker clocker(healCreo, agent);

				if (healCreo->isAggressiveTo(agent) || agent->isAggressiveTo(healCreo))
					return FAILURE;

				if (healCreo->getFaction() > 0 && (healCreo->getFaction() != agent->getFaction() && healCreo->getFactionStatus() > FactionStatus::ONLEAVE)) {
					return FAILURE;
				}

				float distSq = agent->getPosition().squaredDistanceTo(healCreo->getPosition());

				if (distSq > range * range)
					return FAILURE;

				agent->setMovementState(AiAgent::MOVING_TO_HEAL);
				agent->writeBlackboard("healTarget", healCreo);

				return SUCCESS;
			}
		}

		return FAILURE;
	}

	void parseArgs(const LuaObject& args) {
		range = (float) (getArg<float>()(args, "range"));
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << range;

		return msg.toString();
	}

private:
	float range;
};

class RestorePetPatrols : public Behavior {
public:
	RestorePetPatrols(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	RestorePetPatrols(const RestorePetPatrols& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr || !agent->isPet())
			return FAILURE;

		ManagedReference<PetControlDevice*> pcd = agent->getControlDevice().get().castTo<PetControlDevice*>();

		if (pcd == nullptr)
			return FAILURE;

		for (int i = 0; i < pcd->getPatrolPointSize(); ++i) {
			PatrolPoint patrolPoint = pcd->getPatrolPoint(i);

			agent->addPatrolPoint(patrolPoint);
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

class DroidHarvest : public Behavior {
public:
	DroidHarvest(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	DroidHarvest(const DroidHarvest& a) : Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr || agent->isDead() || agent->isIncapacitated() || !agent->isDroid())
			return FAILURE;

		ManagedReference<DroidObject*> droid = cast<DroidObject*>(agent);

		if (droid == nullptr)
			return FAILURE;

		auto module = droid->getModule("harvest_module").castTo<DroidHarvestModuleDataComponent*>();

		if (module == nullptr)
			return FAILURE;

		ManagedReference<SceneObject*> target = nullptr;

		if (!agent->peekBlackboard("harvestTarget")) {
			if (!module->hasMoreTargets())
				return FAILURE;

			uint64 targetID = module->getNextHarvestTarget();

			ZoneServer* zoneServer = agent->getZoneServer();

			if (zoneServer == nullptr)
				return FAILURE;

			target = zoneServer->getObject(targetID, true);
		} else {
			target = agent->readBlackboard("harvestTarget").get<ManagedReference<SceneObject*> >();
		}

		if (target == nullptr || !target->isCreature())
			return FAILURE;

		Locker cLocker(target, agent);

		agent->writeBlackboard("harvestTarget", target);

		CreatureObject* tarCreo = target->asCreatureObject();

		if (tarCreo == nullptr || !tarCreo->isDead())
			return FAILURE;

		ManagedReference<CreatureObject*> owner = agent->getLinkedCreature().get();

		if (owner == nullptr) {
			return FAILURE;
		}

		Locker olock(owner, agent);

		// Droid must have power move to module itself.
		if (!droid->hasPower()) {
			droid->showFlyText("npc_reaction/flytext", "low_power", 204, 0, 0); // "*Low Power*

			return FAILURE;
		}

		if (!tarCreo->isInRange(owner, 64.0f)) {
			agent->eraseBlackboard("harvestTarget");

			agent->setFollowObject(owner);
			agent->storeFollowObject();
			agent->setMovementState(AiAgent::FOLLOWING);

			return FAILURE;
		}

		if (!tarCreo->isInRange(droid, 7.0f + tarCreo->getTemplateRadius() + droid->getTemplateRadius())) {
			agent->setMovementState(AiAgent::HARVESTING);
			agent->setNextPosition(tarCreo->getPositionX(), tarCreo->getPositionZ(), tarCreo->getPositionY(), tarCreo->getParent().get().castTo<CellObject*>());

			droid->notifyObservers(ObserverEventType::STARTCOMBAT, owner);

			return SUCCESS;
		}

		Reference<Task*> task = new DroidHarvestTask(module, tarCreo);
		Core::getTaskManager()->executeTask(task);

		agent->eraseBlackboard("harvestTarget");

		if (!module->hasMoreTargets()) {
			agent->setFollowObject(owner);
			agent->storeFollowObject();
			agent->setMovementState(AiAgent::FOLLOWING);
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-";

		return msg.toString();
	}
};

}
}
}
}
}
}
}

#endif // FOLLOWACTIONS_H_
