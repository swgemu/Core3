#ifndef TEMPINSTALLATIONSPAWNEVENT_H_
#define TEMPINSTALLATIONSPAWNEVENT_H_

#include "../../../objects/installation/InstallationObjectImplementation.h"

//class InstallationObject;
//class Zone;

class TempInstallationSpawnEvent : public Event {
	//Player* player;
	InstallationObject* inso;
	Zone* zone;

public:
	TempInstallationSpawnEvent(InstallationObject * inInso, Zone* z) : Event() {

		//player = play;
		inso = inInso;
		zone = z;

		setKeeping(false);
	}

	bool activate() {
		//try {
		//	cout << "TempInstallationSpawnEvent Start" << endl;
		//	player->wlock();

			inso->insertToZone(zone);

			cout << "TempInstallationSpawnEvent complete" << endl;
		//	player->unlock();
		//} catch (...) {
		//	player->unlock();
		//}
		return true;
	}

};

#endif /*TEMPINSTALLATIONSPAWNEVENT_H_*/
