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

#include "ContainerObject.h"

#include "../tangible/TangibleObject.h"
#include "../player/Player.h"

#include "../../packets/scene/ClientOpenContainerMessage.h"

#include "../../packets.h"

ContainerObject::ContainerObject(SceneObjectImplementation* obj) {
	sceneObject = obj;

	containerType = 0;
	containerVolumeLimit = 0;

	objects.setInsertPlan(SortedVector<VectorMapEntry<uint64, SceneObject*>*>::NO_DUPLICATE);
	objects.setNullValue(NULL);
}

ContainerObject::~ContainerObject() {
	while (objects.size() > 0) {
		ManagedReference<SceneObject> item = objects.get(0);

		objects.drop(item->getObjectID());

		item->setParent(NULL);

		item->finalize();
	}
}

bool ContainerObject::addObject(SceneObject* obj) {
	uint64 oid = obj->getObjectID();

	if (objects.contains(oid))
		return true;

	obj->setPickupFlag(true);

	objects.put(oid, obj);

	obj->setParent((SceneObject*)sceneObject->_getStub());

	return true;
}

bool ContainerObject::removeObject(int index) {
	SceneObject* item = objects.get(index);

	if (item == NULL)
		return false;

	item->setParent(NULL);

	objects.remove(index);

	return true;
}

bool ContainerObject::removeObject(uint64 oid) {
	SceneObject* item = objects.get(oid);

	if (item == NULL)
		return false;

	item->setParent(NULL);

	objects.drop(oid);

	return true;
}

void ContainerObject::openTo(Player* player) {
	if (player != sceneObject->getParent() && player->getInventory() != sceneObject->getParent())
		sendItemsTo(player);

	ClientOpenContainerMessage* msg = new ClientOpenContainerMessage(sceneObject);
	player->sendMessage(msg);
}

void ContainerObject::sendItemsTo(Player* player) {
	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		SceneObject* item = getObject(i);

		item->sendTo(player);
	}
}

int ContainerObject::getContainerObjectsWithChildsSize() {
	int offset = objects.size();

	for (int i = 0; i < getContainerObjectsSize(); ++i) {
		TangibleObject* nestedItem = (TangibleObject*) getObject(i);
		if (nestedItem->isContainer())
			offset += nestedItem->getContainerObjectsSize();
	}

	return offset;
}
