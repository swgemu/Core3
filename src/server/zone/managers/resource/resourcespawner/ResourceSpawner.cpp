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

	Logger::setLoggingName("ResourceSpawner");

	nameManager = processor->getNameManager();
	objectManager = objMan;

	resourceTree = new ResourceTree();
	resourceMap = new ResourceMap();

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

	delete resourceMap;

	activeResourceZones.removeAll();
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
	activeResourceZones.add(planetid);
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

	info("Building Resource Map");

	ObjectDatabase* resourceDatabase = ObjectDatabaseManager::instance()->loadDatabase("resourcespawns", true);

	ObjectDatabaseIterator iterator(resourceDatabase);

	uint64 objectID = 0;

	while (iterator.getNextKey(objectID)) {
		ManagedReference<ResourceSpawn* > resourceSpawn = (ResourceSpawn*) DistributedObjectBroker::instance()->lookUp(objectID);
		resourceMap->add(resourceSpawn->getName(), resourceSpawn);
	}
    String built = "Resource Map Built with " + String::valueOf(resourceMap->size()) + " resources";
	info(built);
}

void ResourceSpawner::shiftResources() {

	minimumPool->update();
	fixedPool->update();
	randomPool->update();
	nativePool->update();

	ResourceShiftTask* resourceShift = new ResourceShiftTask(this);
	resourceShift->schedule(shiftInterval);
}


ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type,
		int zoneid, const Vector<String> excludes) {

	ResourceTreeEntry* resourceEntry = resourceTree->getEntry(type, excludes, zoneid);

	if(resourceEntry == NULL)
		return NULL;

 	String name = makeResourceName(resourceEntry->isOrganic());

 	ResourceSpawn* newSpawn = new ResourceSpawn();

 	String resType = resourceEntry->getType();
 	newSpawn->setType(resType);

 	newSpawn->setName(name);

 	for(int i = 0; i < resourceEntry->getClassCount(); ++i) {
 		String resClass = resourceEntry->getClass(i);
 		newSpawn->addClass(resClass);
 	}

 	for(int i = 0; i < resourceEntry->getAttributeCount(); ++i) {
 		ResourceAttribute* attrib = resourceEntry->getAttribute(i);
 		int randomValue = randomizeValue(attrib->getMinimum(), attrib->getMaximum());
 		String attribName = attrib->getName();
 		newSpawn->addAttribute(attribName, randomValue);
 	}

 	long expires = getRandomExpirationTime(resourceEntry);

 	Vector<uint32> activeZones;
 	activeResourceZones.clone(activeZones);
 	newSpawn->createSpawnMaps(resourceEntry->isJTL(), resourceEntry->getZoneRestriction(), activeZones);

 	objectManager->persistObject(newSpawn,2,"resourcespawns");

 	resourceMap->add(name, newSpawn);

 	newSpawn->print();

	return newSpawn;
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type) {

	Vector<String> excludes;

	return createResourceSpawn(type, -1, excludes);
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const Vector<String> includes,
		int zoneid, const Vector<String> excludes) {

	String type = includes.get(System::random(includes.size() - 1));

	return createResourceSpawn(type, zoneid, excludes);
}

String ResourceSpawner::makeResourceName(bool isOrganic) {

	String randname;

	while (true) {

		randname = nameManager->makeResourceName(isOrganic);

		if (!resourceMap->contains(randname))
			break;
	}

	return randname;
}

int ResourceSpawner::randomizeValue(int min, int max) {
    if (min == 0 && max == 0)
    	return 0;

    if(min > lowerGateOverride)
        min = lowerGateOverride;

	int breakpoint = (int)(spawnThrottling * (max - min)) + min;
	int randomStat = System::random(max - min) + min;
	bool aboveBreakpoint = System::random(10) == 7;

	if (!(aboveBreakpoint && randomStat > breakpoint)
		|| (!aboveBreakpoint && randomStat < breakpoint)) {

		if (aboveBreakpoint) {
			while (randomStat < breakpoint)
				randomStat = System::random(max - min) + min;
		} else {
			while (randomStat > breakpoint)
	        randomStat = System::random(max - min) + min;
		}
	}
	return randomStat;
}

long ResourceSpawner::getRandomExpirationTime(ResourceTreeEntry* resourceEntry) {

	if(resourceEntry->isOrganic())
		return getRandomUnixTimestamp(6, 22);

	else if(resourceEntry->isJTL())
		return getRandomUnixTimestamp(13, 22);

	else
		return getRandomUnixTimestamp(6, 11);
}

long ResourceSpawner::getRandomUnixTimestamp(int min, int max) {

	return time(0) + (System::random((max * shiftDuration) -
			(min * shiftDuration)) + min * shiftDuration);

}
