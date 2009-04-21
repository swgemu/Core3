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

#ifndef MOUNTCREATUREIMPLEMENTATION_H_
#define MOUNTCREATUREIMPLEMENTATION_H_

class Player;
class CreatureObject;
class Creature;

#include "MountCreature.h"
#include "../../scene/ItemAttributes.h"
#include "../../../packets/scene/AttributeListMessage.h"

class MountCreatureImplementation : public MountCreatureServant {
	int mountType;

	CreatureObject* linkedCreature;

	bool instantMount;

	ManagedReference<IntangibleObject> datapadItem;

protected:
	//String attributeString;

	//ItemAttributes* itemAttributes;

public:

	const static int UNKNOWN = 0;
	const static int VEHICLE = 1;
	const static int PET = 2;

public:
	MountCreatureImplementation(CreatureObject* linkCreature, const String& name,
			const String& stf, uint32 itnocrc, uint32 objCRC, uint64 oid);
	MountCreatureImplementation(uint64 oid, uint32 tempcrc, const UnicodeString& n, const String& tempn);

	~MountCreatureImplementation();

	void init();

	void setLinkedCreature(CreatureObject* linkCreature);

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void parseItemAttributes();
	void generateAttributes(SceneObject* obj);
	void addAttributes(AttributeListMessage* alm);

	void call();
	void store(bool doLock = true);

	// setters and getters
	//inline void setAttributes(String& attributeString) {
	//	itemAttributes->setAttributes(attributeString);
	//}

	//inline String& getAttributes() {
	//	itemAttributes->getAttributeString(attributeString);
	//	return attributeString;
	//}

	inline void setObjectFileName(String& name) {
		objectFile = name;
		const String aName = "objectFileName";
		itemAttributes->setStringAttribute(aName, name);
	}

	void repair();

	inline void setMountType(int type) {
		mountType = type;
	}

	inline void setInstantMount(bool val) {
		instantMount = val;
	}

	inline void setDatapadItem(SceneObject* item) {
		if(item->isIntangible())
			datapadItem = (IntangibleObject*) item;
	}

	CreatureObject* getLinkedCreature() {
		return linkedCreature;
	}

	inline bool isDisabled() {
		return conditionDamage >= maxCondition;
	}

	void die();

	inline int getMountType() {
		return mountType;
	}

	inline bool isVehicle() {
		return mountType == VEHICLE;
	}

	inline bool isJetpack() {
		return objectCRC == 0x60250B32;
	}

	inline bool isPet() {
		return mountType == PET;
	}

	inline bool isInWorld() {
		return isInQuadTree();
	}

};

#endif /*MOUNTCREATUREIMPLEMENTATION_H_*/
