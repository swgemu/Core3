#include "server/zone/objects/creature/CreatureObject.h"

#include "RecordTrackTimeoutEvent.h"

RecordTrackTimeoutEvent::RecordTrackTimeoutEvent(DroidPlaybackModuleDataComponent* m, CreatureObject* p, int type) {
	module = m;
	player = p;
	recordingState = type;
}

void RecordTrackTimeoutEvent::run() {
	if (module == nullptr)
		return;

	Locker plock(player);
	module->sessionTimeout(player, recordingState);
}