/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUILDINGOBJECTMESSAGE3_H_
#define BUILDINGOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"
#include "../../objects/building/BuildingObject.h"
#include "../../objects/tangible/campkit/campsite/CampSite.h"

class BuildingObjectMessage3 : public BaseLineMessage {
public:
	BuildingObjectMessage3(BuildingObject *buio)
			: BaseLineMessage(buio->getObjectID(), 0x4255494F, 3, 0x0B) {
		insertFloat(1.0);
		insertAscii("building_name");
		insertInt(0); //nothing.
		insertAscii(buio->getDefaultName());
		insertUnicode(buio->getName()); // insertInt(0); //nothing. Custom Name
		insertInt(0xFF);
		insertShort(0);
		insertInt(0);
		insertInt(0);
		insertInt(0x00000100); // Some type of bitmask?
		insertInt(0);
		insertInt(0);
		//insertInt(1000); // unsure what this is, also seen 0x10E0
		insertInt(0x00001680); // unsure what this is, also seen 0x10E0
		insertByte(1);

		setSize();

		//StringBuffer msg;
		//msg << hex << "BuildingObjectMessage3 [Object = " << buio->getObjectID() << "]\n";
		//System::out << msg.toString();
	}

	/*BuildingObjectMessage3(CampSite *camp)
			: BaseLineMessage(camp->getObjectID(), 0x4255494F, 3, 0x0B) {
		insertFloat(1.0);
		insertAscii("camp");
		insertInt(0); //nothing.
		insertAscii("basic_camp");
		insertUnicode(camp->getName()); // insertInt(0); //nothing. Custom Name
		insertInt(0xFF);
		insertShort(0);
		insertInt(0);
		insertInt(0);
		insertInt(0x00000100); // Some type of bitmask?
		insertInt(0);
		insertInt(0);
		//insertInt(1000); // unsure what this is, also seen 0x10E0
		insertInt(0x00001680); // unsure what this is, also seen 0x10E0
		insertByte(1);

		setSize();

		//StringBuffer msg;
		//msg << hex << "BuildingObjectMessage3 [Object = " << buio->getObjectID() << "]\n";
		//System::out << msg.toString();*/
	}
};
#endif /*BUILDINGOBJECTMESSAGE3_H_*/
