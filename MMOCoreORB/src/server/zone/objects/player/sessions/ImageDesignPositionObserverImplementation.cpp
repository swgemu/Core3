/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "engine/util/Observable.h"
#include "server/zone/objects/player/sessions/ImageDesignPositionObserver.h"
#include "server/zone/objects/player/sessions/ImageDesignSession.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "templates/params/ObserverEventType.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
}  // namespace engine

int ImageDesignPositionObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	ManagedReference<ImageDesignSession*> strongRef = session.get();

	if (strongRef == NULL)
		return 1;

	if (eventType != ObserverEventType::POSITIONCHANGED)
		return 0;

	SceneObject* scene = dynamic_cast<SceneObject*>(observable);

	if (scene == NULL)
		return 1;

	if (scene->getParentRecursively(SceneObjectType::SALONBUILDING) == NULL) {
		//queue the timeout
		strongRef->queueIdTimeoutEvent();
	} else {
		//cancel the timeout
		strongRef->checkDequeueEvent(scene);
	}

	return 0;
}
