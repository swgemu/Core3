#ifndef SIMPLEACTIONSSPACE_H_
#define SIMPLEACTIONSSPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"
#include "server/zone/objects/ship/ai/btspace/BlackboardDataSpace.h"
#include "server/zone/objects/ship/ai/ShipAiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace leafspace {

class DummySpace : public BehaviorSpace {
public:
	DummySpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	DummySpace(const DummySpace& d) : BehaviorSpace(d) {
	}

	BehaviorSpace::Status execute(ShipAiAgent*, unsigned int) const {
		return SUCCESS; // this is meant to be decorated with AlwaysXX, so this return won't matter.
	}
};

class FindNextPosition : public BehaviorSpace {
public:
	FindNextPosition(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	FindNextPosition(const FindNextPosition& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		uint32 movementState = agent->getMovementState();

		if (movementState == ShipAiAgent::FOLLOWING || movementState == ShipAiAgent::ATTACKING) {
			return agent->findNextPosition(agent->getMaxDistance()) ? SUCCESS : FAILURE;
		}

		return agent->findNextPosition(agent->getMaxDistance()) ? RUNNING : SUCCESS;
	}
};

class Wait : public BehaviorSpace {
public:
	Wait(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), duration(-1) {
		parseArgs(args);
	}

	Wait(const Wait& a) : BehaviorSpace(a), duration(a.duration) {
	}

	Wait& operator=(const Wait& a) {
		if (this == &a)
			return *this;

		BehaviorSpace::operator=(a);
		duration = a.duration;

		return *this;
	}

	void parseArgs(const LuaObject& args) {
		duration = (int)(getArg<float>()(args, "duration") * 1000);
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
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

class GeneratePatrol : public BehaviorSpace {
public:
	GeneratePatrol(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), numPoints(0), distFromHome(0.0) {
		parseArgs(args);
	}

	GeneratePatrol(const GeneratePatrol& a) : BehaviorSpace(a), numPoints(a.numPoints), distFromHome(a.distFromHome) {
	}

	GeneratePatrol& operator=(const GeneratePatrol& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);
		numPoints = a.numPoints;
		distFromHome = a.distFromHome;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		numPoints = getArg<int>()(args, "numPoints");
		distFromHome = getArg<float>()(args, "distFromHome");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
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


class ExitCombat : public BehaviorSpace {
public:
	ExitCombat(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	ExitCombat(const ExitCombat& a) : BehaviorSpace(a) {
	}

	ExitCombat& operator=(const ExitCombat& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);
		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		agent->removeDefenders();
		agent->setTargetShipObject(nullptr);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "- called";

		return msg.toString();
	}
};

class WriteBlackboard : public BehaviorSpace {
public:
	WriteBlackboard(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
		parseArgs(args);
	}

	WriteBlackboard(const WriteBlackboard& a) : BehaviorSpace(a), key(a.key), val(a.val) {
	}

	WriteBlackboard& operator=(const WriteBlackboard& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);
		key = a.key;
		val = a.val;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		key = getArg<String>()(args, "key");
		val = getArg<uint32>()(args, "val");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
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

class EraseBlackboard : public BehaviorSpace {
public:
	EraseBlackboard(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), param("") {
		parseArgs(args);
	}

	EraseBlackboard(const EraseBlackboard& a) : BehaviorSpace(a), param(a.param) {
	}

	EraseBlackboard& operator=(const EraseBlackboard& a) {
		if (this == &a)
			return *this;
		BehaviorSpace::operator=(a);
		param = a.param;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		param = getArg<String>()(args, "param");
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
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

class Leash : public BehaviorSpace {
public:
	Leash(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	Leash(const Leash& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		agent->leash();

		return SUCCESS;
	}
};

class SetAlert : public BehaviorSpace {
public:
	SetAlert(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), aggroDelay(0.f) {
		parseArgs(args);
	}

	SetAlert(const SetAlert& b) : BehaviorSpace(b), aggroDelay(b.aggroDelay) {
	}

	SetAlert& operator=(const SetAlert& b) {
		if (this == &b)
			return *this;

		BehaviorSpace::operator=(b);

		aggroDelay = b.aggroDelay;
		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		Time* alert = agent->getAlertedTime();

		if (alert == nullptr || !alert->isPast())
			return FAILURE;

		alert->updateToCurrentTime();
		alert->addMiliTime(duration);

		Time* delay = agent->getAggroDelay();

		if (delay != nullptr && delay->isPast()) {
			delay->updateToCurrentTime();
			delay->addMiliTime(aggroDelay);
			// agent->info(true) << " SetAlert Complete! Delay: " << aggroDelay;
		}

		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		aggroDelay = (int)(getArg<float>()(args, "aggroDelay") * 1000);
	}

	String print() const {
		StringBuffer msg;
		msg << className << "- Aggro Delay: " << aggroDelay;

		return msg.toString();
	}

private:
	int duration;
	int aggroDelay;
};

class SetDisabledEngineSpeed : public BehaviorSpace {
public:
	SetDisabledEngineSpeed(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args) {
	}

	SetDisabledEngineSpeed(const FindNextPosition& a) : BehaviorSpace(a) {
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {

		return agent->setDisabledEngineSpeed() ? RUNNING : SUCCESS;
	}
};

} // namespace leafspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // SIMPLEACTIONSSPACE_H_
