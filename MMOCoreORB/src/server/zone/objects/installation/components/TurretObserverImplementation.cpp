/*
 * TurretObserverImplementation.cpp
 *
 *  Created on: Nov 20, 2012
 *      Author: root
 */
#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "server/zone/managers/gcw/tasks/DestroyFactionInstallationTask.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/components/TurretObserver.h"
#include "system/lang/ref/Reference.h"
#include "system/platform.h"
#include "templates/params/ObserverEventType.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
namespace util {
class Observable;
}  // namespace util
}  // namespace engine


int TurretObserverImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {

	if (eventType == ObserverEventType::OBJECTDESTRUCTION) {
		ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(observable);

		if (installation != NULL) {
			DestroyFactionInstallationTask* task = new DestroyFactionInstallationTask(installation);
			task->execute();
		}

		return 1;
	}

	return 0;
}






