/*
 * ObserverEventType.cpp
 *
 *  Created on: 20/06/2010
 *      Author: victor
 */

#include "ObserverEventMap.h"
#include "Observer.h"

void ObserverEventMap::notifyObservers(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	int index = find(eventType);

	if (index == -1) {
		return;
	}

	SortedVector<ManagedReference<Observer*> >* observers = &elementAt(index).getValue();

	for (int i = 0; i < observers->size(); ++i) {
		ManagedReference<Observer*> observer = observers->get(i);

		int result = observer->notifyObserverEvent(eventType, observable, arg1, arg2);

		if (result == 1) {
			if (observers->drop(observer))
				--i;
		}

	}
}

void ObserverEventMap::registerObserver(uint32 eventType, Observer* observer) {
	int index = find(eventType);

	if (index == -1) {
		SortedVector<ManagedReference<Observer*> > observers;
		observers.put(observer);

		this->put(eventType, observers);
	} else {
		SortedVector<ManagedReference<Observer*> >* observers = &elementAt(index).getValue();
		observers->setNoDuplicateInsertPlan();

		observers->put(observer);
	}
}

void ObserverEventMap::dropObserver(uint32 eventType, Observer* observer) {
	int index = find(eventType);

	if (index == -1)
		return;

	SortedVector<ManagedReference<Observer*> >* observers = &elementAt(index).getValue();

	observers->drop(observer);

	if (observers->size() == 0)
		this->remove(index);
}

SortedVector<ManagedReference<Observer*> >* ObserverEventMap::getObservers(uint32 eventType) {
	int index = find(eventType);

	if (index == -1)
		return NULL;

	SortedVector<ManagedReference<Observer*> >* observers = &elementAt(index).getValue();

	return observers;
}

int ObserverEventMap::getObserverCount(uint32 eventType) {
	int index = find(eventType);

	if (index == -1)
		return 0;

	SortedVector<ManagedReference<Observer*> >* observers = &elementAt(index).getValue();

	return observers->size();
}
