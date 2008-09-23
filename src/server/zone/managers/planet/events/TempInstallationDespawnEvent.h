#ifndef TEMPINSTALLATIONDESPAWNEVENT_H_
#define TEMPINSTALLATIONDESPAWNEVENT_H_

#include "engine/engine.h"

//class InstallationObject;

class TempInstallationDespawnEvent : public Event {
	InstallationObject * inso;

public:
	TempInstallationDespawnEvent(InstallationObject * inInso) : Event() {
		
		inso = inInso;
		
		//setKeeping(true);
	}
	
	bool activate() {

		inso->removeFromZone();
		
		return 1;
	}

};

#endif /*TEMPINSTALLATIONDESPAWNEVENT_H_*/
#ifndef TEMPINSTALLATIONDESPAWNEVENT_H_
#define TEMPINSTALLATIONDESPAWNEVENT_H_

#include "engine/engine.h"

//class InstallationObject;

class TempInstallationDespawnEvent : public Event {
	InstallationObject * inso;

public:
	TempInstallationDespawnEvent(InstallationObject * inInso) : Event() {
		
		inso = inInso;
		
		//setKeeping(true);
	}
	
	bool activate() {

		inso->removeFromZone();
		
		return 1;
	}

};

#endif /*TEMPINSTALLATIONDESPAWNEVENT_H_*/
