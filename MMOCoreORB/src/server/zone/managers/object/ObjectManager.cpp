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

#include "ObjectManager.h"

ObjectManager::ObjectManager(ServiceThread* serv) : Logger("ObjectManager") {
	server = serv;

	objectMap = new ObjectMap(100000);
	objectCacheMap = new ObjectMap(20000);

	setLogging(false);
	setGlobalLogging(true);
}

ObjectManager::~ObjectManager() {
	delete objectMap;

	info("cleaning up objects..");

	objectCacheMap->resetIterator();

	while (objectCacheMap->hasNext()) {
		SceneObject* object = objectCacheMap->next();

		if (object->isPlayer())
			info("object \'" + object->_getName() + "\' was not cleaned up properly");
	}

	info("objects cleaned up", true);

	delete objectCacheMap;
}

SceneObject* ObjectManager::add(SceneObject* obj) {
	uint64 oid = obj->getObjectID();

	if (objectCacheMap->remove(oid) != NULL) {
		obj->redeploy();

		return objectMap->put(oid, obj);
	} else {
		return objectMap->put(oid, obj);
	}
}

SceneObject* ObjectManager::get(uint64 oid) {
	return objectMap->get(oid);
}

SceneObject* ObjectManager::remove(uint64 oid) {
	SceneObject* obj = NULL;

	obj = objectMap->remove(oid);
	if (obj == NULL)
		return NULL;

	obj->info("removed from ObjectManager");

	if (obj->isPlayer()) {
		objectCacheMap->put(oid, obj);

		obj->scheduleUndeploy();
	}

	return obj;
}

bool ObjectManager::destroy(SceneObject* obj) {
	uint64 oid = obj->getObjectID();

	if (!objectCacheMap->containsKey(oid) && objectMap->containsKey(oid))
		return false;

	objectCacheMap->remove(oid);

	return true;
}

SceneObject* ObjectManager::getCachedObject(uint64 oid) {
	SceneObject* obj = objectCacheMap->get(oid);

	if (obj != NULL) {
		objectCacheMap->remove(oid);

		obj->redeploy();
	}

	return obj;
}

SceneObject* ObjectManager::removeCachedObject(uint64 oid) {
	SceneObject* obj = objectCacheMap->remove(oid);

	if (obj != NULL)
		obj->info("removed from ObjectManager cache");

	return obj;
}
