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
#include "SurveyTask.h"
#include "SampleTask.h"
#include "SampleResultsTask.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/resource/ResourceListForSurveyMessage.h"
#include "server/zone/packets/resource/SurveyMessage.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/scene/ObserverEventType.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

ResourceSpawner::ResourceSpawner(ManagedReference<ZoneServer*> serv,
		ZoneProcessServer* impl, ObjectManager* objMan) {

	server = serv;
	processor = impl;
	databaseManager = ObjectDatabaseManager::instance();

	Logger::setLoggingName("ResourceSpawner");

	nameManager = processor->getNameManager();
	objectManager = objMan;
	samplingMultiplier = 1; //should be 1 for normal use

	minimumPool = new MinimumPool(this);
	fixedPool = new FixedPool(this);
	randomPool = new RandomPool(this);
	nativePool = new NativePool(this);
	manualPool = new ManualPool(this);
}

ResourceSpawner::~ResourceSpawner() {

	delete resourceTree;
	delete minimumPool;
	delete fixedPool;
	delete randomPool;
	delete nativePool;
	delete manualPool;

	delete resourceMap;

	activeResourceZones.removeAll();
}

void ResourceSpawner::init() {

	resourceTree = new ResourceTree(this);
	resourceMap = new ResourceMap();
}

void ResourceSpawner::initializeMinimumPool(const String& includes,
		const String& excludes) {
	minimumPool->initialize(includes, excludes);
}

void ResourceSpawner::initializeFixedPool(const String& includes,
		const String& excludes) {
	fixedPool->initialize(includes, excludes);
}

void ResourceSpawner::initializeRandomPool(const String& includes,
		const String& excludes, const int size) {
	randomPool->initialize(includes, excludes, size);
}

void ResourceSpawner::initializeNativePool(const String& includes,
		const String& excludes) {
	nativePool->initialize(includes, excludes);
}

void ResourceSpawner::addPlanet(const String& planetName) {
	activeResourceZones.add(planetName);
}

void ResourceSpawner::addJtlResource(const String& resourceName) {
	jtlResources.add(resourceName);
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

	ObjectDatabase* resourceDatabase =
			ObjectDatabaseManager::instance()->loadObjectDatabase("resourcespawns",
					true);

	ObjectDatabaseManager::instance()->commitLocalTransaction();
	ObjectDatabaseIterator iterator(resourceDatabase, true);

	uint64 objectID = 0;

	while (iterator.getNextKey(objectID)) {

		ManagedReference<ResourceSpawn*>
				resourceSpawn =
						dynamic_cast<ResourceSpawn*> (Core::getObjectBroker()->lookUp(
								objectID));
		//ObjectDatabaseManager::instance()->commitLocalTransaction();

		if (resourceSpawn == NULL) {
			error("Trying to load object as ResourceSpawn that is not a resource spawn");
			continue;
		}

		resourceMap->add(resourceSpawn->getName(), resourceSpawn);

		if (!resourceSpawn->inShift()) {
			despawn(resourceSpawn);
			continue;
		}

		if (resourceSpawn->getSpawnPool() != 0) {

			switch (resourceSpawn->getSpawnPool()) {
			case ResourcePool::MINIMUMPOOL:
				minimumPool->addResource(resourceSpawn, resourceSpawn->getPoolSlot());
				break;
			case ResourcePool::RANDOMPOOL:
				randomPool->addResource(resourceSpawn, resourceSpawn->getPoolSlot());
				break;
			case ResourcePool::FIXEDPOOL:
				fixedPool->addResource(resourceSpawn, resourceSpawn->getPoolSlot());
				break;
			case ResourcePool::NATIVEPOOL:
				nativePool->addResource(resourceSpawn, resourceSpawn->getPoolSlot());
				break;
			case ResourcePool::MANUALPOOL:
				manualPool->addResource(resourceSpawn, resourceSpawn->getPoolSlot());
				break;
			}
		}
	}

	//ObjectDatabaseManager::instance()->commitLocalTransaction();

	String built = "Resource Map Built with " + String::valueOf(
			resourceMap->size()) + " resources";
	info(built);
}

