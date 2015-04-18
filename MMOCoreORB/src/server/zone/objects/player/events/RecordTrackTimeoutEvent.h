/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef RECORDTRACKTIMEOUTEVENT_H
#define RECORDTRACKTIMEOUTEVENT_H

#include "engine/engine.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
namespace server {
namespace zone {
namespace objects {
namespace player {
namespace events {

class RecordTrackTimeoutEvent: public Task {
	ManagedReference<DroidPlaybackModuleDataComponent*> module;
	ManagedReference<CreatureObject*> player;
	int recordingState;
public:
	RecordTrackTimeoutEvent(DroidPlaybackModuleDataComponent* m,CreatureObject* p, int type) {
		module = m;
		player = p;
		recordingState = type;
	}

	void run() {
		if (module == NULL)
			return;
		Locker plock(player);
		module->sessionTimeout(player,recordingState);
	}

};

}
}
}
}
}

#endif /* RECORDTRACKTIMEOUTEVENT_H */
