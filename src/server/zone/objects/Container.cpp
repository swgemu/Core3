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

#include "engine/engine.h"
#include "Container.h"
#include "SceneObject.h"

Container::Container(uint32 limit) {
	parentNode = NULL;
	containerLimit = limit;
	iteratorPosition = 0;

	childNodes.setInsertPlan(SortedVector<VectorMapEntry<uint64, SceneObject*>*>::NO_DUPLICATE);
	childNodes.setNullValue(NULL);
}

Container::Container(SceneObject* parent, uint32 limit) {
	parentNode = parent;
	containerLimit = limit;
	iteratorPosition = 0;

	childNodes.setInsertPlan(SortedVector<VectorMapEntry<uint64, SceneObject*>*>::NO_DUPLICATE);
	childNodes.setNullValue(NULL);
}

Container::~Container() {
	while (childNodes.size() > 0) {
		ManagedReference<SceneObject> obj = childNodes.get(0);

		if (obj == NULL)
			continue;

		childNodes.drop(obj->getObjectID());
		obj->setParent(NULL);
		obj->finalize();
	}
}


/**
 * Returns a container of objects contained within this one that matches the passed object type.
 * \param objtype The gameObjectType to search for.
 * \return Container A container of objects matching the specified object type.
 */
Container Container::getElementsByType(uint32 objtype) {
	Container resultcont(parentNode.get(), containerLimit);

	SceneObject* obj = NULL;

	resetContainerIterator();

	while ((obj = nextSibling()) != NULL) {
		if (obj->getObjectType() == objtype)
			resultcont.appendChild(obj);
	}

	return resultcont;
}

/**
 * Returns the first object of this container that matches the passed object type.
 * \param objtype The gameObjectType to search for.
 * \return SceneObject The first object matching the specified object type.
 */
SceneObject* Container::getElementByType(uint32 objtype) {
	SceneObject* obj = NULL;

	resetContainerIterator();

	while ((obj = nextSibling()) != NULL) {
		if (obj->getObjectType() == objtype)
			return obj;
	}

	return NULL;
}

/**
 * Returns a specific object from the container based on its objectid.
 * \param objid The objectid of the item searched for.
 * \return SceneObject The object if it is found. NULL if it is not.
 */
SceneObject* Container::getElementByID(uint64 objid) {
	if (childNodes.size() <= 0 || childNodes.contains(objid))
		return NULL;

	ManagedReference<SceneObject> obj = childNodes.get(objid);

	return (obj.get());
}

/**
 * Returns the next sibling indicated by the iterator counter.
 * \return SceneObject The next object in the child nodes. Returns NULL if there is none.
 */
SceneObject* Container::nextSibling() {
	if (iteratorPosition < 0)
		resetContainerIterator();

	if (iteratorPosition >= childNodes.size())
		return NULL;

	++iteratorPosition;

	ManagedReference<SceneObject> obj = childNodes.get(iteratorPosition);

	return (obj.get());
}

/**
 * Returns the previous sibling indicated by the iterator counter.
 * \return SceneObject The previous object in the child nodes. Returns NULL if there is none.
 */
SceneObject* Container::previousSibling() {
	if (iteratorPosition > childNodes.size())
		iteratorPosition = childNodes.size();

	if (iteratorPosition <= 0)
		return NULL;

	--iteratorPosition;

	ManagedReference<SceneObject> obj = childNodes.get(iteratorPosition);

	return (obj.get());
}

/**
 * Appends an object to the container list.
 * \param child The object to add to the container list.
 * \return bool Was the child successfully added.
 */
bool Container::appendChild(SceneObject* child) {
	if (containerLimit != 0 && childNodes.size() >= containerLimit)
		return false;

	if (childNodes.contains(child->getObjectID()))
		return false;

	child->setParent(parentNode);

	childNodes.put(child->getObjectID(), child);

	//VectorMap has been altered, reset the iterator.
	resetContainerIterator();

	return true;
}

/**
 * Removes an object from the container list.
 * \param objid The object to remove to the container list.
 * \return bool Was the child successfully removed.
 */
bool Container::removeChild(uint64 objid) {
	if (childNodes.size() <= 0 || !childNodes.contains(objid))
		return false;

	ManagedReference<SceneObject> obj = childNodes.get(objid);

	obj->setParent(NULL);

	childNodes.drop(objid);

	//VectorMap has been altered, reset the iterator.
	resetContainerIterator();

	return true;
}


/**
 * Indicates whether this container has a certain child or not
 * \param objid The object id of the child we are searching for.
 * \param recursive Should we look in child containers of this object as well? Default is false.
 * \return bool Returns true if the child object is found. False if it is not found.
 */
bool Container::hasChild(uint64 objid, bool recursive) {
	if (childNodes.size() <= 0)
		return false;

	if (!recursive)
		return (childNodes.contains(objid));

	resetContainerIterator();

	SceneObject* obj = NULL;

	while ((obj = nextSibling()) != NULL) {
		if (obj->getObjectID() == objid)
			return true;

		if (obj->hasChild(objid, true))
			return true;
	}

	return false;
}

/**
 * Finds the total number of objects in this container.
 * \param recursive Should we look in child containers of this object as well? Default is false.
 * \return int Returns the total number of objects found.
 */
int Container::getContainerSize(bool recursive) {
	int size = childNodes.size();

	if (!recursive)
		return size;

	resetContainerIterator();

	SceneObject* obj = nextSibling();

	while ((obj = nextSibling()) != NULL)
		size += obj->getContainerSize(true);

	return size;
}
