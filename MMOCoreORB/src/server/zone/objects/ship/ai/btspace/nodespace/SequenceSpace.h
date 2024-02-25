/*
 * SequenceSpace.h
 */

#ifndef SEQUENCESPACE_H_
#define SEQUENCESPACE_H_

#include "server/zone/objects/ship/ai/btspace/nodespace/CompositeSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace nodespace {

class SequenceSpace : public CompositeSpace {
public:
	SequenceSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
	}

	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class ParallelSequenceSpace : public CompositeSpace {
public:
	ParallelSequenceSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
	}

	virtual BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class RandomSequenceSpace : public CompositeSpace {
public:
	RandomSequenceSpace(const String& className, const uint32 id, const LuaObject& args) : CompositeSpace(className, id, args) {
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

#endif /* SEQUENCESPACE_H_ */
