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

namespace server {
 namespace zone {
  namespace objects {
   namespace area {

   namespace events {

   class ActiveAreaEvent : public Task {
	   uint32 eventType;

	   ManagedReference<ActiveArea*> area;
	   ManagedReference<SceneObject*> object;

   public:
	   const static int ENTEREVENT = 1;
	   const static int EXITEVENT = 2;

   public:
	   ActiveAreaEvent(ActiveArea* ar, SceneObject* obj, uint32 eventt) {
		   area = ar;
		   eventType = eventt;
		   object = obj;
	   }

	   void run() {
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
