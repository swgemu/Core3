#ifndef CHECKS_H_
#define CHECKS_H_

#include "server/zone/objects/ship/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace leaf {

// helper enum to ensure we have exactly one template realization per check typedef
enum CheckType {

};

// template class to reduce repeated code. Do this instead of inheritance so we
// don't have to retype the ctors (which would be exactly the same)
template <typename val_type, CheckType C>
class _Check : public Behavior {
public:
	_Check(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args), checkVar((val_type)(0)) {
		parseArgs(args);
	}

	_Check(const _Check& c) : Behavior(c), checkVar(c.checkVar) {
	}

	_Check& operator=(const _Check& c) {
		if (this == &c)
			return *this;
		Behavior::operator=(c);
		checkVar = c.checkVar;
		return *this;
	}

	Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(agent != nullptr);

		return check(agent) ? SUCCESS : FAILURE;
	}

	bool check(ShipAiAgent*) const;

	void parseArgs(const LuaObject& args) {
		checkVar = getArg<val_type>()(args, "condition");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << checkVar;

		return msg.toString();
	}

protected:
	val_type checkVar;
};

// typedef _Check<uint32, CHECK_POSTURE> CheckPosture;
// template<> bool CheckPosture::check(ShipAiAgent* agent) const;

} // namespace leaf
} // namespace bt
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // CHECKS_H_
