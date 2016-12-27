/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CELLOBJECTMESSAGE3_H_
#define CELLOBJECTMESSAGE3_H_

#include "server/zone/packets/BaseLineMessage.h"

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
