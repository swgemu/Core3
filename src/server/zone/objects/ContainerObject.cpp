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

ContainerObject::ContainerObject() {
	containerLimit = -1; //no limit

	objects.setInsertPlan(SortedVector<VectorMapEntry<uint64, SceneObject*>*>::NO_DUPLICATE);
	objects.setNullValue(NULL);
}

ContainerObject::~ContainerObject() {
	while (objects.size() > 0) {
		ManagedReference<SceneObject> obj = objects.get(0);

		if (obj == NULL)
			continue;

		objects.drop(obj->getObjectID());

		obj->setParent(NULL);

		obj->finalize();
	}
}

/**
 * Add a child object to the container
 * \param obj Object being added. All of its children can be found if extend is enabled in a container search
 * \retval bool True if successful
 */
bool ContainerObject::addChild(SceneObject* obj) {
	uint64 oid = obj->getObjectID();

	if (objects.contains(oid))
		return true;

	objects.put(oid, obj);

	obj->setParent((SceneObject*)sceneObject->_getStub());

	return true;
}

/**
 * Remove a child object from the container
 * \param oid ID of SceneObject being removed
 * \retval bool True if successful
 */
bool ContainerObject::removeChild(uint64 oid) {
	SceneObject* obj = objects.get(oid);

	if (obj == NULL)
		return false;

	obj->setParent(NULL);

	objects.drop(oid);

	return true;
}

/**
 * Returns child object within the container
 * \param oid Object ID of child object to get
 * \param extend Default: false. Searches all containers (not just top level) in children for the desired object
 * \deprecated Extend can be very resource intensive and is only useful in a set of very limited cases,
 * use sparingly.
 * \retval SceneObject Object of child. NULL if not found
 */
SceneObject* ContainerObject::getChild(uint64 oid, bool extend) {
	if (!extend)
		return objects.get(oid);

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* obj = objects.get(i);
		if (obj == NULL)
			continue;

		SceneObject* nestedObj = obj->getObject(oid, true);
		if (nestedObj != NULL)
			return nestedObj;
	}

	return NULL;
}

/**
 * Returns a boolean indicating if a child exists within the container
 * \param oid Object ID of child object to search for
 * \param extend Default: false. Searches all containers (not just top level) in children for the desired object
 * \deprecated Extend can be very resource intensive and is only useful in a set of very limited cases,
 * use sparingly.
 * \retval bool True if found
 */
bool ContainerObject::hasChild(uint64 oid, bool extend) {
	bool ret = objects.contains(oid);

	if (!ret && extend) {
		for (int i = 0; i < objects.size(); ++i) {
			SceneObject* nestedObj = objects.get(i);
			if (nestedObj == NULL)
				continue;

			if (nestedObj->hasObject(oid, true))
				return true;
		}
	}

	return ret;
}

/**
 * Returns number of children the container has
 * \param extend Default: false. Counts the size of all children, not just the top level.
 * \retval int Number of children.
 */
int ContainerObject::getContainerSize(bool extend) {
	if(!extend)
		return objects.size();

	int offset = objects.size();

	for (int i = 0; i < objects.size(); ++i) {
		SceneObject* nestedObj = objects.get(i);
		if (nestedObj == NULL)
			continue;

		offset += nestedObj->getContainerSize(true);
	}

	return offset;
}

