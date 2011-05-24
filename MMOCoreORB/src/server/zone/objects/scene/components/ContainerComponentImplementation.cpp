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

#include "ContainerComponent.h"
#include "server/zone/objects/scene/SceneObject.h"

int ContainerComponentImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	if (sceneObject == object) {
		errorDescription = "@container_error_message:container02";

		return TransferErrorCode::CANTADDTOITSELF;
	}

	if (containmentType == 4) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement)) {
				errorDescription = "@container_error_message:container04";

				return TransferErrorCode::SLOTOCCUPIED;
			}
		}
	} else if (containmentType == -1) {
		if (containerObjects.size() >= containerVolumeLimit) {
			errorDescription = "@container_error_message:container03";

			return TransferErrorCode::CONTAINERFULL;
		}

	} else {
		sceneObject->error("unkown containmentType type");

		errorDescription = "DEBUG: cant move item unkown containmentType type";
		return TransferErrorCode::UNKNOWNCONTAIMENTTYPE;
	}

	return 0;
}

bool ContainerComponentImplementation::addObject(SceneObject* object, int containmentType, bool notifyClient) {
	if (sceneObject == object)
		return false;

	if (object->getParent() != NULL && object->getParent() != sceneObject) {
		ManagedReference<SceneObject*> objParent = object->getParent();

		if (objParent->hasObjectInContainer(object->getObjectID()) || objParent->hasObjectInSlottedContainer(object)) {
			sceneObject->error("trying to add an object with a parent already");
			objParent->info("the object is in here", true);
			return false;
		} else
			object->setParent(NULL);
	}

	bool update = true;

	//if (containerType == 1 || containerType == 5) {
	if (containmentType == 4) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement)) {
				return false;
			}
		}

		for (int i = 0; i < arrangementSize; ++i) {
			slottedObjects.put(object->getArrangementDescriptor(i), object);
		}
	} else if (containmentType == -1) { /* else if (containerType == 2 || containerType == 3) {*/
		if (containerObjects.size() >= containerVolumeLimit)
			return false;

		/*if (containerObjects.contains(object->getObjectID()))
			return false*/

		if (containerObjects.put(object->getObjectID(), object) == -1)
			update = false;

	} else {
		sceneObject->error("unkown container type");
		return false;
	}

	object->setParent(sceneObject);
	object->setContainmentType(containmentType);

	if (notifyClient)
		sceneObject->broadcastMessage(object->link(sceneObject->getObjectID(), containmentType), true);

	sceneObject->notifyObjectInserted(object);

	if (update) {
		sceneObject->updateToDatabase();
		//object->updateToDatabaseWithoutChildren()();
	}

	return true;
}

bool ContainerComponentImplementation::removeObject(SceneObject* object, bool notifyClient) {
	ManagedReference<SceneObject*> objectKeeper = object;

	if (object->getParent() != sceneObject && object->getParent() != NULL) {
		ManagedReference<SceneObject*> objParent = object->getParent();

		containerObjects.drop(object->getObjectID());

		if (objParent->hasObjectInContainer(object->getObjectID()) || objParent->hasObjectInSlottedContainer(object)) {
			sceneObject->error("trying to remove an object that is in a different object");
			objParent->info("i am the parent", true);

			return false;
		} else
			object->setParent(NULL);
	}

	int containedType = object->getContainmentType();

	//info("trying to remove object with containedType " + String::valueOf(containedType), true);

	if (containedType == 4/*containerType == 1 || containerType == 5*/) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.get(childArrangement) != object) {
				//info("sloted objects contains a different object", true);
				return false;
			}
		}

		for (int i = 0; i < arrangementSize; ++i)
			slottedObjects.drop(object->getArrangementDescriptor(i));
	} else if (containedType == -1/*containerType == 2 || containerType == 3*/) {
		if (!containerObjects.contains(object->getObjectID())) {
			//info("containerObjects doesnt contain specified object", true);
			return false;
		}

		containerObjects.drop(object->getObjectID());
	} else {
		sceneObject->error("unkown container type");
		return false;
	}

	object->setParent(NULL);

	if (notifyClient)
		sceneObject->broadcastMessage(object->link((uint64) 0, 0xFFFFFFFF), true);

	sceneObject->notifyObjectRemoved(object);

	sceneObject->updateToDatabase();
	object->updateToDatabase();

	return true;
}

void ContainerComponentImplementation::getContainmentObjects(VectorMap<String, ManagedReference<SceneObject*> >& objects) {
	objects = slottedObjects;
}

void ContainerComponentImplementation::notifyLoadFromDatabase() {

	/*for (int i = 0; i )
	if (parent == NULL && getZone() != NULL) {
			insertToZone(getZone());
		}
*/
}

