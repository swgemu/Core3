/*
 * ActiveAreaEvent.h
 *
 *  Created on: 23/07/2010
 *      Author: victor
 */

#ifndef ACTIVEAREAEVENT_H_
#define ACTIVEAREAEVENT_H_

#include "engine/engine.h"

/**
 * this event gets enqueued on notifyEnter/notifyExit so we dont mess QuadTree in ::notifyPosUpdate
 */

#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/Zone.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace area {

   namespace events {

   class ActiveAreaEvent : public Task {
	   uint32 eventType;

	   ManagedWeakReference<ActiveArea*> activeArea;
	   ManagedWeakReference<SceneObject*> sceneObject;

   public:
	   const static int ENTEREVENT = 1;
	   const static int EXITEVENT = 2;

   public:
	   ActiveAreaEvent(ActiveArea* ar, SceneObject* obj, uint32 eventt) {
		   activeArea = ar;
		   eventType = eventt;
		   sceneObject = obj;

		   if (!obj) {
		   	return;
		   }

		   const auto zone = obj->getZone();

		   if (zone) {
		   	setCustomTaskQueue(zone->getZoneName());
		   }
	   }

	   void run();

   };
    }
   }
  }
 }
}

using namespace server::zone::objects::area::events;

#endif /* ACTIVEAREAEVENT_H_ */
