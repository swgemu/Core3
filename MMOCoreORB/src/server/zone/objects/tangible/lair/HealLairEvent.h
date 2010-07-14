/*
 * HealLairEvent.h
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#ifndef HEALLAIREVENT_H_
#define HEALLAIREVENT_H_

#include "engine/engine.h"

#include "LairObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace tangible {
    namespace lair {

    class HealLairEvent : public Task {
    	ManagedWeakReference<LairObject*> lair;
    	ManagedWeakReference<TangibleObject*> attacker;

    public:
    	HealLairEvent(LairObject* obj, TangibleObject* attacker) {
    		lair = obj;
    		this->attacker = attacker;
    	}

    	void run() {
    		ManagedReference<LairObject*> strongRef = lair.get();

    		if (strongRef == NULL)
    			return;

    		ManagedReference<TangibleObject*> strongAttackerRef = attacker.get();

    		Locker locker(lair);

    		lair->healLair(attacker);

    		if (lair->getConditionDamage() > 0)
    			lair->checkForHeal(strongAttackerRef, true);
    	}

    	void setAttacker(TangibleObject* obj) {
    		attacker = obj;
    	}

    };

    }
   }
  }
 }
}

using namespace server::zone::objects::tangible::lair;

#endif /* HEALLAIREVENT_H_ */
