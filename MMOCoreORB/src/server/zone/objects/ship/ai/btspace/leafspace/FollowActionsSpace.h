#ifndef FOLLOWACTIONSSPACE_H_
#define FOLLOWACTIONSSPACE_H_

#include "server/zone/objects/ship/ai/ShipAiAgent.h"
#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BlackboardDataSpace.h"
#include "server/zone/SpaceZone.h"

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
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*>>();

		if (target == nullptr || !target->isShipObject())
			return FAILURE;

		ShipObject* tarShip = target->asShipObject();

		if (tarShip == nullptr)
			return FAILURE;

		Locker clocker(tarShip, agent);

		float minMod = 0.5f; // Math::min(1.f - (tarCreo->getLevel() - agent->getLevel()) / 8.f, 1.5f);
		float mod = Math::max(0.75f, minMod);

		agent->writeBlackboard("aggroMod", mod);

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
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*>>();

		if (target == nullptr && !(agent->getShipBitmask() & ShipFlag::FOLLOW) && (state == ShipAiAgent::WATCHING || state == ShipAiAgent::FOLLOWING)) {
			agent->setFollowObject(nullptr);
			return FAILURE;
		}

		switch (state) {
		case ShipAiAgent::OBLIVIOUS:
			agent->setMovementState(ShipAiAgent::OBLIVIOUS);
			break;
		case ShipAiAgent::WATCHING: {
			if (target != nullptr) {
				Locker clocker(target, agent);

				agent->setWatchObject(target);
			}
			break;
		}
		case ShipAiAgent::FOLLOWING:
			break;
		case ShipAiAgent::PATROLLING:
		case ShipAiAgent::ATTACKING:
		case ShipAiAgent::FLEEING:
		case ShipAiAgent::LEASHING:
		case ShipAiAgent::EVADING:
		case ShipAiAgent::PATHING_HOME:
		case ShipAiAgent::FOLLOW_FORMATION:
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

class SetDefenderFromProspect : public BehaviorSpace {
public:
	SetDefenderFromProspect(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	SetDefenderFromProspect(const SetDefenderFromProspect& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("targetProspect"))
			return FAILURE;

		ManagedReference<SceneObject*> target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*>>();

		if (target == nullptr) {
			agent->eraseBlackboard("targetProspect");
			return FAILURE;
		}

		Locker clocker(target, agent);

		agent->setDefender(target);

		return agent->getMainDefender() == target ? SUCCESS : FAILURE;
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
