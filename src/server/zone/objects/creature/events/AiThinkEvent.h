/*
 * AiThinkEvent.h
 *
 *  Created on: 23/06/2010
 *      Author: victor
 */

#ifndef AiThinkEvent_H_
#define AiThinkEvent_H_


#include "../AiAgent.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace events {

class AiThinkEvent : public Task {
	ManagedWeakReference<AiAgent*> creature;

public:
	AiThinkEvent(AiAgent* pl) : Task(1000) {
		creature = pl;
	}

	~AiThinkEvent() {
	}

	void run() {
		ManagedReference<AiAgent*> strongRef = creature.get();

		if (strongRef == NULL)
			return;

		Locker locker(strongRef);
		strongRef->doRecovery();
	}

};

}
}
}
}
}

using namespace server::zone::objects::creature::events;


#endif /* AiThinkEvent_H_ */
