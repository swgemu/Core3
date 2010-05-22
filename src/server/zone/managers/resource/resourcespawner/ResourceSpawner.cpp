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
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/packets/resource/ResourceListForSurveyMessage.h"
#include "server/zone/packets/resource/SurveyMessage.h"

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

	minimumPool = new MinimumPool(this);
	fixedPool = new FixedPool(this);
	randomPool = new RandomPool(this);
	nativePool = new NativePool(this);
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

void ResourceSpawner::setSpawningParameters(const int dur, const float throt,
		const int override, const int spawnquantity) {

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
	loadResourceSpawns();
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

		if(resourceSpawn->getSpawnPool() != 0) {

			switch(resourceSpawn->getSpawnPool()) {
			case ResourcePool::MINIMUMPOOL:
				minimumPool->addResource(resourceSpawn);
				break;
			case ResourcePool::RANDOMPOOL:
				randomPool->addResource(resourceSpawn);
				break;
			case ResourcePool::FIXEDPOOL:
				fixedPool->addResource(resourceSpawn);
				break;
			case ResourcePool::NATIVEPOOL:
				nativePool->addResource(resourceSpawn);
				break;
			}
		}
	}

    String built = "Resource Map Built with " + String::valueOf(resourceMap->size()) + " resources";
	info(built);
}

void ResourceSpawner::shiftResources() {

	minimumPool->update();
	randomPool->update();
	fixedPool->update();
	nativePool->update();
}


ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type,
		const Vector<String> excludes, int zonerestriction) {

	ResourceTreeEntry* resourceEntry = resourceTree->getEntry(type, excludes, zonerestriction);

	if(resourceEntry == NULL) {
		info("Resource type not found: " + type);
		return NULL;
	}

 	String name = makeResourceName(resourceEntry->isOrganic());

  	ResourceSpawn* newSpawn = (ResourceSpawn*)objectManager->createObject(0xb2825c5a, 1, "resourcespawns");

 	String resType = resourceEntry->getType();
 	newSpawn->setType(resType);

 	newSpawn->setName(name);

 	for(int i = 0; i < resourceEntry->getClassCount(); ++i) {
 		String resClass = resourceEntry->getClass(i);
 		newSpawn->addClass(resClass);
 	}

 	for(int i = 0; i < resourceEntry->getStfClassCount(); ++i) {
 		String resClass = resourceEntry->getStfClass(i);
 		newSpawn->addStfClass(resClass);
 	}

 	for(int i = 0; i < resourceEntry->getAttributeCount(); ++i) {
 		ResourceAttribute* attrib = resourceEntry->getAttribute(i);
 		int randomValue = randomizeValue(attrib->getMinimum(), attrib->getMaximum());
 		String attribName = attrib->getName();
 		newSpawn->addAttribute(attribName, randomValue);
 	}

 	long expires = getRandomExpirationTime(resourceEntry);
 	newSpawn->setDespawned(expires);

 	newSpawn->setZoneRestriction(resourceEntry->getZoneRestriction());

 	newSpawn->setSurveyToolType(resourceEntry->getSurveyToolType());

 	Vector<uint32> activeZones;
 	activeResourceZones.clone(activeZones);
 	newSpawn->createSpawnMaps(resourceEntry->isJTL(), resourceEntry->getZoneRestriction(), activeZones);

 	resourceMap->add(name, newSpawn);

	return newSpawn;
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type, int zonerestriction) {

	Vector<String> excludes;

	return createResourceSpawn(type, excludes, zonerestriction);
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const Vector<String> includes,
		const Vector<String> excludes, int zonerestriction) {

	String type = includes.get(System::random(includes.size() - 1));

	return createResourceSpawn(type, excludes, zonerestriction);
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

Vector<uint32> ResourceSpawner::getActiveResourceZones() {
	return activeResourceZones;
}

void ResourceSpawner::sendResourceListForSurvey(PlayerCreature* playerCreature, const int toolType, const String& surveyType) {

	ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(playerCreature->getZone()->getZoneID());
	if(zoneMap == NULL) {
		playerCreature->sendSystemMessage("The tool fails to locate any resources");
		return;
	}

	ResourceListForSurveyMessage* message = new ResourceListForSurveyMessage();
	ManagedReference<ResourceSpawn* > resourceSpawn;
	Vector<ManagedReference<ResourceSpawn* > > matchingResources;

	for(int i = 0; i < zoneMap->size(); ++i) {
		resourceSpawn = zoneMap->get(i);
		if(resourceSpawn->getSurveyToolType() == toolType) {
			matchingResources.add(resourceSpawn);
			message->addResource(resourceSpawn->getName(), resourceSpawn->getType(), resourceSpawn->_getObjectID());
		}
	}

	message->finish(surveyType, playerCreature->getObjectID());

	playerCreature->sendMessage(message);

	for(int i = 0; i < matchingResources.size(); ++i) {

	}
}

void ResourceSpawner::sendSurvey(PlayerCreature* playerCreature, const String& resname) {

	ManagedReference<SurveyTool* > surveyTool = playerCreature->getSurveyTool();

	if(surveyTool == NULL || !resourceMap->contains(resname))
		return;

	int zoneid = playerCreature->getZone()->getZoneID();

	Survey* surveyMessage = new Survey();

	//int toolRange = surveyTool->getRange();
	//int points = surveyTool->getPoints();

	int toolRange = 8192;
	int points = 32;

	float spacer = float(toolRange) / float(points);

	float posX = playerCreature->getPositionX() - ((points / 2.0f) * spacer);
	float posY = playerCreature->getPositionY() - ((points / 2.0f) * spacer);

	float maxDensity;
	float maxX, maxY;

	for (int i = 0; i < points; i++) {
		for (int j = 0; j < points; j++) {

			float density = resourceMap->getDensityAt(resname, zoneid, posX, posY);

			if (density > maxDensity) {
				maxDensity = density;
				maxX = posX;
				maxY = posY;
			}

			surveyMessage->add(posX, posY, density);

			posX += spacer;
		}

		posY += spacer;
		posX -= (points * spacer);
	}

	// Send Survey Results
	playerCreature->sendMessage(surveyMessage);

	/*if (max_res_percent >= 0.1f) {
		// Create Waypoint
		if (player->getSurveyWaypoint() != NULL) {
			ManagedReference<WaypointObject> wayobj = player->getSurveyWaypoint();
			player->removeWaypoint(wayobj);
			wayobj->finalize();
			player->setSurveyWaypoint(NULL);
		}

		WaypointObject* waypoint = new WaypointObject(player->getZoneID(), player->getNewItemID());
		waypoint->setCustomName(UnicodeString("Resource Survey"));
		waypoint->setPosition(wp_x, 0.0f, wp_y);

		waypoint->setActive(true);

		player->setSurveyWaypoint(waypoint);
		player->addWaypoint(waypoint);

		// Send Waypoint System Message
		UnicodeString ustr = "";
		ChatSystemMessage* endMessage = new ChatSystemMessage("survey", "survey_waypoint", ustr, 0, true);

		player->sendMessage(endMessage);
	}*/

}
