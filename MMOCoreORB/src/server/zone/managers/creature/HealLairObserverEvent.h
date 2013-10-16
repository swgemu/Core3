/*
 * HealLairObserverEvent.h
 *
 *  Created on: 10/12/2011
 *      Author: victor
 */

#ifndef HEALLAIROBSERVEREVENT_H_
#define HEALLAIROBSERVEREVENT_H_

#include "server/zone/managers/creature/LairObserver.h"
#include "server/zone/objects/tangible/TangibleObject.h"

namespace server {
 namespace zone {
  namespace managers {
   namespace creature {

   class HealLairObserverEvent : public Task {
	   ManagedWeakReference<TangibleObject*> lair;
	   ManagedWeakReference<TangibleObject*> attacker;
	   ManagedWeakReference<LairObserver*> observer;

   public:
	   HealLairObserverEvent(TangibleObject* obj, TangibleObject* attacker, LairObserver* observer) {
		   lair = obj;
		   this->attacker = attacker;
		   this->observer = observer;
	   }

	   void run() {
		   ManagedReference<TangibleObject*> strongRef = lair.get();

		   if (strongRef == NULL)
			   return;

		   ManagedReference<TangibleObject*> strongAttackerRef = attacker.get();
		   ManagedReference<LairObserver*> strongObserver = observer.get();

		   if (strongObserver == NULL)
			   return;

		   Locker locker(strongRef);

		  // Locker clocker(attacker, lair);

		   strongObserver->healLair(strongRef, strongAttackerRef);

		   if (strongRef->getConditionDamage() > 0)
			   strongObserver->checkForHeal(strongRef, strongAttackerRef, true);
	   }

	   void setAttacker(TangibleObject* obj) {
		   attacker = obj;
	   }

   };

   }
  }
 }
}

using namespace server::zone::managers::creature;



#endif /* HEALLAIROBSERVEREVENT_H_ */
