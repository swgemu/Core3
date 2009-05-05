/*
 * FactoryCreateItemEvent.h
 *
 *  Created on: Feb 12, 2008
 *      Author: swgemu
 */

#ifndef FACTORYCREATEITEMEVENT_H_
#define FACTORYCREATEITEMEVENT_H_

#include "../factory/FactoryObjectImplementation.h"

class FactoryObjectImplementation;

class FactoryCreateItemEvent : public Event {
	FactoryObjectImplementation* fact;

public:
	FactoryCreateItemEvent(FactoryObjectImplementation * inFact) : Event() {
		fact = inFact;

		setKeeping(true);
	}

	bool activate() {

		try {
			fact->wlock();

			fact->createItem();
			fact->updateOperators();
			fact->updateMaintenance();

			fact->scheduleItemCreation();

			fact->unlock();

		} catch (...) {
			System::out << "exception in FactoryCreateItemEvent\n";
			fact->unlock();
		}
		return true;
	}

};


#endif /* FACTORYCREATEITEMEVENT_H_ */
