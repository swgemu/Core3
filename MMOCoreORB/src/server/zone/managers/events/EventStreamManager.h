//
// Created by theanswer on 2/4/18.
//

#ifndef CORE3_EVENTSTREAMMANAGER_H
#define CORE3_EVENTSTREAMMANAGER_H

#include "engine/engine.h"
#include "server/zone/objects/events/StreamEvent.h"

class EventStreamManager : public Singleton<EventStreamManager>, public Object {
protected:
	Logger fileStream;
public:
	EventStreamManager();

	void pushEvent(StreamEvent& event);
};

#endif //CORE3_EVENTSTREAMMANAGER_H
