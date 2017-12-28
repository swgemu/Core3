/*
 * InstrumentObserverImplementation.cpp
 *
 *  Created on: 31/10/2010
 *      Author: victor
 */

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/InstrumentObserver.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "templates/params/ObserverEventType.h"

namespace engine {
namespace core {
class ManagedObject;
}  // namespace core
namespace util {
class Observable;
}  // namespace util
}  // namespace engine

int InstrumentObserverImplementation::notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType != ObserverEventType::POSITIONCHANGED && eventType != ObserverEventType::OBJECTREMOVEDFROMZONE) {
		return 0;
	}

	SceneObject* creature = cast<SceneObject*>(observable);

	if (creature == NULL) {
		return 0;
	}

	ManagedReference<Instrument* > instrument = this->instrument.get();

	if (instrument == NULL || instrument->getZone() == NULL) {
		if (eventType == ObserverEventType::OBJECTREMOVEDFROMZONE) {
			creature->dropObserver(ObserverEventType::POSITIONCHANGED, _this.getReferenceUnsafeStaticCast());
		} else if (eventType == ObserverEventType::POSITIONCHANGED) {
			creature->dropObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, _this.getReferenceUnsafeStaticCast());
		}

		return 1;
	} else {
		Locker locker(instrument);

		if (eventType == ObserverEventType::POSITIONCHANGED) {
			if (creature->getDistanceTo(instrument) > 8) {
				instrument->destroyObjectFromWorld(true);

				creature->dropObserver(ObserverEventType::OBJECTREMOVEDFROMZONE, _this.getReferenceUnsafeStaticCast());

				return 1;
			}
		} else if (eventType == ObserverEventType::OBJECTREMOVEDFROMZONE) {
			instrument->destroyObjectFromWorld(true);

			creature->dropObserver(ObserverEventType::POSITIONCHANGED, _this.getReferenceUnsafeStaticCast());

			return 1;
		}
	}

	return 0;
}
