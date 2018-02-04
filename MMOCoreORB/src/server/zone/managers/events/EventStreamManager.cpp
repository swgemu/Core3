//
// Created by theanswer on 2/4/18.
//

#include "EventStreamManager.h"

EventStreamManager::EventStreamManager() : fileStream("EventStreamManager") {
	fileStream.setLogTimeToFile(false);
	fileStream.setLogLevelToFile(false);

	fileStream.setFileLogger("log/eventstream.log", true);
}

void EventStreamManager::pushEvent(StreamEvent& event) {
	fileStream.log(event.getGraphData().dump().c_str());
}
