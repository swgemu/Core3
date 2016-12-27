/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTDELTAMESSAGE6_H_
#define INSTALLATIONOBJECTDELTAMESSAGE6_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/installation/InstallationObject.h"

class InstallationObjectDeltaMessage6 : public DeltaMessage {
	InstallationObject* inso;

public:
	InstallationObjectDeltaMessage6(InstallationObject* ins)
			: DeltaMessage(ins->getObjectID(), 0x494E534F, 6) {
		inso = ins;
	}


	void startDefenderUpdate(int updates) {
		startUpdate(0x01);

		uint32 counter = inso->getNewDefenderUpdateCounter(updates);
		startList(updates, counter);
	}

	void addDefender(uint16 index, uint64 defenderID) {
		insertByte(1);
		insertShort(index);
		insertLong(defenderID);
	}

	void setDefender(uint16 idx, uint64 defenderID) {
		insertByte(2);
		insertShort(idx);
		insertLong(defenderID);
	}

	void removeDefender(uint16 index) {
		insertByte(0);
		insertShort(index);
	}

	void removeDefenders() {
		insertByte(4);
	}

};

#endif /* INSTALLATIONOBJECTDELTAMESSAGE6_H_ */
