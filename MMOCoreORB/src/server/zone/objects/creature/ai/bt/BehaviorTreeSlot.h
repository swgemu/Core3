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

enum class BehaviorTreeSlot : uint32 {
	IDLE 	  = STRING_HASHCODE("IDLE"),
	COMBAT	  = STRING_HASHCODE("COMBAT"),
	ATTACK	  = STRING_HASHCODE("ATTACK"),
	WEAPON	  = STRING_HASHCODE("WEAPON"),
	TARGET	  = STRING_HASHCODE("TARGET"),
	AWARENESS = STRING_HASHCODE("AWARENESS"),
	REACTION  = STRING_HASHCODE("REACTION"),
	MOVE	  = STRING_HASHCODE("MOVE"),
	AWARE	  = STRING_HASHCODE("AWARE"),
	LOOKAT	  = STRING_HASHCODE("LOOKAT"),
	AGGRO	  = STRING_HASHCODE("AGGRO"),
	RUNAWAY	  = STRING_HASHCODE("RUNAWAY"),
	NONE	  = STRING_HASHCODE("NONE")
};

}
}
}
}
}
}

using namespace sys::io;

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
