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
	Reference<DroidPlaybackModuleDataComponent*> module;
	Reference<CreatureObject*> player;
	int recordingState;
public:
	RecordTrackTimeoutEvent(DroidPlaybackModuleDataComponent* m, CreatureObject* p, int type);

	void run();

};

}
}
}
}
}
using namespace server::zone::objects::player::events;

#endif /* RECORDTRACKTIMEOUTEVENT_H */
