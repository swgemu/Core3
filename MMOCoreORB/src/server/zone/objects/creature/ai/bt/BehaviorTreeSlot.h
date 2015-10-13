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
	IDLE,
	COMBAT,
	ATTACK,
	EQUIP,
	TARGET,
	AWARENESS,
	REACTION,
	MOVE,
	LOOKAT,
	AGGRO,
	SCARE,
	NONE
};

}
}
}
}
}
}

using namespace sys::io;
using namespace server::zone::objects::creature::ai::bt;

template<>
class TypeInfo<BehaviorTreeSlot> : public TypeInfoAtomicUnsignedInteger<BehaviorTreeSlot>
{
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
