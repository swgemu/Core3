/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef COMMANDQUEUEACTION_H_
#define COMMANDQUEUEACTION_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {
	   class SceneObject;
   }
  }
 }
}

using namespace server::zone::objects::scene;

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
	   class CreatureObject;
   }
  }
 }
}

using namespace server::zone::objects::creature;

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace commands {
	class QueueCommand;
}
}
}
}
}

using namespace server::zone::objects::creature::commands;

class CommandQueueAction : public Object {
	ManagedReference<CreatureObject*> creature;
	uint64 target;
	uint32 queueCommand;

	uint32 actionCounter;

	UnicodeString arguments;

	int compareToCounter;

public:
	CommandQueueAction(CreatureObject* cr, uint64 tar, uint32 command, uint32 acntr, const UnicodeString& amod);

	void run();

	void clearError(uint32 tab1, uint32 tab2 = 0) {
		clear(0.0f, tab1, tab2);
	}

	void clear(float timer, uint32 tab1 = 0, uint32 tab2 = 0);

	int compareTo(CommandQueueAction* action) {
		if (compareToCounter == action->compareToCounter) {
			if (this == action)
				return 0;
			else if (this < action)
				return 1;
			else
				return -1;
		} else if (compareToCounter < action->compareToCounter)
			return 1;
		else
			return -1;
	}

	inline void setCompareToCounter(int c) {
		compareToCounter = c;
	}

	inline int getCompareToCounter() {
		return compareToCounter;
	}

	inline CreatureObject* getCreature() {
		return creature;
	}

	inline uint32 getCommand() {
		return queueCommand;
	}

	inline uint64 getTarget() {
		return target;
	}

	inline uint32 getActionCounter() {
		return actionCounter;
	}

	inline UnicodeString getArguments() {
		return arguments;
	}

};

#endif /*COMMANDQUEUEACTION_H_*/
