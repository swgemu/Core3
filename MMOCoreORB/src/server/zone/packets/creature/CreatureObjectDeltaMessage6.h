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

#ifndef CREATUREOBJECTDELTAMESSAGE6_H_
#define CREATUREOBJECTDELTAMESSAGE6_H_

#include "../tangible/TangibleObjectDeltaMessage6.h"

#include "../../objects/creature/CreatureObject.h"

#include "../../objects/creature/CreatureAttribute.h"

class CreatureObjectDeltaMessage6 : public TangibleObjectDeltaMessage6 {
	CreatureObject* creo;

public:
	CreatureObjectDeltaMessage6(CreatureObject* cr)
		: TangibleObjectDeltaMessage6(cr, 0x4352454F) {
		creo = cr;
	}

	void updateWeapon() {
		addLongUpdate(0x05, creo->getWeaponID());
	}

	void updateTarget() {
		addLongUpdate(0x09, creo->getTargetID());
	}

	void updateInviterId() {
		startUpdate(0x07);

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getGroupInviteCounter());
	}

	void updateGroupID() {
		addLongUpdate(0x06, creo->getGroupID());
	}

	void updateGuildID() {
		addIntUpdate(0x08, creo->getGuildID());
	}

	void updateMoodID() {
		addByteUpdate(0x0A, creo->getMoodID());
	}

	void updateMoodStr() {
		addAsciiUpdate(0x04, creo->getMoodString());
	}

	void updateInstrumentID(int value) {
		startUpdate(0x0C);
		insertInt(value);
	}

	void updatePerformanceCounter(uint32 pCounter) {
		startUpdate(0x0B);
		insertInt(pCounter);
	}

	void updatePerformanceAnimation(const String& pAnimation) {
		startUpdate(0x03);
		insertAscii(pAnimation);
	}

	void updateLevel(uint16 value) {
		startUpdate(0x02);
		insertShort(value);
	}

	/*

	void updateInviterId() {
		startUpdate(0x07);

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getNewGroupInviteCounter());
	}






	void updateInstrumentID(int value) {
		startUpdate(0x0C);
		insertInt(value);
	}

	void updateMoodAnimation(String value) {
		startUpdate(0x04);
		insertAscii(value);
	}

	void updateTemplateString() {
		startUpdate(0x10);
		insertAscii(creo->getTemplateString());
	}

	void setFrozen(bool frozen) {
		startUpdate(0x11);
		if (frozen) {
			insertByte(0x01);
		} else {
			insertByte(0);
		}
	}
	}*/
};

#endif /*CREATUREOBJECTDELTAMESSAGE6_H_*/
