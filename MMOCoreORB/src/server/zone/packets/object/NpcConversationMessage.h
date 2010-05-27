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

#ifndef NPCCONVERSATIONMESSAGE_H_
#define NPCCONVERSATIONMESSAGE_H_

#include "ObjectControllerMessage.h"
#include "../../objects/creature/CreatureObject.h"
#include "../../objects/scene/variables/ParameterizedStringId.h"

class NpcConversationMessage : public ObjectControllerMessage {
public:

	NpcConversationMessage(CreatureObject* creo, UnicodeString& message)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		insertUnicode(message);
	}

	/*NpcConversationMessage(CreatureObject* creo, const String& file, const String& stringid)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		//insertUnicode(UnicodeString("@" + file + ":" + stringid));
		ParameterizedStringId params(file, stringid);
		params.addToPacketStream(this);

		insertInt(0);
	}*/
	NpcConversationMessage(CreatureObject* creo, const String& file, const String& str, uint64 TO = 0, uint64 TU = 0, uint64 TT = 0, int DI = 0, float DF = 0) :
		ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		int size = 0x56 + file.length() + str.length();
		bool odd = (size & 1);

		if (odd)
			insertInt((size + 1) / 2);
		else
			insertInt(size / 2);

		insertShort(0);
		insertShort(0);
		insertByte(1);
		insertInt(0xFFFFFFFF);

		insertAscii(file.toCharArray());
		insertInt(0);
		insertAscii(str.toCharArray());

		insertLong(TU); // %TU
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertInt(0);

		insertLong(TT); //%TT
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertInt(0);

		insertLong(TO); //%TO
		insertAscii("");
		insertInt(0);
		insertAscii("");
		insertInt(0);

		insertInt(DI); //%DI
		insertFloat(DF); //%DF
		insertByte(0);
		insertShort(0);

		if (odd)
			insertByte(0);

		insertInt(0);
	}

	NpcConversationMessage(CreatureObject* creo, ParameterizedStringId& stringid)
		: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xDF) {

		stringid.addToPacketStream(this);

		insertInt(0);
	}
};

#endif