void ResourceSpawner::shiftResources() {
	randomPool->update();
	fixedPool->update();
	nativePool->update();
	minimumPool->update();
	manualPool->update();
}

ResourceSpawn* ResourceSpawner::manualCreateResourceSpawn(const String& type) {
	ResourceSpawn* resourceSpawn = createResourceSpawn(type);

	if (resourceSpawn != NULL)
		manualPool->addResource(resourceSpawn, "any");

	return resourceSpawn;
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type,
		const Vector<String>& excludes, const String& zonerestriction) {
	ResourceTreeEntry* resourceEntry = resourceTree->getEntry(type, excludes,
			zonerestriction);

	if (resourceEntry == NULL) {
		info("Resource type not found: " + type);
		return NULL;
	}

	String name = makeResourceName(resourceEntry->isOrganic());

	ResourceSpawn* newSpawn =
			dynamic_cast<ResourceSpawn*> (objectManager->createObject(
					0xb2825c5a, 1, "resourcespawns"));

	if (newSpawn == NULL) {
		error(
				"createResourceSpawn is trying to create a resourcespawn with the wrong type");
		return NULL;
	}

	String resType = resourceEntry->getType();
	newSpawn->setType(resType);

	newSpawn->setName(name);

	for (int i = 0; i < resourceEntry->getClassCount(); ++i) {
		String resClass = resourceEntry->getClass(i);
		newSpawn->addClass(resClass);

	}

	for (int i = 0; i < resourceEntry->getStfClassCount(); ++i) {
		String resClass = resourceEntry->getStfClass(i);
		newSpawn->addStfClass(resClass);
	}

	for (int i = 0; i < resourceEntry->getAttributeCount(); ++i) {
		ResourceAttribute* attrib = resourceEntry->getAttribute(i);
		int randomValue = randomizeValue(attrib->getMinimum(),
				attrib->getMaximum());
		String attribName = attrib->getName();
		int index = attrib->getIndex();
		newSpawn->addAttribute(attribName, randomValue);
	}

	long expires = getRandomExpirationTime(resourceEntry);
	newSpawn->setDespawned(expires);

	newSpawn->setZoneRestriction(resourceEntry->getZoneRestriction());

	newSpawn->setSurveyToolType(resourceEntry->getSurveyToolType());

	newSpawn->setContainerCRC(resourceEntry->getContainerCRC());

	Vector<String> activeZones;
	activeResourceZones.clone(activeZones);

	newSpawn->createSpawnMaps(resourceEntry->isJTL(),
			resourceEntry->getMinpool(), resourceEntry->getMaxpool(),
			resourceEntry->getZoneRestriction(), activeZones);

	if (newSpawn->isType("energy") || newSpawn->isType("radioactive"))
		newSpawn->setIsEnergy(true);

	resourceMap->add(name, newSpawn);

	//resourceEntry->toString();
	//newSpawn->print();

	return newSpawn;
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(const String& type,
		const String& zonerestriction) {
	Vector<String> excludes;

	return createResourceSpawn(type, excludes, zonerestriction);
}

ResourceSpawn* ResourceSpawner::createResourceSpawn(
		const Vector<String>& includes, const Vector<String>& excludes,
		const String& zonerestriction) {

	String type = includes.get(System::random(includes.size() - 1));

	return createResourceSpawn(type, excludes, zonerestriction);
}

void ResourceSpawner::despawn(ResourceSpawn* spawn) {

	for(int i = 0; i < spawn->getSpawnMapSize(); ++i) {
		String zone = spawn->getSpawnMapZone(i);
		resourceMap->remove(spawn, zone);
	}

	spawn->setSpawnPool(ResourcePool::NOPOOL, "");
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

	if (min > lowerGateOverride)
		min = lowerGateOverride;

	int breakpoint = (int) (spawnThrottling * (max - min)) + min;
	int randomStat = System::random(max - min) + min;
	bool aboveBreakpoint = System::random(10) == 7;

	if (!(aboveBreakpoint && randomStat > breakpoint) || (!aboveBreakpoint
			&& randomStat < breakpoint)) {

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

	if (resourceEntry->isOrganic())
		return getRandomUnixTimestamp(6, 22);

	else if (resourceEntry->isJTL())
		return getRandomUnixTimestamp(13, 22);

	else
		return getRandomUnixTimestamp(6, 11);
}

long ResourceSpawner::getRandomUnixTimestamp(int min, int max) {

	return time(0) + (System::random((max * shiftDuration) - (min
			* shiftDuration)) + min * shiftDuration);

}

Vector<String>& ResourceSpawner::getActiveResourceZones() {
	return activeResourceZones;
}

Vector<String>& ResourceSpawner::getJtlResources() {
	return jtlResources;
}

void ResourceSpawner::sendResourceListForSurvey(CreatureObject* player,
		const int toolType, const String& surveyType) {

	ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(
			player->getZone()->getZoneName());
	if (zoneMap == NULL) {
		player->sendSystemMessage("The tool fails to locate any resources");
		return;
	}

	ResourceListForSurveyMessage* message = new ResourceListForSurveyMessage();
	ManagedReference<ResourceSpawn*> resourceSpawn;
	Vector<ManagedReference<ResourceSpawn*> > matchingResources;

	for (int i = 0; i < zoneMap->size(); ++i) {
		resourceSpawn = zoneMap->get(i);

		if (resourceSpawn->getSurveyToolType() == toolType) {
			matchingResources.add(resourceSpawn);
			message->addResource(resourceSpawn->getName(),
					resourceSpawn->getType(), resourceSpawn->_getObjectID());
		}
	}

	message->finish(surveyType, player->getObjectID());

	player->sendMessage(message);

	/*for (int i = 0; i < matchingResources.size(); ++i) {

	 }*/
}

void ResourceSpawner::sendSurvey(CreatureObject* player, const String& resname) {

	/*if (player->getHAM(CreatureAttribute::MIND) < 100) {
		player->setPosture(CreaturePosture::UPRIGHT, true);
		player->sendSystemMessage("@error_message:survey_mind"); //You are exhausted. You nee to clear your head before you can survey again.
		return;
	}*/

	player->inflictDamage(player, CreatureAttribute::MIND, 100, false, true);

	PlayerObject* ghost = player->getPlayerObject();

	ManagedReference<SurveyTool*> surveyTool = ghost->getSurveyTool();

	if (surveyTool == NULL || !resourceMap->contains(resname) || player == NULL
			|| player->getZone() == NULL)
		return;

	String zoneName = player->getZone()->getZoneName();

	Survey* surveyMessage = new Survey();

	int toolRange = surveyTool->getRange(player);
	int points = surveyTool->getPoints();

	if (toolRange > 1024 || toolRange < 0)
		toolRange = 320;

	if (points <= 0 || points > 6)
		points =  3;

	float spacer = float(toolRange) / float(points - 1);

	float posX = player->getPositionX() - (((points - 1) / 2.0f) * spacer);
	float posY = player->getPositionY() + (((points - 1) / 2.0f) * spacer);

	float maxDensity = -1;
	float maxX, maxY;

	for (int i = 0; i < points; i++) {
		for (int j = 0; j < points; j++) {

			float density = resourceMap->getDensityAt(resname, zoneName, posX,
					posY);

			if (density > maxDensity) {
				maxDensity = density;
				maxX = posX;
				maxY = posY;
			}

			surveyMessage->add(posX, posY, density);

			posX += spacer;
		}

		posY -= spacer;
		posX -= (points * spacer);
	}

	ManagedReference<WaypointObject*> waypoint = NULL;

	if (maxDensity >= 0.1f) {

		// Get previous survey waypoint
		waypoint = ghost->getSurveyWaypoint();

		// Create new waypoint
		if (waypoint == NULL)
			waypoint = cast<WaypointObject*>( server->createObject(0xc456e788, 1));

		// Update new waypoint
		waypoint->setCustomName(UnicodeString("Resource Survey"));
		waypoint->setPlanetCRC(player->getZone()->getZoneCRC());
		waypoint->setPosition(maxX, 0, maxY);
		waypoint->setColor(WaypointObject::COLOR_BLUE);
		waypoint->setSpecialTypeID(WaypointObject::SPECIALTYPE_RESOURCE);
		waypoint->setActive(true);
	}

	// Send survey start message
	StringIdChatParameter message("survey", "start_survey");
	message.setTO(resname);
	ChatSystemMessage* sysMessage = new ChatSystemMessage(message);
	player->sendMessage(sysMessage);

	ManagedReference<ResourceSpawn*> resourceSpawn = resourceMap->get(resname);
	Reference<SurveyTask*> surveyTask = new SurveyTask(player, surveyMessage, waypoint, maxDensity * 100, resourceSpawn);
	player->addPendingTask("survey", surveyTask, 3000);
}

void ResourceSpawner::sendSample(CreatureObject* player, const String& resname,
		const String& sampleAnimation) {

	// Determine if survey tool is valid, and that resource actually exists
	PlayerObject* ghost = player->getPlayerObject();
	ManagedReference<SurveyTool*> surveyTool = ghost->getSurveyTool();

	if (surveyTool == NULL || !resourceMap->contains(resname) || player == NULL
			|| player->getZone() == NULL)
		return;

	/*if (player->getHAM(CreatureAttribute::ACTION) < 200) {
		player->setPosture(CreaturePosture::UPRIGHT, true);
		player->sendSystemMessage("@error_message:survey_mind"); //You are exhausted. You nee to clear your head before you can survey again.
		return;
	}*/

	player->inflictDamage(player, CreatureAttribute::ACTION, 200, false, true);

	PlayClientEffectLoc* effect = new PlayClientEffectLoc(sampleAnimation,
			player->getZone()->getZoneName(), player->getPositionX(),
			player->getPositionZ(), player->getPositionY());

	player->broadcastMessage(effect, true);

	// Obtain position information
	String zoneName = player->getZone()->getZoneName();
	float posX = player->getPositionX();
	float posY = player->getPositionY();

	// Get resource Density ay players position
	float density = resourceMap->getDensityAt(resname, zoneName, posX, posY);

	// Add sampleresultstask
	Reference<SampleResultsTask*> sampleResultsTask = new SampleResultsTask(
			player, this, density, resname);
	player->addPendingTask("sampleresults", sampleResultsTask, 3000);

	// Add sampletask
	Reference<SampleTask*> sampleTask = new SampleTask(player, surveyTool);
	player->addPendingTask("sample", sampleTask, 18000);
}

void ResourceSpawner::sendSampleResults(CreatureObject* player,
		const float density, const String& resname) {

	// Determine if survey tool is valid, and that resource actually exists
	PlayerObject* ghost = player->getPlayerObject();
	ManagedReference<SurveyTool*> surveyTool = ghost->getSurveyTool();
	if (surveyTool == NULL || player == NULL || player->getZone() == NULL)
		return;

	Locker playerLocker(player);

	String zoneName = player->getZone()->getZoneName();

	// If density is too low, we can't obtain a sample
	if (density < .10f) {
		StringIdChatParameter message("survey", "efficiency_too_low");
		message.setTO(resname);
		player->sendSystemMessage(message);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	// Lower skill levels mean you can't sample lower concetrations
	int surveySkill = player->getSkillMod("surveying");
	if ((density * 100) < (32 - ((surveySkill / 20) * 6)) || density < .10) {
		StringIdChatParameter message("survey", "density_below_threshold");
		message.setTO(resname);
		player->sendSystemMessage(message);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	Coordinate* richSampleLocation = surveyTool->getRichSampleLocation();

	float sampleRate = (surveySkill * density) + System::random(100);

	// Was the sample successful or not
	if (!surveyTool->tryGamble() && richSampleLocation == NULL && sampleRate
			< 40) {
		StringIdChatParameter message("survey", "sample_failed");
		message.setTO(resname);
		player->sendSystemMessage(message);

		return;
	}

	int maxUnitsExtracted = (int) (density * (25 + System::random(3)));

	int unitsExtracted = (maxUnitsExtracted * (float(surveySkill) / 100.0f))
			* samplingMultiplier;
	int xpcap = 40;

	if (surveyTool->tryGamble()) {
		if (System::random(2) == 1) {
			player->sendSystemMessage("@survey:gamble_success");
			unitsExtracted *= 5;
		} else {
			player->sendSystemMessage("@survey:gamble_fail");
		}
		surveyTool->clearGamble();
		xpcap = 50;
	}

	if (richSampleLocation != NULL) {

		if (player->getDistanceTo(richSampleLocation) < 10) {

			player->sendSystemMessage("@survey:node_recovery");
			unitsExtracted *= 5;

		} else {

			player->sendSystemMessage("@survey:node_not_close");
		}

		surveyTool->clearRichSampleLocation();
		xpcap = 50;
	}

	if (unitsExtracted < 2) {

		// Send message to player about trace amounts
		StringIdChatParameter message("survey", "trace_amount");
		message.setTO(resname);
		message.setDI(unitsExtracted);
		player->sendSystemMessage(message);

		return;
	}

	// Send message to player about unit extraction
	StringIdChatParameter message("survey", "sample_located");
	message.setTO(resname);
	message.setDI(unitsExtracted);
	player->sendSystemMessage(message);

	// We need the spawn object to track extraction
	ManagedReference<ResourceSpawn*> resourceSpawn = resourceMap->get(resname);
	resourceSpawn->extractResource(zoneName, unitsExtracted);

	int xp = (int) (((float) unitsExtracted / (float) maxUnitsExtracted)
			* xpcap);
	ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

	if (playerManager != NULL)
		playerManager->awardExperience(player, "resource_harvesting_inorganic", xp, true);

	addResourceToPlayerInventory(player, resourceSpawn, unitsExtracted);

	if (resourceSpawn->isType("radioactive")) {
		int wound = int((sampleRate / 30) - System::random(7));

		if (wound > 0) {
			player->addWounds(CreatureAttribute::HEALTH, wound, true);
			player->addWounds(CreatureAttribute::ACTION, wound, true);
			player->addWounds(CreatureAttribute::MIND, wound, true);
		}
	}
}

void ResourceSpawner::addResourceToPlayerInventory(CreatureObject* player, ResourceSpawn* resourceSpawn, int unitsExtracted) {
	// Add resource to inventory
	ManagedReference<SceneObject*> inventory = player->getSlottedObject(
			"inventory");

	if (inventory->hasFullContainerObjects()) {
		StringIdChatParameter err("survey", "no_inv_space");
		player->sendSystemMessage(err);
		player->setPosture(CreaturePosture::UPRIGHT, true);
		return;
	}

	// Check inventory for resource and add if existing
	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		ManagedReference<SceneObject*> object =
				inventory->getContainerObject(i);

		if (object->isResourceContainer()) {
			ManagedReference<ResourceContainer*> resource =
					cast<ResourceContainer*>( object.get());

			if (resource->getSpawnName() == resourceSpawn->getName() &&
					resource->getQuantity() < ResourceContainer::MAXSIZE) {
				int newStackSize = resource->getQuantity() + unitsExtracted;

				resource->setQuantity(newStackSize);
				return;
			}
		}
	}

	// Create New resource container if one isn't found in inventory
	ResourceContainer* harvestedResource = resourceSpawn->createResource(unitsExtracted);

	harvestedResource->sendTo(player, true);
	inventory->transferObject(harvestedResource, -1, true);
}

ResourceContainer* ResourceSpawner::harvestResource(CreatureObject* player,
		const String& type, const int quantity) {

	String zoneName = player->getZone()->getZoneName();

	ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(zoneName);
	if (zoneMap == NULL) {
		player->sendSystemMessage("Failed to locate any resources");
		return NULL;
	}

	ManagedReference<ResourceSpawn*> resourceSpawn;

	for (int i = 0; i < zoneMap->size(); ++i) {
		resourceSpawn = zoneMap->get(i);

		if (resourceSpawn != NULL && resourceSpawn->getType() == type) {
			resourceSpawn->extractResource(player->getZone()->getZoneName(), quantity);
			return resourceSpawn->createResource(quantity);
		}

	}
	player->sendSystemMessage("Failed to locate any suitable resources");
	return NULL;
}

void ResourceSpawner::harvestResource(CreatureObject* player, ResourceSpawn* resourceSpawn, int quantity) {

	resourceSpawn->extractResource(player->getZone()->getZoneName(), quantity);

	addResourceToPlayerInventory(player, resourceSpawn, quantity);
}

ResourceSpawn* ResourceSpawner::getCurrentSpawn(const String& restype, const String& zoneName) {

	ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(zoneName);

	if (zoneMap == NULL) {
		return NULL;
	}

	ManagedReference<ResourceSpawn*> resourceSpawn;

	for (int i = 0; i < zoneMap->size(); ++i) {
		resourceSpawn = zoneMap->get(i);

		if (resourceSpawn != NULL && resourceSpawn->getType().indexOf(restype) != -1)
			return resourceSpawn;
	}

	return NULL;
}

ResourceSpawn* ResourceSpawner::getFromRandomPool(const String& type) {
	return randomPool->removeSpawn(type);
}

void ResourceSpawner::addNodeToListBox(SuiListBox* sui, const String& nodeName) {
	ResourceTreeNode* baseNode = resourceTree->getBaseNode();

	ResourceTreeNode* node = baseNode->findNode(nodeName);

	//If we couldn't find a node
	if (node == NULL) {

		if (resourceMap->containsType(nodeName)) {
			resourceMap->addToSuiListBox(sui, nodeName);
			return;
		}

		node = baseNode;
	}

	node->addToSuiListBox(sui);
}

String ResourceSpawner::addParentNodeToListBox(SuiListBox* sui, const String& currentNode) {
	//currentNode can be the resource name itself, the ResourceTreeEntry (finalClass), or a ResourceTreeNode...
	ResourceTreeNode* baseNode = resourceTree->getBaseNode();

	//If is resource name
	if (resourceMap->contains(currentNode)) {
		ManagedReference<ResourceSpawn*> spawn = resourceMap->get(currentNode);
		ResourceTreeEntry* entry = baseNode->find(spawn->getFinalClass());

		if (entry != NULL) {
			resourceMap->addToSuiListBox(sui, entry->getFinalClass());
			return entry->getFinalClass();
		}
	}

	//If is finalClass
	ResourceTreeEntry* entry = baseNode->find(currentNode);

	if (entry != NULL) {
		ResourceTreeNode* node = entry->getMyNode();

		if (node != NULL) {
			node->addToSuiListBox(sui);
			return node->getName();
		}
	}

	ResourceTreeNode* node = baseNode->findNode(currentNode);

	if (node == NULL)
		node = baseNode;

	ResourceTreeNode* parentNode = node->getParentNode();

	if (parentNode != NULL)
		node = parentNode;

	node->addToSuiListBox(sui);

	return node->getName();
}

void ResourceSpawner::listResourcesForPlanetOnScreen(CreatureObject* creature, const String& planet) {
	ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(planet);

	if (zoneMap == NULL) {
		creature->sendSystemMessage("Invalid planet specified");
		return;
	}

	creature->sendSystemMessage("Resource spawns for " + planet);
	ManagedReference<ResourceSpawn*> resourceSpawn;

	for (int i = 0; i < zoneMap->size(); ++i) {
		resourceSpawn = zoneMap->get(i);

		if(resourceSpawn == NULL)
			continue;

		StringBuffer info;
		int hours = (((resourceSpawn->getDespawned() - System::getTime()) / 60) /60);
		int minutes = ((resourceSpawn->getDespawned() - System::getTime()) % 60);

		info << resourceSpawn->getFinalClass() << "   |   " << resourceSpawn->getName()
			 << "   |   " << "Despawns in: " << hours << " hours " << minutes << " minutes.";

		creature->sendSystemMessage(info.toString());
	}
}

String ResourceSpawner::healthCheck() {
	StringBuffer health;
	health << minimumPool->healthCheck() << endl;
	health << fixedPool->healthCheck() << endl;
	health << randomPool->healthCheck() << endl;
	health << nativePool->healthCheck() << endl;
	health << manualPool->healthCheck() << endl;

	return health.toString();
}
