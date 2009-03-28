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

#ifndef CREATUREOBJECTMESSAGE6_H_
#define CREATUREOBJECTMESSAGE6_H_

#include "../../packets/BaseLineMessage.h"

#include "../../objects/creature/CreatureObject.h"
#include "../tangible/TangibleObjectMessage6.h"

class CreatureObjectMessage6 : public TangibleObjectMessage6 {
public:
	CreatureObjectMessage6(CreatureObject* creo)
			: TangibleObjectMessage6(creo, 0x4352454F, 0x16) {

		insertShort((uint16)creo->getLevel());

		insertAscii(creo->getPerformanceAnimation());

		insertAscii(creo->getMoodStr());

		insertLong(creo->getWeaponID());

		insertLong(creo->getGroupID());

		insertLong(creo->getGroupInviterID());
		insertLong(creo->getGroupInviteCounter());

		insertInt(creo->getGuildID());
		//0x50, 0xC3, 0x00, 0x00,   // #08

		insertLong(creo->getTargetID());

		insertByte(creo->getMoodID());

		insertInt(creo->getPerformanceCounter()); //might be switched

		insertInt(creo->getInstrumentID()); //might be switched

		insertInt(9);
		insertInt(creo->getHAMUpdateCounter());
		insertInt(creo->getHealth());
		insertInt(creo->getStrength());
		insertInt(creo->getConstitution());
		insertInt(creo->getAction());
		insertInt(creo->getQuickness());
		insertInt(creo->getStamina());
		insertInt(creo->getMind());
		insertInt(creo->getFocus());
		insertInt(creo->getWillpower());

		insertInt(9);
		insertInt(creo->getHAMMaxUpdateCounter());
		insertInt(creo->getHealthMax());
		insertInt(creo->getStrengthMax());
		insertInt(creo->getConstitutionMax());
		insertInt(creo->getActionMax());
		insertInt(creo->getQuicknessMax());
		insertInt(creo->getStaminaMax());
		insertInt(creo->getMindMax());
		insertInt(creo->getFocusMax());
		insertInt(creo->getWillpowerMax());

		insertInt(0); //Equipment list
		insertInt(0); //Equipment update count
		/*
		insertShort(0); //Customization String
		insertInt(0x04); //Equipped
		insertLong(creo->getObjectID() + 1); //Inventory ID
		insertInt(0x2110791C); //CRC of Inventory


		insertShort(0); //Customization String
		insertInt(0x04); //Equipped
		insertLong(creo->getWeaponID()); //Weapon ID
		insertInt(0xC470AE12); //CRC of the weapon
	*/


		insertAscii(creo->getTemplateString());

		if (creo->isFrozen() == true) {
			insertByte(1);
		} else {
			insertByte(0);
		}


		setSize();
	}
};

#endif /*CREATUREOBJECTMESSAGE6_H_*/
