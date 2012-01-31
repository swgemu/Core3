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

#ifndef CREATUREOBJECTDELTAMESSAGE4_H_
#define CREATUREOBJECTDELTAMESSAGE4_H_

#include "../../packets/DeltaMessage.h"

class CreatureObjectDeltaMessage4 : public DeltaMessage {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage4(CreatureObject* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 4) {
		creo = cr;
	}

	void updateAccelerationMultiplierBase() {
		addFloatUpdate(0x00, creo->getAccelerationMultiplierBase());
	}

	void updateAccelerationMultiplierMod() {
		addFloatUpdate(0x01, creo->getAccelerationMultiplierMod());
	}

	void updateSpeedMultiplierBase() {
		addFloatUpdate(0x04, creo->getSpeedMultiplierBase());
	}

	void updateSpeedMultiplierMod() {
		addFloatUpdate(0x05, creo->getSpeedMultiplierMod());
	}

	void updateRunSpeed() {
		addFloatUpdate(0x07, creo->getRunSpeed());
	}

	void updateEntertainerValue(uint32 value) {
		startUpdate(0x09);
		insertInt(value);
	}

	void updateListenToID(uint64 objectid) {
		startUpdate(0x06);
		insertLong(objectid);
	}

	void updateTurnScale() {
		addFloatUpdate(0x08, creo->getTurnScale());
	}

	void updateTerrainNegotiation() {
		addFloatUpdate(0x09, creo->getTerrainNegotiation());
	}

	/*void updateAcceleration() {
		addFloatUpdate(0x0B, creo->acceleration);
	}



	void startSkillModsUpdate(int skillModsToUpdate) {
		startUpdate(0x03);
		startList(skillModsToUpdate, creo->skillModsCounter += skillModsToUpdate);
	}

	void addSkillMod(const String& skillMod, int value) {
		insertByte(0);
		insertAscii(skillMod.toCharArray());
		insertInt(value);
		insertInt(0);
	}

	void removeSkillMod(const String& skillMod, int value) {
		insertByte(1);
		insertAscii(skillMod.toCharArray());
		insertInt(value);
		insertInt(0);
	}

	*/

};

#endif /*CREATUREOBJECTDELTAMESSAGE4_H_*/
