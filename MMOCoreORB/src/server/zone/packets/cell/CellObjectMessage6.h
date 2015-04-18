/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CELLOBJECTMESSAGE6_H_
#define CELLOBJECTMESSAGE6_H_

#include "../BaseLineMessage.h"

class CellObjectMessage6 : public BaseLineMessage {
public:
	CellObjectMessage6(uint64 coId)
			: BaseLineMessage(coId, 0x53434C54, 6, 0x02) {

		//insertShort(1); //operand count
		//insertInt(0x42); // some const value it appears
		//insertInt(0x4A); //*shrug*
		insertInt(0x95);
		insertInt(0);
		insertInt(0);

		setSize();

		/*
		 *
		 *
Pre-CU:
05 00
0C 5F A7 68
26 88 AB 67 00 00 00 00
54 4C 43 53
06
01 00
42 00 00 00

		 * From Current Live:
// CellObjectMessage6
0000:    00 09 04 C8
05 00
0C 5F A7 68
93 D5 E3 09
23 00 00 00
54 4C 43 53 // CellObjectMessage
06 // 6
0E 00 00 00 // size - 14
02 00 // operand count
8C 00 00 00
00 00 00 00
00 00 00 00
*/
		//StringBuffer msg;
		//msg << hex << "CellObjectMessage6 [Object = " << coId << "]\n";
		//System::out << msg.toString();
	}
};
#endif /*CELLOBJECTMESSAGE6_H_*/
