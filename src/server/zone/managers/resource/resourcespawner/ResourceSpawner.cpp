/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

#include "ResourceSpawner.h"
#include "ResourceShiftTask.h"

ResourceSpawner::ResourceSpawner(ManagedReference<ZoneServer* > serv,
		ZoneProcessServerImplementation* impl, ObjectManager* objMan) {

	server = serv;
	processor = impl;
	databaseManager = ObjectDatabaseManager::instance();

	nameManager = processor->getNameManager();
	objectManager = objMan;

	resourceTree = new ResourceTree();

	loadResourceSpawns();

	minimumPool = new MinimumPool(this, resourceTree);
	fixedPool = new FixedPool(this, resourceTree);
	randomPool = new RandomPool(this, resourceTree);
	nativePool = new NativePool(this, resourceTree);
}

ResourceSpawner::~ResourceSpawner() {

	delete resourceTree;
	delete minimumPool;
	delete fixedPool;
	delete randomPool;
	delete nativePool;

	resourceZones.removeAll();
}

void ResourceSpawner::initializeMinimumPool(const String& includes, const String& excludes) {
	minimumPool->initialize(includes, excludes);
}

void ResourceSpawner::initializeFixedPool(const String& includes, const String& excludes) {
	fixedPool->initialize(includes, excludes);
}

void ResourceSpawner::initializeRandomPool(const String& includes, const String& excludes, const int size) {
	randomPool->initialize(includes, excludes, size);
}

void ResourceSpawner::initializeNativePool(const String& includes, const String& excludes) {
	nativePool->initialize(includes, excludes);
}

void ResourceSpawner::addPlanet(const int planetid) {
	resourceZones.add(planetid);
}

void ResourceSpawner::setSpawningParameters(const int shiftint, const int dur,
		const float throt, const int override, const int spawnquantity) {

	shiftInterval = shiftint;
	shiftDuration = dur;
	lowerGateOverride = override;
	maxSpawnAmount = spawnquantity;

	spawnThrottling = throt;

	if (spawnThrottling > .9f)
		spawnThrottling = .9f;
	if (spawnThrottling < .1f)
		spawnThrottling = .1f;

	if (lowerGateOverride < 1)
		lowerGateOverride = 1;
	if (lowerGateOverride > 1000)
		lowerGateOverride = 1000;
}

void ResourceSpawner::start() {
	shiftResources();
}

void ResourceSpawner::loadResourceSpawns() {

	/*ObjectDatabase* resourceSpawnDatabase = databaseManager->loadDatabase("resourcespawns", true, 0);

	ObjectDatabaseIterator iterator(resourceSpawnDatabase);

	uint64 objectID;

	ObjectInputStream objectData(2000);

	while (iterator.getNextKeyAndValue(objectID, &objectData)) {
		SceneObject* object = (SceneObject*) getObject(objectID);

		if (object != NULL)
			continue;

		if (!Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, &objectData)) {
			error("unknown scene object in static database");
			continue;
		}

		if (object == NULL) {
			object = createObject(serverObjectCRC, 0, "staticobjects", objectID);

			if (object == NULL) {
				error("could not load object from static database");

				continue;
			}

			deSerializeObject(object, &objectData);

			objectData.reset();
		}
	}*/
}

void ResourceSpawner::shiftResources() {

	minimumPool->update();
	fixedPool->update();
	randomPool->update();
	nativePool->update();

	createResourceSpawn("metal");

	ResourceShiftTask* resourceShift = new ResourceShiftTask(this);
	resourceShift->schedule(shiftInterval);
}


ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type,
		const Vector<String> excludes) {

	ResourceTreeEntry* resourceTemplate = resourceTree->getRandomResource(type, excludes);

	resourceTemplate->toString();

	resourceTemplate = resourceTree->getRandomResource(type, excludes);

	resourceTemplate->toString();

	resourceTemplate = resourceTree->getRandomResource(type, excludes);

	resourceTemplate->toString();

 	String name = nameManager->makeResourceName(resourceTemplate->isOrganic());

	ResourceSpawn* newSpawn = (ResourceSpawn*) objectManager->createObject(741847407, 2, "resourcespawns");

	System::out << name << endl;

	return newSpawn;
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type) {

	Vector<String> excludes;

	return createResourceSpawn(type, excludes);
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const Vector<String> includes,
		const Vector<String> excludes) {

	String type = includes.get(System::random(includes.size() - 1));

	return createResourceSpawn(type, excludes);
}
