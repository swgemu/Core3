

#ifndef SPAWNRESOURCESEVENT_H_
#define SPAWNRESOURCESEVENT_H_

#include "../ResourceManagerImplementation.h"

class ResourceManagerImplementation;

class SpawnResourcesEvent : public Event {
	ResourceManagerImplementation* resources;

public:
	SpawnResourcesEvent(ResourceManagerImplementation* resmgr) : Event() {
		resources = resmgr;
		
		setKeeping(true);
	}

	bool activate() {
		resources->theShift();
		
		return true;
	}

};

#endif /*SPAWNRESOURCESEVENT_H_*/
