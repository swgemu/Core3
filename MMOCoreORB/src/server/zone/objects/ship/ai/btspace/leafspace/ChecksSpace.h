#ifndef CHECKSSPACE_H_
#define CHECKSSPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace leafspace {

// helper enum to ensure we have exactly one template realization per check typedef
enum CheckTypeSpace {

};

// template class to reduce repeated code. Do this instead of inheritance so we
// don't have to retype the ctors (which would be exactly the same)
template <typename val_type, CheckTypeSpace C>
class _CheckSpace : public BehaviorSpace {
public:
	_CheckSpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), checkVar((val_type)(0)) {
		parseArgs(args);
	}

	_CheckSpace(const _CheckSpace& c) : BehaviorSpace(c), checkVar(c.checkVar) {
	}

	_CheckSpace& operator=(const _CheckSpace& c) {
		if (this == &c)
			return *this;

		BehaviorSpace::operator=(c);

		checkVar = c.checkVar;
		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
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

} // namespace leafspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // CHECKSSPACE_H_
