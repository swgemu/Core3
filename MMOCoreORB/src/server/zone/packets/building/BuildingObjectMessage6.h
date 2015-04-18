/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUILDINGOBJECTMESSAGE6_H_
#define BUILDINGOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

class BuildingObjectMessage6 : public BaseLineMessage {
public:
	BuildingObjectMessage6(BuildingObject *buio)
			: BaseLineMessage(buio->getObjectID(), 0x4255494F, 6, 0x02) {
		// BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt)
		//insertInt(0x4A);
		insertInt(0x42);

		insertInt(0); //Counter of uint64's
		insertInt(0); //Update count I assume.

		setSize();

		//StringBuffer msg;
		//msg << hex << "BuildingObjectMessage6 [Object = " << buio->getObjectID() << "]\n";
		//System::out << msg.toString();
	}

	/*BuildingObjectMessage6(CampSite *camp)
			: BaseLineMessage(camp->getObjectID(), 0x4255494F, 6, 0x02) {
		// BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt)
		//insertInt(0x4A);
		insertInt(0x42);

		insertInt(0); //Counter of uint64's
		insertInt(0); //Update count I assume.

		setSize();

		//StringBuffer msg;
		//msg << hex << "BuildingObjectMessage6 [Object = " << buio->getObjectID() << "]\n";
		//System::out << msg.toString();
	}*/
};
#endif /*BUILDINGOBJECTMESSAGE6_H_*/
