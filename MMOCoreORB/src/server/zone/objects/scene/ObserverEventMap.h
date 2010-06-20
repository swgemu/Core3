/*
 * ObserverEventMap.h
 *
 *  Created on: 20/06/2010
 *      Author: victor
 */

#ifndef OBSERVEREVENTMAP_H_
#define OBSERVEREVENTMAP_H_

namespace server {
 namespace zone {
  namespace objects {
	namespace scene {
	 class Observable;
	 class Observer;
	}
  }
 }
}

using namespace server::zone::objects::scene;

#include "engine/engine.h"

class ObserverEventMap : public VectorMap<uint32, SortedVector<ManagedReference<Observer*> > > {
public:
	ObserverEventMap() {
		setNoDuplicateInsertPlan();
	}

	void notifyObservers(uint32 eventType, Observable* observable, ManagedObject* arg1 = NULL, int64 arg2 = 0);

	void registerObserver(uint32 eventType, Observer* observer);

	void dropObserver(uint32 eventType, Observer* observer);

	SortedVector<ManagedReference<Observer*> >* getObservers(uint32 eventType);
};


#endif /* OBSERVEREVENTMAP_H_ */
