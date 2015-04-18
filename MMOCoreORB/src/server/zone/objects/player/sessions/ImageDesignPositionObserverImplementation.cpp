/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/player/sessions/ImageDesignPositionObserver.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"

int ImageDesignPositionObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<ImageDesignSession*> strongRef = session.get();

	if (strongRef == NULL)
		return 1;

	if (eventType != ObserverEventType::POSITIONCHANGED)
		return 1;

	SceneObject* scene = dynamic_cast<SceneObject*>(observable);

	if (scene == NULL)
		return 1;

	ManagedReference<ImageDesignSession*> strong = session.get();

	if (scene->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL) {
		//queue the timeout
		strong->queueIdTimeoutEvent();
	} else {
		//cancel the timeout
		strong->checkDequeueEvent(scene);
	}

	return 0;
}
