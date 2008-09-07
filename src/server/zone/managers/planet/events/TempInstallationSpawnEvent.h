#ifndef TEMPINSTALLATIONSPAWNEVENT_H_
#define TEMPINSTALLATIONSPAWNEVENT_H_

#include "../../../objects/installation/InstallationObjectImplementation.h"

//class InstallationObject;
//class Zone;

class TempInstallationSpawnEvent : public Event {
	Player * player;
	InstallationObject* inso;

public:
	TempInstallationSpawnEvent(Player * play, InstallationObject * inInso) : Event() {

		player = play;
		inso = inInso;
		
		//setKeeping(true);
	}

	bool activate() {

		inso->insertToZone(player->getZone());

		return 1;
	}

};

#endif /*TEMPINSTALLATIONSPAWNEVENT_H_*/
#ifndef TEMPINSTALLATIONSPAWNEVENT_H_
#define TEMPINSTALLATIONSPAWNEVENT_H_

#include "../../../objects/installation/InstallationObjectImplementation.h"

//class InstallationObject;
//class Zone;

class TempInstallationSpawnEvent : public Event {
	Player * player;
	InstallationObject* inso;

public:
	TempInstallationSpawnEvent(Player * play, InstallationObject * inInso) : Event() {

		player = play;
		inso = inInso;
		
		//setKeeping(true);
	}

	bool activate() {

		inso->insertToZone(player->getZone());

		return 1;
	}

};

#endif /*TEMPINSTALLATIONSPAWNEVENT_H_*/
