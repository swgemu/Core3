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

#include "Inventory.h"
#include "InventoryImplementation.h"
#include "../../managers/item/ItemManager.h"

#include "../creature/CreatureObject.h"

#include "../../packets.h"

InventoryImplementation::InventoryImplementation(CreatureObject* creature) :
	InventoryServant(creature->getObjectID() + 0x01) {

	objectType = INVENTORYOBJECT;

	customName = UnicodeString("");

	stfFile = "item_n";
	stfName = "inventory";

	parent = (SceneObject*) creature;
}

InventoryImplementation::~InventoryImplementation() {
	setParent(NULL);
}

TangibleObject* InventoryImplementation::getItemByMisoKey(String& misKey) {
	TangibleObject* retTano = NULL;
	TangibleObject* tano = NULL;

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		SceneObject* obj = getObject(i);

		if (obj->isTangible()) {
			tano = (TangibleObject*)obj;

			if ((tano->getMisoAsocKey() == misKey) && !tano->isEquipped()) {
				break;
			} else {
				tano = NULL;
			}
		}
	}

	if (tano != NULL) {
		retTano = tano;
	}

	return retTano;
}

void InventoryImplementation::removeAllByMisoKey(CreatureObject* owner, String& misKey) {
	TangibleObject* tano = NULL;

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		SceneObject* obj = getObject(i);

		if (obj->isTangible()) {
			tano = (TangibleObject*)obj;

			if ((tano->getMisoAsocKey() == misKey) && (!tano->isEquipped())) {
				if (tano != NULL) {
					removeObject(tano->getObjectID());

					if (owner->isPlayer()) {
						tano->sendDestroyTo((Player*) owner);
					}

					tano->finalize();
				}
			} else {
				tano = NULL;
			}
		}
	}
}

int InventoryImplementation::getUnequippedItemCount() {
	int count = 0;

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		SceneObject* obj = getObject(i);

		if (obj->isTangible()) {
			TangibleObject* tano = (TangibleObject*) obj;

			if (!tano->isEquipped()) {
				++count;

				if (tano->isContainer())
					count = count + tano->getContainerObjectsWithChildsSize();
			}
		}
	}

	return count;
}

bool InventoryImplementation::addObject(SceneObject* obj) {
	uint64 oid = obj->getObjectID();

	if (!objects.contains(oid))
		obj->acquire();

	if (!((TangibleObject*) obj)->isEquipped())
		obj->setParent(_this, 0xFFFFFFFF);

	obj->setPickupFlag(true);

	objects.put(oid, obj);

	return true;
}

bool InventoryImplementation::removeObject(int index) {
	SceneObject* item = objects.get(index);

	if (item == NULL)
		return false;

	objects.remove(index);

	item->setParent(NULL);
	item->release();

	return true;
}

bool InventoryImplementation::removeObject(uint64 oid) {
	SceneObject* item = objects.get(oid);

	if (item == NULL)
		return false;

	objects.drop(oid);

	item->setParent(NULL);
	item->release();

	return true;
}

void InventoryImplementation::moveObjectToTopLevel(CreatureObject* owner, TangibleObject* obj) {
	SceneObject* parent = obj->getParent();
	if (parent == NULL)
		return;

	if (!((TangibleObject*) parent)->isContainer())	//Item not in a container, no need to go further
		return;

	//Item is in a container, check for inventory. Item needs to be moved to the inventory for/on use
	while (parent->getParentID() > 0) {
		if (parent->isPlayer() && parent->isCell()) // item is not in a nested inventory container - break out!
			break;

		if (parent->isPlayerInventory()) {
			Zone* zone = owner->getZone();

			if (zone != NULL) {
				ItemManager* itemmanager = zone->getZoneServer()->getItemManager();

				if (itemmanager != NULL) {
					itemmanager->moveItemToDestination((Player*) owner, (TangibleObject*) obj, owner->getInventory());
					break;
				}
			}
		}
		parent = parent->getParent();
	}
}
