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
