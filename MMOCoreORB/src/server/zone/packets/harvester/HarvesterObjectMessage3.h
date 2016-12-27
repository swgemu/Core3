/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef HARVESTEROBJECTMESSAGE3_H_
#define HARVESTEROBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"

class HarvesterObjectMessage3 : public BaseLineMessage {
public:
	HarvesterObjectMessage3(HarvesterObject * hino)
			: BaseLineMessage(hino->getObjectID(), 0x48494E4F, 3, 0x05) {
		insertFloat(1.0);
		insertAscii("installation_n"); // STF File
		insertInt(0); //nothing.
		insertAscii(hino->getStfName()); // Key for Default Name
		insertUnicode(hino->getName()); // Object Name

		insertInt(1);

		String app;
		hino->getCustomizationString(app);
		insertAscii(app); // I think - seems to work - but no real options to update, //insertShort(0);

		insertInt(2);
		insertInt(0);

		insertInt(0); // was 0
		insertInt(0x01000000);  // 16777216 ? - bitmask?


		insertInt(0);
		insertInt(String::hashCode("rebel"));


		insertInt(hino->getConditionDamage());//insertInt(0x03E80000); // max condition ??
		insertInt(hino->getMaxCondition()); //insertInt(0x00010000); //refer to hardcode below. (trying to replace)

		insertByte(1); // 0222
		insertByte(1);

		insertInt(0);
		/*System::out << "Neutral: " << String::hashCode("neutral") << endl;
		System::out << "Rebel: " << String::hashCode("rebel") << endl;
		System::out << "Imp: " << String::hashCode("imperial") << endl;*/
		insertInt(0x000041C8);
		setSize();
/*
0x00, 0x00, 0x01, 0x00,
0x00,
0x00,
0x00, 0x00, 0x00, 0x00,

This could be short, int, int. I dont know.
*/

	}
};

#endif /*HARVESTEROBJECTMESSAGE3_H_*/
