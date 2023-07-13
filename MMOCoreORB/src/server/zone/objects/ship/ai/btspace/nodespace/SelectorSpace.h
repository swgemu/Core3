/*
 * SelectorSpace.h
 */

#ifndef SELECTORSPACE_H_
#define SELECTORSPACE_H_

#include "server/zone/objects/ship/ai/btspace/nodespace/CompositeSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace nodespace {

class SelectorSpace : public CompositeSpace {
public:
	SelectorSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
	}

	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class ParallelSelectorSpace : public CompositeSpace {
public:
	ParallelSelectorSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
	}

	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class RandomSelectorSpace : public CompositeSpace {
public:
	RandomSelectorSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
	}

	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

} // namespace nodespace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif /* SELECTORSPACE_H_ */
