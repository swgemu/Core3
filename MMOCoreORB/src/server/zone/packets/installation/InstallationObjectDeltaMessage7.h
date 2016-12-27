/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONOBJECTDELTAMESSAGE7_H_
#define INSTALLATIONOBJECTDELTAMESSAGE7_H_

#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/installation/InstallationObject.h"

class InstallationObjectDeltaMessage7 : public DeltaMessage {
	InstallationObject* inso;

public:
	InstallationObjectDeltaMessage7(InstallationObject* ins)
			: DeltaMessage(ins->getObjectID(), 0x494E534F, 7) {
		inso = ins;
	}

	void updateExtractionRate(float rate) {
		addFloatUpdate(0x09, rate);
	}

	void setNoHopperUpdate() {
		addByteUpdate(0x0C, 0);
	}

	void updateOperating(bool state) {
		addByteUpdate(0x06, state);
	}

	void updateHopper() {
		addByteUpdate(0x0C, 1); // think about incrementing like a counter
	}

	void updateHopperSize(float size) {
		addFloatUpdate(0x0A, size);
	}

	void updateActiveResourceSpawn(uint64 id) {
		addLongUpdate(0x05, id);
	}

	/*void updateActiveResource(uint64 oid) {

		if (inso->getObjectSubType() == TangibleObjectImplementation::HARVESTER && ((HarvesterObject*)inso)->getActiveResourceID() != oid)
			((HarvesterObject*)inso)->changeActiveResourceID(oid);

		// Active Resource
		addLongUpdate(0x05, oid);
		//System::out << "Adding 0x05 update for oid: " << hex << oid << endl;

	}



	void updateHopperItem(uint64 rId) {

		startUpdate(0x0D); // hopper
		insertInt(1); // list size
		insertInt(inso->getNewHopperUpdateCounter(1));
		insertByte(0x02); // change
		insertShort(0x00);
		insertLong(rId); // ID
		insertFloat(inso->getHopperItemQuantity(rId)); // size
	}

	void addHopperItem(uint64 rId) {
		startUpdate(0x0D); // hopper
		insertInt(1); // list size
		insertInt(inso->getNewHopperUpdateCounter(1));
		insertByte(0x01); // add
		insertShort(0x00);
		insertLong(rId); // ID
		insertFloat(inso->getHopperItemQuantity(rId)); // size
	}*/

};

#endif /* INSTALLATIONOBJECTDELTAMESSAGE7_H_ */
