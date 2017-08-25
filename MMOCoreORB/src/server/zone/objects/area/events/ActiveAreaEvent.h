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
	   }

	   void run() {
		   ManagedReference<ActiveArea*> area = activeArea.get();
		   ManagedReference<SceneObject*> object = sceneObject.get();

		   if (area == NULL || object == NULL)
			   return;

		   Locker clocker(object);

		   Locker locker(area, object);

		   switch (eventType) {
		   case ENTEREVENT:
			   area->notifyEnter(object);
			   break;

		   case EXITEVENT:
			   area->notifyExit(object);
			   break;

		   default:
			   break;
		   }
	   }

   };
    }
   }
  }
 }
}

using namespace server::zone::objects::area::events;

#endif /* ACTIVEAREAEVENT_H_ */
