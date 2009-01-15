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

#ifndef INSTRUMENTIMPLEMENTATION_H_
#define INSTRUMENTIMPLEMENTATION_H_

#include "../../player/Player.h"

#include "Instrument.h"

class InstrumentImplementation : public InstrumentServant {
protected:
	int instrumentType;
public:

	// Redoing consts to match the Audio ID in TRE for instruments

	/* Redoing instrument consts to match the instrumentAudioId in TRE
	 * The actual packets for triggering sound is different & in creature
	 * implementation as well as the appropriate animation for each inst type
	1	traz
	2	slitherhorn
	3	fanfar
	4	flutedroopy
	5	kloohorn
	6	fizz
	7	bandfill
	8	omnibox
	9	nalargon
	10	mandoviol*/

	static const int TRAZ = 1;
	static const int SLITHERHORN = 2;
	static const int FANFAR = 3;
	static const int FLUTEDROOPY = 4;
	static const int KLOOHORN = 5;
	static const int FIZZ = 6;
	static const int BANDFILL = 7;
	static const int OMNIBOX = 8;
	static const int NALARGON = 9;
	static const int MANDOVIOL = 10;

public:
	InstrumentImplementation(Player* player, uint32 tempCRC, const UnicodeString& n, const String& tempn, int insttype)
			: InstrumentServant(player->getNewItemID(), INSTRUMENT) {
		objectCRC = tempCRC;

		instrumentType = insttype;

		String key = "instrumentType";
		itemAttributes->setIntAttribute(key, instrumentType);

		templateTypeName = "obj_n";
		templateName = tempn;

		customName = n;

	    setParent((TangibleObject*) player->getInventory(), 0xFFFFFFFF);
	}

	InstrumentImplementation(uint64 objectid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool equipd)
		: InstrumentServant(objectid, INSTRUMENT) {

		objectCRC = tempCRC;

		templateTypeName = "obj_n";
		templateName = tempn;

		customName = n;

		equipped = equipd;
	}

	void parseItemAttributes() {
		String key = "instrumentType";
		instrumentType = itemAttributes->getIntAttribute(key);
	}

	int useObject(Player* player) {
		return 0;
	}

	inline int getInstrumentType() {
		return instrumentType;
	}

	inline void setInstrumentType(const int type) {
		instrumentType = type;

		String key = "instrumentType";
		itemAttributes->setIntAttribute(key, instrumentType);
	}
};

#endif /*INSTRUMENTIMPLEMENTATION_H_*/

