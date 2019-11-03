#ifndef IF_H_
#define IF_H_

#include "server/zone/objects/creature/ai/bt/decorator/Decorator.h"

#include <cassert>

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace decorator {

class If : public Decorator {
public:
	If(const String& className, const uint32 id, const LuaObject& args)
			: Decorator(className, id, args) {
	}

	If(const If& b)
			: Decorator(b) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		assert(child != nullptr);

		return child->doAction(agent);
	}
};

}
}
}
}
}
}
}

#endif // IF_H_
