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
		insertAscii(creo->getMoodString());
		insertLong(creo->getWeaponID());
		insertLong(creo->getGroupID());
		insertLong(creo->getGroupInviterID());
		insertLong(creo->getGroupInviteCounter());
		insertInt(creo->getGuildID());
		insertLong(creo->getTargetID());
		insertByte(creo->getMoodID());
		insertInt(creo->getPerformanceCounter()); //might be switched
		insertInt(creo->getInstrumentID()); //might be switched

		DeltaVector<int>* ham = creo->getHAM();
		ham->insertToMessage(this);

		DeltaVector<int>* maxHam = creo->getMaxHAM();
		maxHam->insertToMessage(this);

		insertEquipmentList(creo);

		insertAscii("");//insertAscii(creo->getTemplateString());

		insertByte(creo->getFrozen());

		setSize();
	}

	void insertEquipmentList(CreatureObject* creo) {
		/*VectorMap<String, ManagedReference<SceneObject*> >* equipmentList = creo->getSlottedObjects();

		SortedVector<ManagedReference<SceneObject*> > uniqueObjects;
		uniqueObjects.setNoDuplicateInsertPlan();

		for (int i = 0; i < equipmentList->size(); ++i) {
			SceneObject* object = equipmentList->get(i);

			String arrangement = equipmentList->elementAt(i).getKey();

			if (arrangement == "mission_bag" || arrangement == "ghost" || arrangement == "bank")
				continue;

			uniqueObjects.put(object);
		}

		int size = uniqueObjects.size();

		insertInt(size);
		insertInt(size);

		for (int i = 0; i < size; ++i) {
			SceneObject* object = uniqueObjects.get(i);

			String custString;

			if (object->isTangibleObject()) {
				cast<TangibleObject*>(object)->getCustomizationString(custString);
			}

			insertAscii(custString);
			insertInt(object->getContainmentType()); //Equipped
			insertLong(object->getObjectID()); //object id
			insertInt(object->getClientObjectCRC()); //CRC of the object
		}*/

		DeltaVector<ManagedReference<TangibleObject*> >* wearables = creo->getWearablesDeltaVector();
		wearables->insertToMessage(this);

	}
};

#endif /*CREATUREOBJECTMESSAGE6_H_*/
