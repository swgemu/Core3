#ifndef SIMPLEACTIONS_H_
#define SIMPLEACTIONS_H_

#include "server/zone/objects/ship/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace leaf {

class Dummy : public Behavior {
public:
	Dummy(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	Dummy(const Dummy& d) : Behavior(d) {
	}

	Behavior::Status execute(ShipAiAgent*, unsigned int) const {
		return SUCCESS; // this is meant to be decorated with AlwaysXX, so this return won't matter.
	}
};
/*
class GeneratePatrol : public Behavior {
public:
	GeneratePatrol(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), numPoints(0), distFromHome(0.0) {
		parseArgs(args);
	}

	GeneratePatrol(const GeneratePatrol& a) : Behavior(a), numPoints(a.numPoints), distFromHome(a.distFromHome) {
	}

	GeneratePatrol& operator=(const GeneratePatrol& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		numPoints = a.numPoints;
		distFromHome = a.distFromHome;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		numPoints = getArg<int>()(args, "numPoints");
		distFromHome = getArg<float>()(args, "distFromHome");
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		return agent->generatePatrol(numPoints, distFromHome) ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << numPoints << ":" << distFromHome;

		return msg.toString();
	}

private:
	int numPoints;
	float distFromHome;
};

class ExitCombat : public Behavior {
public:
	ExitCombat(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), clearDefenders(false) {
		parseArgs(args);
	}

	ExitCombat(const ExitCombat& a) : Behavior(a), clearDefenders(a.clearDefenders) {
	}

	ExitCombat& operator=(const ExitCombat& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		clearDefenders = a.clearDefenders;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		clearDefenders = getArg<bool>()(args, "clearDefenders");
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->isInCombat())
			return FAILURE;

		agent->clearQueueActions(true);
		agent->clearCombatState(clearDefenders);

		return !agent->isInCombat() ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << clearDefenders;

		return msg.toString();
	}

private:
	bool clearDefenders;
};

class WriteBlackboard : public Behavior {
public:
	WriteBlackboard(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
		parseArgs(args);
	}

	WriteBlackboard(const WriteBlackboard& a) : Behavior(a), key(a.key), val(a.val) {
	}

	WriteBlackboard& operator=(const WriteBlackboard& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		key = a.key;
		val = a.val;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		key = getArg<String>()(args, "key");
		val = getArg<uint32>()(args, "val");
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		agent->writeBlackboard(key, val);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << key << ":" << val;

		return msg.toString();
	}

private:
	String key;
	uint32 val;
};

class EraseBlackboard : public Behavior {
public:
	EraseBlackboard(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), param("") {
		parseArgs(args);
	}

	EraseBlackboard(const EraseBlackboard& a) : Behavior(a), param(a.param) {
	}

	EraseBlackboard& operator=(const EraseBlackboard& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		param = a.param;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		param = getArg<String>()(args, "param");
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		agent->eraseBlackboard(param);
		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << param;

		return msg.toString();
	}

private:
	String param;
};

class FindNextPosition : public Behavior {
public:
	FindNextPosition(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	FindNextPosition(const FindNextPosition& a) : Behavior(a) {
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		DataVal mode = DataVal::WALK;

		if (agent->peekBlackboard("moveMode"))
			mode = static_cast<DataVal>(agent->readBlackboard("moveMode").get<uint32>());

		uint32 movementState = agent->getMovementState();

		if (movementState == ShipAiAgent::FOLLOWING) {
			return agent->findNextPosition(agent->getMaxDistance(), mode == DataVal::WALK) ? SUCCESS : FAILURE;
		}

		return agent->findNextPosition(agent->getMaxDistance(), mode == DataVal::WALK) ? RUNNING : SUCCESS;
	}
};

class Leash : public Behavior {
public:
	Leash(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	Leash(const Leash& a) : Behavior(a) {
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		agent->leash();
		return SUCCESS;
	}
};


class Wait : public Behavior {
public:
	Wait(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), duration(-1) {
		parseArgs(args);
	}

	Wait(const Wait& a) : Behavior(a), duration(a.duration) {
	}

	Wait& operator=(const Wait& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		duration = a.duration;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		duration = (int)(getArg<float>()(args, "duration") * 1000);
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		// we don't need to check a value. Just checking to see if this value
		// exists on the blackboard is fine since it can never be false
		if (agent->peekBlackboard("isWaiting")) {
			if (agent->isWaiting() || duration < 0) // < 0 means indefinite wait
				return RUNNING;
			else {
				agent->eraseBlackboard("isWaiting");
				return SUCCESS;
			}
		}

		agent->setWait(duration);
		agent->writeBlackboard("isWaiting", true);

		return RUNNING;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << duration;

		return msg.toString();
	}

private:
	int duration;
};

class SetAlert : public Behavior {
public:
	SetAlert(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), duration(0.f), show(true) {
		parseArgs(args);
	}

	SetAlert(const SetAlert& b) : Behavior(b), duration(b.duration), show(b.show) {
	}

	SetAlert& operator=(const SetAlert& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		duration = b.duration;
		show = b.show;
		return *this;
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		Time* alert = agent->getAlertedTime();

		if (alert == nullptr || !alert->isPast())
			return FAILURE;

		alert->updateToCurrentTime();
		alert->addMiliTime(duration);

		Time* delay = agent->getAggroDelay();
		if (delay != nullptr && delay->isPast()) {
			delay->updateToCurrentTime();
			uint32 newDelay = 5000;
			delay->addMiliTime(newDelay);
		}

		if (agent->getPosture() != CreaturePosture::UPRIGHT)
			agent->setPosture(CreaturePosture::UPRIGHT, true);

		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*>>().get();

		if (show && target != nullptr && target->isPlayerCreature()) {
			agent->showFlyText("npc_reaction/flytext", "alert", 255, 0, 0);

			if (agent->isNpc() && agent->getFaction() > 0 && agent->isAggressiveTo(target->asCreatureObject()))
				agent->doAnimation("search");

			agent->sendReactionChat(target, ReactionManager::ALERT);
		}

		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		duration = (int)(getArg<float>()(args, "duration") * 1000);
		show = getArg<bool>()(args, "show");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << duration << ":" << show;

		return msg.toString();
	}

private:
	int duration;
	bool show;
};
*/

} // namespace leaf
} // namespace bt
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // SIMPLEACTIONS_H_
