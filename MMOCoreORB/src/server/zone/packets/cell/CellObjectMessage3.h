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

#ifndef CELLOBJECTMESSAGE3_H_
#define CELLOBJECTMESSAGE3_H_

#include "../BaseLineMessage.h"

class CellObjectMessage3 : public BaseLineMessage {
public:
	CellObjectMessage3(uint64 coId, int cellNumber)
			: BaseLineMessage(coId, 0x53434C54, 3, 0x05) {
		//BaseLineMessage(uint64 oid, uint32 name, uint8 type, uint16 opcnt) {
		insertInt(0);
		insertShort(0); // STFName
		insertInt(0);
		insertShort(0); // STF
		insertInt(0); // custom name
		insertInt(0);
		insertInt(cellNumber); //Cell Number, like 1,2,3,4 etc. NOT Object id.

		setSize();

		/*
		 * From Current Live:
		// CellObjectMessage3
		0000:    00 09 04 C8
		05 00
		0C 5F A7 68 // Baseline Message
		93 D5 E3 09 23 00 00 00 // Cell 1 Object ID
		54 4C 43 53 //  CellObjectMessage
		03 // 3
		1B 00 00 00
		06 00
		00 00 00 00
		00 00  // STFName
		00 00 00 00  // something
		00 00 // stf
		00 00 00 00 // UnicodeString custom name
		00 00 00 00 //something
		01 // extra bit on live?
		01 00 00 00 // Cell Number
		*/

		//StringBuffer msg;
		//msg << hex << "CellObjectMessage3 [Object = " << coId << "]" << " cellID to (" << cellID <<  ")\n";
		//System::out << msg.toString();

	}
};
#endif /*CELLOBJECTMESSAGE3_H_*/
