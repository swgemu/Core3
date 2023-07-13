/*
 * Selector.h
 */

#ifndef SELECTOR_H_
#define SELECTOR_H_

#include "server/zone/objects/ship/ai/bt/node/Composite.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace node {

class Selector : public Composite {
public:
	Selector(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
	}

	virtual Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class ParallelSelector : public Composite {
public:
	ParallelSelector(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
	}

	virtual Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class RandomSelector : public Composite {
public:
	RandomSelector(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
	}

	virtual Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

} // namespace node
} // namespace bt
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif /* SELECTOR_H_ */
