#ifndef BEHAVIORTREESLOTSPACE_H_
#define BEHAVIORTREESLOTSPACE_H_

#include "system/io/ObjectInputStream.h"
#include "system/io/ObjectOutputStream.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {

enum BehaviorTreeSlotSpace : uint32 { NONE = 0, AWARE, IDLE, ATTACK, LASTTREESLOT };

// These definition allow looping through slots with iterator semantics.
// The underlying assumptions are that the enum increments each member by one,
// the first member is NONE, and the last member is LASTTREESLOT, which is
// unused (because end() must return one past the end)
inline BehaviorTreeSlotSpace operator++(BehaviorTreeSlotSpace &in) {
	return in = (BehaviorTreeSlotSpace)(std::underlying_type<BehaviorTreeSlotSpace>::type(in) + 1);
}
inline BehaviorTreeSlotSpace operator*(BehaviorTreeSlotSpace in) {
	return in;
}
inline BehaviorTreeSlotSpace begin(BehaviorTreeSlotSpace) {
	return BehaviorTreeSlotSpace::NONE;
}
inline BehaviorTreeSlotSpace end(BehaviorTreeSlotSpace) {
	return BehaviorTreeSlotSpace::LASTTREESLOT;
}

inline const char *getBehaviorTreeSlotName(BehaviorTreeSlotSpace slot) {
	switch (slot) {
	case NONE:
		return "NONE";
	case AWARE:
		return "MOVE";
	case IDLE:
		return "IDLE";
	default:
		return "";
	}

	return "";
}

} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace sys::io;
using namespace server::zone::objects::ship::ai::btspace;

template <>
class TypeInfo<BehaviorTreeSlotSpace> : public TypeInfoAtomicUnsignedInteger<BehaviorTreeSlotSpace> {
public:
	static bool toBinaryStream(BehaviorTreeSlotSpace *address, ObjectOutputStream *stream) {
		stream->writeInt(static_cast<uint32>(*address));

		return true;
	}

	static bool parseFromBinaryStream(BehaviorTreeSlotSpace *address, ObjectInputStream *stream) {
		*address = static_cast<BehaviorTreeSlotSpace>(stream->readInt());

		return true;
	}
};

#endif // BEHAVIORTREESLOTSPACE_H_
