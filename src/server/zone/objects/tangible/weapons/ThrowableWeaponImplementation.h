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

#ifndef THROWABLEWEAPONIMPLEMENTATION_H_
#define THROWABLEWEAPONIMPLEMENTATION_H_

#include "ThrowableWeapon.h"

class ThrowableWeaponImplementation: public ThrowableWeaponServant {
protected:
	uint32 skill;
public:
	ThrowableWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn,const int tp, bool eqp = false);

	ThrowableWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, const int tp, bool eqp = false);

	void initialize();

	/*
	 * Uses a charge of the object. Ramoves the object if 0 charges left
	 * \param player The player.
	 */
	virtual void useCharge(Player* player) {

		decreaseUsesRemaining();
		updated = true;

		if (getUsesRemaining() == 0)
			remove(player);
	}

	/*
	 * Removes the camo kit from the inventory.
	 * \param player The player.
	 */
	void remove(Player* player);

	/*
	 * Uses the object.
	 * \param player The player using the object.
	 */
	int useObject(Player* player);

	/*
	 * Parses the items attributes.
	 */
	void parseItemAttributes();

	/*
	 * Sets the related skills name.
	 */
	void setSkill(const String& sk);

	/*
	 * Returns the related skills crc.
	 */
	int getSkillCRC();

	/*
	 * Sets the related skills crc.
	 */
	void setSkillCRC(const int sk);

	/*
	 * Checks if the object is usefull.
	 * \param player The player using the object.
	 */
	bool isUsefull(Player* player);

};

#endif /* THROWABLEWEAPONIMPLEMENTATION_H_ */
