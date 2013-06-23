/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef HARVESTEROBJECTMESSAGE3_H_
#define HARVESTEROBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

#include "../../objects/installation/harvester/HarvesterObject.h"

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
