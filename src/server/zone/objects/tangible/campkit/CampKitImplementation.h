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

#ifndef CAMPKITIMPLEMENTATION_H_
#define CAMPKITIMPLEMENTATION_H_

#include "CampKit.h"
#include "../../player/Player.h"
#include "../../area/ActiveAreaTrigger.h"

class CampKitImplementation: public CampKitServant {
protected:
	uint16 usesRemaining;
	uint16 exp;
	uint16 duration;

	uint16 campType;

public:

	CampKitImplementation(unsigned long long oid, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	CampKitImplementation(Player* player, unsigned int tempCRC, const UnicodeString& n, const String& tempn);

	void updateCraftingValues(DraftSchematic* draftSchematic);

	int useObject(Player* player);

	bool isUsefull(Player* player);
	bool canNotUse(Player* player);
	/*
	 * Returns the camps max xp.
	 * \return The xp.
	 */
	int getXP() {
		return exp;
	}

	/*
	 * Sets the camps max xp.
	 * \param xp The max xp.
	 */
	void setXP(const int xp) {
		exp = xp;
		String attr = "exp";
		itemAttributes->setIntAttribute(attr, exp);
	}
	/*
	 * Returns the camps duration.
	 * \return The durarion.
	 */
	int getDuration() {
		return duration;
	}
	/*
	 * Sets the camps duration.
	 * \param dur The duration.
	 */
	void setDuration(const int dur) {
		duration = dur;
		String attr = "duration";
		itemAttributes->setIntAttribute(attr, duration);
	}

	/*
	 * Returns the camps crc.
	 * \return The camps crc.
	 */
	int getCampType() {
		return campType;
	}

	/*
	 * Sets the camps crc.
	 * \return Returns the camps crc.
	 */
	void setCampType(const int type) {
		campType = type;
		String attr = "campType";
		itemAttributes->setIntAttribute(attr, campType);
	}

	void remove(Player* player);

	void generateAttributes(SceneObject* obj);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);
	void addAttributes(AttributeListMessage* alm);

	void parseItemAttributes();
};

#endif /* CAMOKITIMPLEMENTATION2_H_ */
