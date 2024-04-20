#ifndef BEHAVIOR_TREE_SLOT_H_
#define BEHAVIOR_TREE_SLOT_H_

#include "system/io/ObjectInputStream.h"
#include "system/io/ObjectOutputStream.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {

enum BehaviorTreeSlot : uint32 {
	NONE = 0,
	AWARE,
	IDLE,
	ATTACK,
	EQUIP,
	TARGET,
	MOVE,
	LOOKAT,
	AGGRO,
	SCARE,
	KILL,
	STALK,
	CRACKDOWNSCAN,
	HEAL,
	CHATREACTION,
	NOTIFYHELP,
	HARVEST,
	LASTTREESLOT
};

// These definition allow looping through slots with iterator semantics.
// The underlying assumptions are that the enum increments each member by one,
// the first member is NONE, and the last member is LASTTREESLOT, which is
// unused (because end() must return one past the end)
inline BehaviorTreeSlot operator++(BehaviorTreeSlot& in) {
	return in = (BehaviorTreeSlot)(std::underlying_type<BehaviorTreeSlot>::type(in) + 1);
}
inline BehaviorTreeSlot operator*(BehaviorTreeSlot in) { return in; }
inline BehaviorTreeSlot begin(BehaviorTreeSlot) { return BehaviorTreeSlot::NONE; }
inline BehaviorTreeSlot end(BehaviorTreeSlot) { return BehaviorTreeSlot::LASTTREESLOT; }

inline const char* getBehaviorTreeSlotName(BehaviorTreeSlot slot) {
	switch(slot) {
	case NONE:
		return "NONE";
	case AWARE:
		return "AWARE";
	case IDLE:
		return "IDLE";
	case ATTACK:
		return "ATTACK";
	case EQUIP:
		return "EQUIP";
	case TARGET:
		return "TARGET";
	case MOVE:
		return "MOVE";
	case LOOKAT:
		return "LOOKAT";
	case AGGRO:
		return "AGGRO";
	case SCARE:
		return "SCARE";
	case KILL:
		return "KILL";
	case STALK:
		return "STALK";
	case CRACKDOWNSCAN:
		return "CRACKDOWNSCAN";
	case HEAL:
		return "HEAL";
	case CHATREACTION:
		return "CHATREACTION";
	case NOTIFYHELP:
		return "NOTIFYHELP";
	case HARVEST:
		return "HARVEST";
	case LASTTREESLOT:
		return "LASTTREESLOT";
	default:
		return "";
	}

	return "";
}

}
}
}
}
}
}

using namespace sys::io;
using namespace server::zone::objects::creature::ai::bt;

template<>
class TypeInfo<BehaviorTreeSlot> : public TypeInfoAtomicUnsignedInteger<BehaviorTreeSlot> {
public:
	static bool toBinaryStream(BehaviorTreeSlot *address, ObjectOutputStream *stream) {
		stream->writeInt(static_cast<uint32>(*address));

		return true;
	}

	static bool parseFromBinaryStream(BehaviorTreeSlot *address, ObjectInputStream *stream) {
		 *address = static_cast<BehaviorTreeSlot>(stream->readInt());

		 return true;
	}
};

#endif // BEHAVIOR_TREE_SLOT_H_
