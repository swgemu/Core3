/*
 * Sequence
 */

#ifndef SEQUENCE_H_
#define SEQUENCE_H_

#include "server/zone/objects/ship/ai/bt/node/Composite.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace bt {
namespace node {

class Sequence : public Composite {
public:
	Sequence(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
	}

	virtual Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class ParallelSequence : public Composite {
public:
	ParallelSequence(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
	}

	virtual Behavior::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const;
};

class RandomSequence : public Composite {
public:
	RandomSequence(const String& className, const uint32 id, const LuaObject& args) : Composite(className, id, args) {
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

#endif /* SEQUENCE_H_ */
