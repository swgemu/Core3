/*
 * InstallationSyncUIEvent.h
 *
 *  Created on: Oct 16, 2008
 *      Author: swgemu
 */

#ifndef INSTALLATIONSYNCUIEVENT_H_
#define INSTALLATIONSYNCUIEVENT_H_

#include "../InstallationObjectImplementation.h"

class InstallationObjectImplementation;

class InstallationSyncUIEvent : public Event {
	InstallationObjectImplementation *inso;

public:
	InstallationSyncUIEvent(InstallationObjectImplementation * inInso) : Event() {
		inso = inInso;

		setKeeping(true);
	}

	bool activate() {

		try {
			inso->wlock();

			inso->updateHopper();
			inso->updateOperators();

			if(inso->getOperatorListSize() > 0)
				inso->activateSync(); // renew

			inso->unlock();

		} catch (...) {
			cout << "exception InstallationSyncUIEvent" << endl;
			inso->unlock();
		}
		return true;
	}

};


#endif /* INSTALLATIONSYNCUIEVENT_H_ */
