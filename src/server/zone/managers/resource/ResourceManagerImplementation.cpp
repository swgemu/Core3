/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.ta


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

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "events/SpawnResourcesEvent.h"

#include "ResourceManager.h"
#include "ResourceManagerImplementation.h"
#include "ResourceHarvestType.h"
#include "ResourceList.h"
#include "ResourceItem.h"

#include "../name/NameManager.h"

#include "../../objects/tangible/resource/ResourceContainerImplementation.h"
#include "../../objects/tangible/surveytool/SurveyToolImplementation.h"
#include "../../objects/tangible/InventoryImplementation.h"

#include "../../packets.h"

ResourceManagerImplementation::ResourceManagerImplementation(ZoneServer* inserver,
		ZoneProcessServerImplementation* inserv) : ResourceManagerServant(), Mutex("ResourceManager"), Lua() {

	setLoggingName("ResourceManager");

	itemStrings = NULL;

	init();

	serv = inserv;

	spawnResourcesEvent = new SpawnResourcesEvent(this);
	serv->addEvent(spawnResourcesEvent, 1000);
	//  This dictates the first time the spawner will run
	//  Spawner does take a good bit of time to populate an
	//  Empty database.

	forageResource = true;

	setLogging(false);
	setGlobalLogging(true);

	EMPTY = "";
}

ResourceManagerImplementation::~ResourceManagerImplementation() {
	if (spawnResourcesEvent != NULL) {
		delete spawnResourcesEvent;
		spawnResourcesEvent = NULL;
	}

	if (minimumpool != NULL) {
		delete minimumpool;
		minimumpool = NULL;
	}

	if (fixedpool != NULL) {
		delete fixedpool;
		fixedpool = NULL;
	}

	if (nativepool != NULL) {
		delete nativepool;
		nativepool = NULL;
	}

	if (resourceMap != NULL) {
		delete resourceMap;
		resourceMap = NULL;
	}
	if (resourceIDNameMap != NULL) {
		delete resourceIDNameMap;
		resourceIDNameMap = NULL;
	}

	if (resourceTree != NULL) {
		delete resourceTree;
		resourceTree = NULL;
	}

	if (itemStrings != NULL) {
		delete itemStrings;
		itemStrings = NULL;
	}
}

void ResourceManagerImplementation::init() {
	Lua::init();

	resourceMap = new VectorMap<String, ResourceTemplate*>();
	resourceMap->setNullValue(NULL);

	resourceIDNameMap = new VectorMap<uint64, String>();
	//resourceIDNameMap->setNullValue(NULL);


	info("Initializing Resource Manager");

	buildResourceMap();

	info("Resources built from database.");

	if (!loadConfigData()) {
		averageShiftTime = 3 * 3600000;

		aveduration = 86400;

		spawnThrottling = .9f;

		maxspawns = 40;
		minspawns = 25;
		maxradius = 2000;
		minradius = 600;

		info("Error in resource config file");
	}

	makeResourceTree();
	makeMinimumPoolVector();
	makeFixedPoolVector();
	makeNativePoolVector();
}


bool ResourceManagerImplementation::loadConfigFile() {
	return runFile("scripts/resources/config.lua");
}

bool ResourceManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;

	averageShiftTime = getGlobalInt("averageShiftTime");
	aveduration = getGlobalInt("aveduration");
	spawnThrottling = getGlobalFloat("spawnThrottling");

	maxspawns = getGlobalInt("maxspawns");
	minspawns = getGlobalInt("minspawns");
	maxradius = getGlobalInt("maxradius");
	minradius = getGlobalInt("minradius");

	//dBUser = getGlobalString("DBUser");
	//dBPass = getGlobalString("DBPass");

	return true;
}

void ResourceManagerImplementation::stop() {
	lock();

	if (spawnResourcesEvent->isQueued())
		serv->removeEvent(spawnResourcesEvent);

	for (int i = 0; i < resourceMap->size(); ++i)
		delete resourceMap->get(i);

	if (resourceMap != NULL)
		resourceMap->removeAll();

	if (resourceIDNameMap != NULL)
		resourceIDNameMap->removeAll();

	unlock();
}

void ResourceManagerImplementation::theShift() {
	lock();
	// Much of this method can be removed, the output statements
	// Make it easier to see what the spawner is doing and what
	// To expect what it runs.
	numQueries = 0;
	numFunctions = 0;
	numInsert = 0;
	numNameFunctions = 0;

	/*tempOver = 0;
	tempUnder = 0;*/

	info("starting resource spawner");

	removeExpiredResources();

	checkMinimumPool();
	checkRandomPool();
	checkFixedPool();
	checkNativePool();

	info("Queries run = " + String::valueOf(numQueries));
	info("Insert Queries run = " + String::valueOf(numInsert));
	info("Functions run = " + String::valueOf(numFunctions));
	info("Name functions run = " + String::valueOf(numNameFunctions));

	countResources();

	//verifyResourceMap();

	info("resource Spawner Finished");

	serv->addEvent(spawnResourcesEvent, averageShiftTime);
	unlock();

	//System::out << "Throttled at " << spawnThrottling << "   Over = " << tempOver << "   under = " << tempUnder << endl;
}

void ResourceManagerImplementation::countResources() {
	// This method pure supports out for the above method, is purely cosmetic
	try {
		StringBuffer query, query2, query3, query4;

		query << "SELECT DISTINCT resource_name FROM resource_spawns"
		<< " WHERE pool = 'minimum'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		info("Minimum Pool has " + String::valueOf(res->size()) + "/15 resources");
		delete res;

		query2 << "SELECT DISTINCT resource_name FROM resource_spawns"
		<< " WHERE pool = 'random'";

		res = ServerDatabase::instance()->executeQuery(query2);

		info("Random Pool has " + String::valueOf(res->size()) + "/24 resources");
		delete res;

		query3 << "SELECT DISTINCT resource_name FROM resource_spawns"
		<< " WHERE pool = 'fixed'";

		res = ServerDatabase::instance()->executeQuery(query3);

		info("Fixed Pool has " + String::valueOf(res->size()) + "/22 resources");
		delete res;

		query4 << "SELECT DISTINCT resource_name FROM resource_spawns"
		<< " WHERE pool = 'native'";

		res = ServerDatabase::instance()->executeQuery(query4);

		info("Native Pool has " + String::valueOf(res->size()) + "/420 resources");
		delete res;

		info("*** Extra resources expected ***");
	} catch (DatabaseException& e) {
		System::out << "Error in ResourceManagerImplementation::countResources()\n";
		System::out << e.getMessage();
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::countResources()\n";
	}
}

void ResourceManagerImplementation::clearResources() {
	lock();

	try {
		numFunctions++;

		StringBuffer query;
		query << "TRUNCATE TABLE `resource_spawns`;";
		query << "TRUNCATE TABLE `resource_data`;";

		ServerDatabase::instance()->executeStatement(query);

		numQueries++;
	} catch (DatabaseException& e) {
		System::out << "Error in ResourceManagerImplementation::clearResources\n";
		System::out << e.getMessage();
	} catch (...) {
		System::out << "unreported exception caught in in ResourceManagerImplementation::clearResources\n";
	}

	unlock();
}

float ResourceManagerImplementation::getDensity(int planet, String& resname,
		float inx, float iny) {
	float density = 0.0f, max_density = 0.0f;

	try {
		float x, y, radius, source, distance = 0.0f;

		SpawnLocation* sl;

		ResourceTemplate* resource = resourceMap->get(resname);

		if (resource == NULL)
			return max_density;

		for (int i = resource->getSpawnSize() - 1; i >= 0; i--) {
			sl = resource->getSpawn(i);

			if (sl->getPlanet() == planet) {
				x = sl->getX();
				y = sl->getY();

				radius = sl->getRadius();

				source = sl->getMax();

				if (inx > (x - radius) && inx < (x + radius) && iny > (y
						- radius) && iny < (y + radius)) {
					distance = sqrt(((inx - x) * (inx - x)) + ((iny - y) * (iny
							- y)));

					density = ((((radius - distance) / radius) * source)
							/ 100.0f);

					if (density > max_density)
						max_density = density;
				}
			}
		}
	} catch (DatabaseException& e) {
		System::out << e.getMessage();
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::getDensity\n";
	}

	return max_density;
}

float ResourceManagerImplementation::getDistanceFrom(float inx, float iny, float x, float y){
	float theX = x - inx;
	float theY = y - iny;

	return sqrt((theX * theX)+ (theY * theY));
}

void ResourceManagerImplementation::sendSurveyMessage(Player* player,
		String& resourceName, bool doLock) {
	// Added by Ritter
	if (player->getSurveyTool() == NULL)
		return;

	try {
		lock(doLock);

		Survey* surveyMessage = new Survey();

		float player_x = player->getPositionX();
		float player_y = player->getPositionY();

		float spacer, x, y, res_percent = 0.0f;
		float wp_x, wp_y, max_res_percent = 0.0f;

		int points;

		switch (player->getSurveyTool()->getSurveyToolRange()) {
		case 128:
			spacer = 42.6f;
			points = 4;
			x = player_x - (1.5 * spacer);
			y = player_y - (1.5 * spacer);
			break;
		case 192:
			spacer = 64.0f;
			points = 4;
			x = player_x - (1.5 * spacer);
			y = player_y - (1.5 * spacer);
			break;
		case 256:
			spacer = 64.0f;
			points = 5;
			x = player_x - (2 * spacer);
			y = player_y - (2 * spacer);
			break;
		case 320:
			spacer = 80.0f;
			points = 5;
			x = player_x - (2 * spacer);
			y = player_y - (2 * spacer);
			break;
		default:
			spacer = 32.0f;
			points = 3;
			x = player_x - spacer;
			y = player_y - spacer;
			break;
		}

		for (int i = 0; i < points; i++) {
			for (int j = 0; j < points; j++) {
				res_percent = getDensity(player->getZoneIndex(), resourceName, x, y);

				if (res_percent> max_res_percent) {
					max_res_percent = res_percent;
					wp_x = x;
					wp_y = y;
				}

				surveyMessage->add(x, y, res_percent);

				x += spacer;
			}

			y += spacer;
			x -= (points * spacer);
		}

		// Send Survey Results
		player->sendMessage(surveyMessage);

		if (max_res_percent >= 0.1f) {
			// Create Waypoint
			if (player->getSurveyWaypoint() != NULL) {
				player->removeWaypoint(player->getSurveyWaypoint());
				player->setSurveyWaypoint(NULL);
			}

			WaypointObject* waypoint = new WaypointObject(player, player->getNewItemID());
			waypoint->setName("Resource Survey");
			waypoint->setPosition(wp_x, 0.0f, wp_y);

			waypoint->changeStatus(true);

			player->setSurveyWaypoint(waypoint);
			player->addWaypoint(waypoint);

			// Send Waypoint System Message
			UnicodeString ustr = "";
			ChatSystemMessage* endMessage = new ChatSystemMessage("survey", "survey_waypoint", ustr, 0, true);

			player->sendMessage(endMessage);
		}

		unlock(doLock);
	} catch(...) {
		info("ResourceManagerImplementation::sendSurveyMessage threw an exception");
		player->sendSystemMessage("Error in sendSurveyMessage, please report this");
		unlock(doLock);
	}
}

void ResourceManagerImplementation::sendSampleMessage(Player* player,
		String& resourceName, bool doLock) {
	// Added by Ritter
	try {
		lock(doLock);

		float density = getDensity(player->getZoneIndex(), resourceName, player->getPositionX(), player->getPositionY());

		if (density < 0.1f) {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "density_below_threshold", resourceName, 0, false);

			player->sendMessage(sysMessage);

			player->changePosture(CreaturePosture::UPRIGHT);
		} else {
			if (player->getSampleTool() == NULL) {
				unlock(doLock);
				return;
			}

			float sampleRate = (player->getSkillMod("surveying") * density) + System::random(150);

			if (sampleRate > 100) {
				int resQuantity = int(density * 25 + System::random(3));

				if (!(resQuantity > 0))
					resQuantity = 1;

				player->getSampleTool()->sendSampleEffect(player);

				String xpType = "resource_harvesting_inorganic";
				int xp = 15;

				player->addXp(xpType, xp, true);

				ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_located", resourceName, resQuantity, false);
				player->sendMessage(sysMessage);

				ResourceContainer* newRcno = createNewResourceContainer(player, resourceName, resQuantity);

				if ( newRcno == NULL ) {
					unlock(doLock);
					return;
				}

				if (newRcno->getObjectSubType() == TangibleObjectImplementation::ENERGYRADIOACTIVE) {
					int wound = int((sampleRate / 70) - System::random(9));

					if (wound> 0) {
						player->changeHealthWoundsBar(wound, false);
						player->changeActionWoundsBar(wound, false);
						player->changeMindWoundsBar(wound, false);
					}
				}

				player->addInventoryResource(newRcno);
			} else {
				ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_failed", resourceName, 0, false);

				player->getSampleTool()->sendSampleEffect(player);

				player->sendMessage(sysMessage);
			}
		}

		unlock(doLock);
	} catch(...) {
		info("ResourceManagerImplementation::sendSampleMessage threw an exception");
		player->sendSystemMessage("Error in sendSampleMessage, please report this");
		unlock(doLock);
	}
}

ResourceList* ResourceManagerImplementation::getResourceListAtLocation(int zone, float x, float y, int type) {

	//lock(doLock);

	String class2, class2re = "";
	switch(type) {
	case ResourceHarvestType::SOLAR:
		class2 = "Solar Energy";
		break;
	case ResourceHarvestType::CHEMICAL:
		class2 = "Chemical";
		break;
	case ResourceHarvestType::FLORA:
		class2 = "Flora";
		break;
	case ResourceHarvestType::GAS:
		class2 = "Gas";
		break;
	case ResourceHarvestType::GEOTHERMAL:
		class2 = "Geothermal Energy";
		break;
	case ResourceHarvestType::MINERAL:
		class2 = "Mineral";
		class2re = "Radioactive Energy";
		break;
	case ResourceHarvestType::WATER:
		class2 = "Water";
		break;
	case ResourceHarvestType::WIND:
		class2 = "Wind Energy";
		break;
	case ResourceHarvestType::FUSION:
		class2 = "Radioactive Energy";
		break;
	default:
		//unlock(doLock);
		return NULL;
	}

	ResourceList *list = new ResourceList();

	ResourceTemplate* resource;

	for (int i = resourceMap->size() - 1; i > 0; i--) {
		resource = resourceMap->get(i);
		if (resource->getSpawnSize() > 0 && (strcmp(resource->getClass2().toCharArray(), class2.toCharArray()) == 0 || strcmp(resource->getClass2().toCharArray(), class2re.toCharArray()) == 0)) {
			for (int i = resource->getSpawnSize() - 1; i >= 0; i--) {
				SpawnLocation* sl = resource->getSpawn(i);
				if (sl->getPlanet() == zone) {
					if (!list->contains(resource->getName())) {

						//list->put(resource->getName(), Resource());
						float density = getDensity(zone, resource->getName(), x, y);
						if (density >= .01)
						{
							ResourceItem* ri = new ResourceItem(resource->getResourceID(), sl->getID(), sl->getExpireTime(), resource->getName(), resource->getType(), (int) (density * 100) );

							list->put(resource->getName(), ri);
						}

						//Resource *r = new Resource(resource->getResourceID(), resource->getName(), resource->getType(), 50);
						// list->put(resource->getName(), r);
					}
				}
			}
		}
	}


//	unlock(doLock);

	return list;
}

void ResourceManagerImplementation::harvestOrganics(Player* player,
		Creature* creature, int type) {
	/**
	 * Pre/post: creature and player are wlock()
	 */

	lock();

	bool proceed = false;
	int loop = 0;
	String harvestType = "";
	String creatureHealthType = "";
	int baseAmount = 0;
	int bonusAmount = 0;
	float bonusPercentage = 0;
	int variance;
	int creatureHealth;

	CreatureObject* creatureObj = (CreatureObject*) creature;

	String skillBox = "outdoors_scout_novice";

	if (player->isInRange(creature->getPositionX(), creature->getPositionY(),
			10.0f) && !player->isInCombat() && player->hasSkillBox(skillBox)
			&& creature->isDead() && creature->canHarvest(
			player->getFirstName())) {

		getHarvestingType(creatureObj, harvestType, baseAmount, type);

		if (baseAmount == 0 || harvestType == "") {
			unlock();
			return;
		}

		baseAmount = int(baseAmount * float(player->getSkillMod(
				"creature_harvesting") / 100.0f));

		creatureHealth = creatureObj->getCreatureHealth();

		switch (creatureHealth) {
		case 1:
			baseAmount = int(baseAmount * 0.50f);
			creatureHealthType = "creature_quality_scrawny";
			break;
		case 2:
			baseAmount = int(baseAmount * 0.75f);
			creatureHealthType = "creature_quality_skinny";
			break;
		case 3:
			baseAmount = int(baseAmount * 1.00f);
			creatureHealthType = "creature_quality_medium";
			break;
		case 4:
			baseAmount = int(baseAmount * 1.25f);
			creatureHealthType = "creature_quality_fat";
			break;
		}

		if (player->isInAGroup()) {

			GroupObject* group = player->getGroupObject();

			try {
				group->wlock(player);

				bonusPercentage = group->getRangerBonusForHarvesting(player);

				group->unlock();
			} catch (...) {
				group->unlock();
			}

			bonusAmount = int(bonusPercentage * baseAmount);
		}

		if (baseAmount < 1)
			baseAmount = 1;

		ResourceContainer* newRcno =
				new ResourceContainer(player->getNewItemID());

		String resname = getCurrentNameFromType(harvestType);

		if (resname == "") {
			unlock();
			return;
		}

		newRcno->setResourceName(resname);
		newRcno->setContents(baseAmount + bonusAmount);
		setResourceData(newRcno, false);

		StfParameter* stfparams = new StfParameter();

		stfparams->addDI(newRcno->getContents());
		stfparams->addTU(newRcno->getClassSeven());

		player->sendSystemMessage("skl_use", creatureHealthType, stfparams);

		if (player->isInAGroup()) {

			GroupObject* group = player->getGroupObject();

			try {
				group->wlock(player);

				stfparams = new StfParameter();

				stfparams->addTU(player->getFirstNameProper());
				stfparams->addDI(newRcno->getContents());
				stfparams->addTO(newRcno->getClassSeven());

				StringBuffer creatureName;
				creatureName << "@" << creature->getTemplateTypeName() << ":" << creature->getTemplateName();
				stfparams->addTT(creatureName.toString());

				group->sendSystemMessage(player, "group",
						"notify_harvest_corpse", stfparams, false);

				if (bonusPercentage == 0.2f)
					player->sendSystemMessage("skl_use", "group_harvest_bonus");
				else if (bonusPercentage == 0.3f)
					player->sendSystemMessage("skl_use", "group_harvest_bonus_ranger");
				else if (bonusPercentage == 0.4f)
					player->sendSystemMessage("skl_use", "group_harvest_bonus_masterranger");

				group->unlock();
			} catch (...) {
				group->unlock();
			}

		}

		player->addInventoryResource(newRcno);

		creature->removePlayerFromHarvestList(player->getFirstName());

		String xpType = "scout";
		//int xp = int(creatureObj->getXP() * .1f);
		int xp = int(creatureObj->getLevel() * 10);

		player->addXp(xpType, xp, true);
	}
	unlock();
}

void ResourceManagerImplementation::getHarvestingType(CreatureObject* creatureObj,
		String& harvestType, int& harvestAmount, int type) {

	bool proceed = false;
	int loop = 0;

	if (type == 0)
		type = System::random(2) + 1;

	while (!proceed) {

		if (loop > 4) {
			return;
		}

		switch (type) {
		case 1:
			if (creatureObj->getMeatMax() != 0) {
				harvestType = creatureObj->getMeatType();
				harvestAmount = creatureObj->getMeatMax();
				proceed = true;
			}
			break;
		case 2:
			if (creatureObj->getHideMax() != 0) {
				harvestType = creatureObj->getHideType();
				harvestAmount = creatureObj->getHideMax();
				proceed = true;
			}
			break;
		case 3:
			if (creatureObj->getBoneMax() != 0) {
				harvestType = creatureObj->getBoneType();
				harvestAmount = creatureObj->getBoneMax();
				proceed = true;
			}
			break;
		}

		if (!proceed) {
			type++;

			if (type > 3)
				type = 1;
		}

		loop++;
	}
}

void ResourceManagerImplementation::generateSUI(Player* player, SuiListBox* sui){

	SuiListBoxVector* choicesList = player->getSuiBoxChoices();
	Vector<String>* menuList = resourceTree->getSuiMenuList(choicesList);

	if (choicesList->size() > 0 && !resourceMap->contains(choicesList->get(choicesList->size()-1)) && resourceTree->classContainsResources(choicesList))
		sui->setPromptText("Choose resource type from " + choicesList->get(choicesList->size()-1));
	for (int i=0; i<menuList->size(); i++){
		sui->addMenuItem(menuList->get(i));
	}
}

bool ResourceManagerImplementation::useResourceDeed(Player* player, String& resourceName, int resourceQuantity) {
	Inventory* inventory = player->getInventory();

	if (inventory->getUnequippedItemCount() + 1 > InventoryImplementation::MAXUNEQUIPPEDCOUNT) {
		player->sendSystemMessage("You don't have enough space in your inventory");
		return false;
	}

	ResourceContainer* newRcno = createNewResourceContainer(player, resourceName, resourceQuantity);

	if ( newRcno == NULL ) {
		return false;
	}

	player->addInventoryItem(newRcno);
	newRcno->sendTo(player);
	return true;
}

String ResourceManagerImplementation::getCurrentNameFromType(String type){
	ResourceTemplate* resTemp;

	for (int i = 0; i < resourceMap->size(); ++i){
		resTemp = resourceMap->get(i);

		if (resTemp->getType() == type){
			if (resTemp->getSpawnSize() == 1)
				return resTemp->getName();
		}
	}

	return "";
}

ResourceContainer* ResourceManagerImplementation::createNewResourceContainer(CreatureObject* creature, String& resourceName, int resourceQuantity) {
	if ( !containsResource(resourceName) ) {
		info("Attempt to create invalid resource.");
		return NULL;
	}

	ResourceContainer* newRcno = new ResourceContainer(creature->getNewItemID());
	newRcno->setResourceName(resourceName);
	newRcno->setContents(resourceQuantity);
	setResourceData(newRcno, false);

	return newRcno;
}

bool ResourceManagerImplementation::containsResource(String& resourceName) {
	return resourceMap->contains(resourceName);
}

void ResourceManagerImplementation::setResourceData(ResourceContainer* resContainer, bool doLock) {
	// Added by Ritter
	lock(doLock);

	String resourceName = resContainer->getResourceName().toCharArray();
	ResourceTemplate* resource = resourceMap->get(resourceName);

	if (resource == NULL) {
		unlock(doLock);
		return;
	}

	try {
		resContainer->wlock();

		String contName;
		getResourceContainerName(resourceName, contName, false);
		UnicodeString cName = UnicodeString(contName.toCharArray());
		resContainer->setName(cName);

		resContainer->setResourceID(resource->getResourceID());

		resContainer->setDecayResistance(resource->getAtt1Stat());
		resContainer->setQuality(resource->getAtt2Stat());
		resContainer->setFlavor(resource->getAtt3Stat());
		resContainer->setPotentialEnergy(resource->getAtt4Stat());
		resContainer->setMalleability(resource->getAtt5Stat());
		resContainer->setToughness(resource->getAtt6Stat());
		resContainer->setShockResistance(resource->getAtt7Stat());
		resContainer->setColdResistance(resource->getAtt8Stat());
		resContainer->setHeatResistance(resource->getAtt9Stat());
		resContainer->setConductivity(resource->getAtt10Stat());
		resContainer->setEntangleResistance(resource->getAtt11Stat());
		resContainer->setClassSeven(resource->getClass7());

		resContainer->setContainerFile(resource->getType());
		resContainer->setObjectCRC(resource->getContainerCRC());
		resContainer->setObjectSubType(resource->getObjectSubType());

		resContainer->unlock();
	} catch(...) {
		resContainer->unlock();
		System::out << "unreported exception caught in ResourceManagerImplementation::setResourceData\n";
	}

	unlock(doLock);
}

bool ResourceManagerImplementation::checkResource(Player* player, String& resourceName, int SurveyToolType, bool doLock) {
	// Added by Ritter
	lock(doLock);

	ResourceTemplate* resource = resourceMap->get(resourceName);

	String surveyType, class2, class2re = "";
	switch(SurveyToolType) {
	case ResourceHarvestType::SOLAR:
		class2 = "Solar Energy";
		break;
	case ResourceHarvestType::CHEMICAL:
		class2 = "Chemical";
		break;
	case ResourceHarvestType::FLORA:
		class2 = "Flora";
		break;
	case ResourceHarvestType::GAS:
		class2 = "Gas";
		break;
	case ResourceHarvestType::GEOTHERMAL:
		class2 = "Geothermal Energy";
		break;
	case ResourceHarvestType::MINERAL:
		class2 = "Mineral";
		class2re = "Radioactive Energy";
		break;
	case ResourceHarvestType::WATER:
		class2 = "Water";
		break;
	case ResourceHarvestType::WIND:
		class2 = "Wind Energy";
		break;
	default:
		player->error("Invalid Tool (SurveyToolType) in ResourceManagerImplementation::checkResource");
		unlock(doLock);
		return false;
	}

	if (resource != NULL) {
		if (strcmp(resource->getClass2().toCharArray(), class2.toCharArray()) == 0 || strcmp(resource->getClass2().toCharArray(), class2re.toCharArray()) == 0) {
			for (int i = resource->getSpawnSize() - 1; i >= 0; i--) {
				SpawnLocation* sl = resource->getSpawn(i);

				if (sl->getPlanet() == player->getZoneID()) {
					unlock(doLock);
					return true;
				}
			}
		} else {
			ChatSystemMessage* msg = new ChatSystemMessage("survey","wrong_tool", resourceName, false, 0);
			player->sendMessage(msg);
		}
	}

	unlock(doLock);

	return false;
}

bool ResourceManagerImplementation::sendSurveyResources(Player* player, int SurveyToolType, bool doLock) {
	// Added by Ritter
	lock(doLock);
	Vector<String>* resourceList = new Vector<String>();

	String surveyType, class2, class2re = "";
	switch(SurveyToolType) {
	case ResourceHarvestType::SOLAR:
		class2 = "Solar Energy";
		surveyType = "energy_renewable_unlimited_solar";
		break;
	case ResourceHarvestType::CHEMICAL:
		class2 = "Chemical";
		surveyType = "chemical";
		break;
	case ResourceHarvestType::FLORA:
		class2 = "Flora";
		surveyType = "flora_resources";
		break;
	case ResourceHarvestType::GAS:
		class2 = "Gas";
		surveyType = "gas";
		break;
	case ResourceHarvestType::GEOTHERMAL:
		class2 = "Geothermal Energy";
		surveyType = "enegy_renewable_site_limited_geothermal";
		break;
	case ResourceHarvestType::MINERAL:
		class2 = "Mineral";
		class2re = "Radioactive Energy";
		surveyType = "mineral";
		break;
	case ResourceHarvestType::WATER:
		class2 = "Water";
		surveyType = "water";
		break;
	case ResourceHarvestType::WIND:
		class2 = "Wind Energy";
		surveyType = "enegy_renewable_unlimited_wind";
		break;
	default:
		player->error("Invalid Tool (SurveyToolType) in ResourceManagerImplementation::sendSurveyResources");
		delete resourceList;
		unlock(doLock);
		return false;
	}

	ResourceListForSurvey* packet = new ResourceListForSurvey();

	ResourceTemplate* resource;

	for (int i = resourceMap->size() - 1; i > 0; i--) {
		resource = resourceMap->get(i);
		if (resource->getSpawnSize() > 0 && (strcmp(resource->getClass2().toCharArray(), class2.toCharArray()) == 0 || strcmp(resource->getClass2().toCharArray(), class2re.toCharArray()) == 0)) {
			for (int i = resource->getSpawnSize() - 1; i >= 0; i--) {
				SpawnLocation* sl = resource->getSpawn(i);
				if (sl->getPlanet() == player->getZoneID()) {
					if (!isDuplicate(resourceList, resource->getName())) {
						packet->addResource(resource->getName(), resource->getType(), resource->getResourceID());
					}
				}
			}
		}
	}

	packet->finish(surveyType, player->getObjectID());

	player->sendMessage(packet);

	sendSurveyResourceStats(player, resourceList);

	delete resourceList;

	unlock(doLock);

	return true;
}

void ResourceManagerImplementation::sendSurveyResourceStats(Player* player, Vector<String>* rList) {
	// Added by Ritter
	ResourceTemplate* resource;

	for (int i = rList->size() - 1; i >= 0; i--) {
		resource = resourceMap->get(rList->get(i));

		AttributeListMessage* packet = new AttributeListMessage(resource->getResourceID());

		if (resource->getAtt1Stat() != 0) {
			packet->insertAttribute(resource->getAtt1(),resource->getAtt1Stat());
		}

		if (resource->getAtt2Stat() != 0) {
			packet->insertAttribute(resource->getAtt2(),resource->getAtt2Stat());
		}

		if (resource->getAtt3Stat() != 0) {
			packet->insertAttribute(resource->getAtt3(),resource->getAtt3Stat());
		}

		if (resource->getAtt4Stat() != 0) {
			packet->insertAttribute(resource->getAtt4(),resource->getAtt4Stat());
		}

		if (resource->getAtt5Stat() != 0) {
			packet->insertAttribute(resource->getAtt5(),resource->getAtt5Stat());
		}

		if (resource->getAtt6Stat() != 0) {
			packet->insertAttribute(resource->getAtt6(),resource->getAtt6Stat());
		}

		if (resource->getAtt7Stat() != 0) {
			packet->insertAttribute(resource->getAtt7(),resource->getAtt7Stat());
		}

		if (resource->getAtt8Stat() != 0) {
			packet->insertAttribute(resource->getAtt8(),resource->getAtt8Stat());
		}

		if (resource->getAtt9Stat() != 0) {
			packet->insertAttribute(resource->getAtt9(),resource->getAtt9Stat());
		}

		if (resource->getAtt10Stat() != 0) {
			packet->insertAttribute(resource->getAtt10(),resource->getAtt10Stat());
		}

		if (resource->getAtt11Stat() != 0) {
			packet->insertAttribute(resource->getAtt11(),resource->getAtt11Stat());
		}

		player->sendMessage(packet);
	}
}

void ResourceManagerImplementation::getClassSeven(const String& resource, String& clas, bool doLock) {
	lock(doLock);

	ResourceTemplate* resTemp = resourceMap->get(resource);

	if (resTemp != NULL)
		clas = resTemp->getClass7();

	unlock(doLock);
}

void ResourceManagerImplementation::getResourceContainerName(const String& resource, String& name, bool doLock) {
	lock(doLock);

	ResourceTemplate* resTemp = resourceMap->get(resource);

	if (resTemp != NULL) {
		if ( resTemp->getClass6() != "" && resTemp->getClass6() != "JTL")
			name = resTemp->getClass6();
		else if ( resTemp->getClass5() != "" && resTemp->getClass5() != "JTL")
			name = resTemp->getClass5();
		else if ( resTemp->getClass4() != "" && resTemp->getClass4() != "JTL")
			name = resTemp->getClass4();
		else if ( resTemp->getClass3() != "" && resTemp->getClass3() != "JTL")
			name = resTemp->getClass3();
		else if ( resTemp->getClass2() != "" && resTemp->getClass2() != "JTL")
			name = resTemp->getClass2();
		else if ( resTemp->getClass1() != "" && resTemp->getClass1() != "JTL")
			name = resTemp->getClass1();
	}

	unlock(doLock);
}

bool ResourceManagerImplementation::isDuplicate(Vector<String>* rList, String& resource) {
	// Added by Ritter
	if (rList->isEmpty()) {
		rList->add(resource);
		return false;
	}

	for (int i = rList->size() - 1; i >= 0; i--) {
		if (rList->get(i) == resource) {
			return true;
		}
	}

	rList->add(resource);

	return false;
}

void ResourceManagerImplementation::buildResourceMap() {
	ResourceTemplate* resTemp;
	SpawnLocation* sl;
	String resname;
	String query = "SELECT resource_data.`INDEX`, resource_data.resource_name, resource_data.resource_type, "
		"resource_data.class_1, resource_data.class_2, resource_data.class_3, resource_data.class_4, "
		"resource_data.class_5, resource_data.class_6, resource_data.class_7, resource_data.res_decay_resist, "
		"resource_data.res_quality, resource_data.res_flavor, resource_data.res_potential_energy, "
		"resource_data.res_malleability, resource_data.res_toughness, resource_data.res_shock_resistance, "
		"resource_data.res_cold_resist, resource_data.res_heat_resist, resource_data.res_conductivity, "
		"resource_data.entangle_resistance, resource_data.shiftedIn, resource_data.shiftedOut, resource_data.container, "
		"resource_data.containerCRC, resource_spawns.`INDEX`, resource_spawns.resource_name, resource_spawns.planet_id, "
		"resource_spawns.x, resource_spawns.y, resource_spawns.radius, resource_spawns.`max`, resource_spawns.despawn, "
		"resource_spawns.pool FROM resource_data LEFT JOIN resource_spawns ON resource_data.resource_name = "
		"resource_spawns.resource_name ORDER BY resource_data.resource_name ASC";

	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() != 0) {
			while (res->next()) {

				resname = res->getString(1);

				if (!resourceMap->contains(resname)) {

					resTemp = new ResourceTemplate(res->getString(2));
					resTemp->setName(resname);
					resTemp->setResourceID(res->getUnsignedLong(0));

					resTemp->setClass1(res->getString(3));
					resTemp->setClass2(res->getString(4));
					resTemp->setClass3(res->getString(5));
					resTemp->setClass4(res->getString(6));
					resTemp->setClass5(res->getString(7));
					resTemp->setClass6(res->getString(8));
					resTemp->setClass7(res->getString(9));

					resTemp->setMaxType(0);
					resTemp->setMinType(0);
					resTemp->setMinPool(0);
					resTemp->setMaxPool(0);

					resTemp->setAtt1("res_decay_resist");
					resTemp->setAtt2("res_quality");
					resTemp->setAtt3("res_flavor");
					resTemp->setAtt4("res_potential_energy");
					resTemp->setAtt5("res_malleability");
					resTemp->setAtt6("res_toughness");
					resTemp->setAtt7("res_shock_resistance");
					resTemp->setAtt8("res_cold_resist");
					resTemp->setAtt9("res_heat_resist");
					resTemp->setAtt10("res_conductivity");
					resTemp->setAtt11("entangle_resistance");

					resTemp->setAtt1Stat(res->getInt(10));
					resTemp->setAtt2Stat(res->getInt(11));
					resTemp->setAtt3Stat(res->getInt(12));
					resTemp->setAtt4Stat(res->getInt(13));
					resTemp->setAtt5Stat(res->getInt(14));
					resTemp->setAtt6Stat(res->getInt(15));
					resTemp->setAtt7Stat(res->getInt(16));
					resTemp->setAtt8Stat(res->getInt(17));
					resTemp->setAtt9Stat(res->getInt(18));
					resTemp->setAtt10Stat(res->getInt(19));
					resTemp->setAtt11Stat(res->getInt(20));

					resTemp->setContainer(res->getString(23));
					resTemp->setContainerCRC(res->getUnsignedInt(24));

					setObjectSubType(resTemp);

					resourceIDNameMap->put(resTemp->getResourceID(), resname);
					resourceMap->put(resname, resTemp);
				} else {
					resTemp = resourceMap->get(resname);
				}

				try {

					String pool = res->getString(33);
					// SpawnLocation(uint64 id, int inPlanet, float inX, float inY, float inRadius, float inMax, String& inPool) {
					sl
							= new SpawnLocation(res->getUnsignedLong(25), res->getInt(
									27), res->getFloat(28), res->getFloat(29), res->getFloat(
									30), res->getFloat(31), res->getUnsignedLong(32), pool);

					resTemp->addSpawn(sl);

				} catch (...) {

				}
			}
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in buildMap\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::buildResourceMap()\n";
	}
}

void ResourceManagerImplementation::verifyResourceMap() {
	ResourceTemplate* resTemp;

	for (int i = 0; i < resourceMap->size(); ++i){
		resTemp = resourceMap->get(i);

		verifyResourceData(i, resTemp);
	}
}

void ResourceManagerImplementation::verifyResourceData(int i, ResourceTemplate* resTemp) {
	ResourceTemplate* resNew;
	String resname;
	String query = "SELECT `INDEX`, `resource_name`, `resource_type`, `class_1`, `class_2`, `class_3`, `class_4`,"
		" `class_5`, `class_6`, `class_7`, `res_decay_resist`, `res_quality`, `res_flavor`, `res_potential_energy`,"
		" `res_malleability`, `res_toughness`, `res_shock_resistance`, `res_cold_resist`, `res_heat_resist`,"
		" `res_conductivity`, `entangle_resistance`, `shiftedIn`, `shiftedOut`, `container`, `containerCRC`"
		"  FROM resource_data WHERE `resource_name` = '" + resTemp->getName() + "'";
	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() == 1) {
			while (res->next()) {
				resname = res->getString(1);
				resNew = new ResourceTemplate(res->getString(2));
				resNew->setName(resname);
				resNew->setResourceID(res->getUnsignedLong(0));

				resNew->setClass1(res->getString(3));
				resNew->setClass2(res->getString(4));
				resNew->setClass3(res->getString(5));
				resNew->setClass4(res->getString(6));
				resNew->setClass5(res->getString(7));
				resNew->setClass6(res->getString(8));
				resNew->setClass7(res->getString(9));

				resNew->setMaxType(0);
				resNew->setMinType(0);
				resNew->setMinPool(0);
				resNew->setMaxPool(0);

				resNew->setAtt1("res_decay_resist");
				resNew->setAtt2("res_quality");
				resNew->setAtt3("res_flavor");
				resNew->setAtt4("res_potential_energy");
				resNew->setAtt5("res_malleability");
				resNew->setAtt6("res_toughness");
				resNew->setAtt7("res_shock_resistance");
				resNew->setAtt8("res_cold_resist");
				resNew->setAtt9("res_heat_resist");
				resNew->setAtt10("res_conductivity");
				resNew->setAtt11("entangle_resistance");

				resNew->setAtt1Stat(res->getInt(10));
				resNew->setAtt2Stat(res->getInt(11));
				resNew->setAtt3Stat(res->getInt(12));
				resNew->setAtt4Stat(res->getInt(13));
				resNew->setAtt5Stat(res->getInt(14));
				resNew->setAtt6Stat(res->getInt(15));
				resNew->setAtt7Stat(res->getInt(16));
				resNew->setAtt8Stat(res->getInt(17));
				resNew->setAtt9Stat(res->getInt(18));
				resNew->setAtt10Stat(res->getInt(19));
				resNew->setAtt11Stat(res->getInt(20));

				resNew->setContainer(res->getString(23));
				resNew->setContainerCRC(res->getUnsignedInt(24));

				setObjectSubType(resNew);

				if (!resNew->compare(resTemp)) {
					info("******* Resource: " + resname + " is inconsistant ********");

					//resTemp->toString();
					//resNew->toString();
				} else {
					//System::out << i << ". " << resname << " is good!\n";
				}
			}
		} else {
			info("Multiple Resource with name: " + resTemp->getName());
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in verifyMap\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::verifyResourceData\n";
	}
}

void ResourceManagerImplementation::removeExpiredResources() {
	try {
		numFunctions++;

		StringBuffer query, query2, query3;
		uint64 now = time(0);

		query << "SELECT `INDEX`, `resource_name` FROM resource_spawns WHERE despawn < " << now;

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() != 0) {
			while (res->next()) {
				uint64 sid = res->getUnsignedLong(0);
				String rname = res->getString(1);
				ResourceTemplate* resource = resourceMap->get(rname);

				if (resource != NULL) {
					SpawnLocation* sl = resource->removeSpawn(sid);
				} else {
					info("Error removing spawn location.");
				}
			}

			StringBuffer ss;
			ss << "Resources to be despawned: " << res->size();
			info(ss.toString());

			query2 << "UPDATE resource_data rd  "
			<< "INNER JOIN resource_spawns rs "
			<< " ON rd.resource_name = rs.resource_name "
			<< " SET rd.shiftedOut = " << now + (System::random(aveduration) + (averageShiftTime * 2))
			<< " WHERE rs.despawn <  " << now << " and rd.shiftedOut = 0";

			ServerDatabase::instance()->executeStatement(query2);

			info("Updated expiring resources with spawnout time");

			query3 << "DELETE FROM resource_spawns WHERE despawn < " << now;

			ServerDatabase::instance()->executeStatement(query3);

			info("Deleted despawned resources");

			numQueries++;
			numQueries++;
		} else {
			info("No resources to be despawned");
		}

		delete res;

		numQueries++;
	} catch (DatabaseException& e) {
		System::out << "Database error in ResourceManagerImplementation::removeExpiredResources()\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::removeExpiredResources()\n";
	}
}

void ResourceManagerImplementation::checkMinimumPool() {
	numFunctions++;

	String restype;
	String exclusion = "";

	Vector<String> spawnMe;

	poolNeeds(minimumpool, "minimum", &spawnMe);

	info("Minimum pool spawns = " + String::valueOf(spawnMe.size()));

	getFromRandomPool(&spawnMe, "minimum");

	for (int x = 0; x < spawnMe.size(); x++) {
		restype = getRandomResourceFromType(spawnMe.get(x), exclusion);
		createResource(restype, "minimum", false);
	}
}

void ResourceManagerImplementation::checkRandomPool() {
	numFunctions++;

	String restype;
	String exclusion = " AND (class_1 != 'Organic' and class_5 != 'Iron' and class_3 != 'Fiberplast')";
	String type = "Inorganic";

	int spawnMe = randomPoolNeeds();

	info("Random pool spawns = " + String::valueOf(spawnMe));

	for (int x = 0; x < spawnMe; x++) {
		restype = getRandomResourceFromType(type, exclusion);
		createResource(restype, "random", false);
	}
}

int ResourceManagerImplementation::randomPoolNeeds() {
	StringBuffer query;
	query << "SELECT DISTINCT rd.resource_name, rd.resource_type, rd.class_1,rd.class_2,rd.class_3,"
	<< "rd.class_4, rd.class_5, rd.class_6, rd.class_7 FROM `resource_data` rd "
	<< "INNER JOIN `resource_spawns` rs ON rs.resource_name = rd.resource_name "
	<< "WHERE rs.pool = 'random'";

	ResultSet* res = ServerDatabase::instance()->executeQuery(query);

	int size = res->size();

	numQueries++;

	delete res;

	return 24 - size;
}

void ResourceManagerImplementation::checkFixedPool() {
	numFunctions++;

	String restype;
	int ironCount = fixedPoolIron();

	info("Fixed pool iron spawns = " + String::valueOf(ironCount));

	for (int x = 0; x < ironCount; x++) {
		restype = getRandomResourceFromType(String("Iron"),	String(" AND class_2 != 'Energy'"));
		createResource(restype, "fixed", false);
	}

	Vector<String> spawnMe;

	poolNeeds(fixedpool, "fixed", &spawnMe);

	info("Fixed pool JTL spawns = " + String::valueOf(spawnMe.size()));

	for (int x = 0; x < spawnMe.size(); x++) {
		createResource(spawnMe.get(x), "fixed", true);
	}
}

int ResourceManagerImplementation::fixedPoolIron() {
	numFunctions++;

	StringBuffer query;
	query << "SELECT DISTINCT rd.resource_name, rd.resource_type, rd.class_1,rd.class_2,rd.class_3,"
	<< "rd.class_4, rd.class_5, rd.class_6, rd.class_7 FROM `resource_data` rd "
	<< "INNER JOIN `resource_spawns` rs ON rs.resource_name = rd.resource_name "
	<< "WHERE rs.pool = 'fixed'  AND rd.class_5 = 'Iron'";

	ResultSet* res = ServerDatabase::instance()->executeQuery(query);

	int size = res->size();

	delete res;

	numQueries++;

	return 14 - size;
}

void ResourceManagerImplementation::checkNativePool() {
	numFunctions++;

	String restype;
	String exclusion = " AND (class_1 = 'Organic')";
	String type = "Organic";

	Vector<String> spawnMe;

	poolNeeds(nativepool, "native", &spawnMe);

	info("Native pool spawns = " + String::valueOf(spawnMe.size()));

	getFromRandomPool(&spawnMe, "native");

	for (int x = 0; x < spawnMe.size(); x++) {
		//System::out << spawnMe[x] << endl;
		createResource(spawnMe.get(x), "native", false);
	}
}

void ResourceManagerImplementation::poolNeeds(Vector<String>* invector, String pool, Vector<String>* needs) {
	try {
		numFunctions++;

		StringBuffer query;

		Vector<String> has;

		bool hasItem;

		if (pool == "minimum") {
			query << "SELECT DISTINCT rd.resource_name, rd.resource_type, rd.class_1,rd.class_2,rd.class_3,"
			<< "rd.class_4, rd.class_5, rd.class_6, rd.class_7 FROM `resource_data` rd "
			<< "INNER JOIN `resource_spawns` rs ON rs.resource_name = rd.resource_name "
			<< "WHERE rs.pool = 'minimum'";
		} else {
			query << "SELECT DISTINCT rd.resource_type FROM `resource_data` rd "
			<< "INNER JOIN `resource_spawns` rs ON rs.resource_name = rd.resource_name "
			<< "WHERE rs.pool = '"<< pool << "'";
		}

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		numQueries++;

		while (res->next()) {
			for (int x = 0; x < invector->size(); x++) {
				if (pool == "minimum") {
					if (res->getString(2) == invector->get(x) || res->getString(3) == invector->get(x) ||
							res->getString(4) == invector->get(x) || res->getString(5) == invector->get(x) ||
							res->getString(6) == invector->get(x) || res->getString(7) == invector->get(x) ||
							res->getString(8) == invector->get(x)) {
						has.add(invector->get(x));
						break;
					}
				} else {
					if (res->getString(0) == invector->get(x)) {
						has.add(invector->get(x));
						break;
					}
				}
			}
		}

		for (int x = 0; x < invector->size(); x++) {
			hasItem = false;
			for (int y = 0; y < has.size(); y++) {

				if (has.get(y) == invector->get(x)) {

					hasItem = true;
					break;

				}
			}

			if (!hasItem) {
				needs->add(invector->get(x));
			}
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in ResourceManagerImplementation::poolNeeds\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::poolNeeds\n";
	}
}

void ResourceManagerImplementation::getFromRandomPool(Vector<String> * spawnMe,	String pool) {
	numFunctions++;

	for (int x = 0; x < spawnMe->size(); x++) {
		if (pool != "native" || (spawnMe->get(x).indexOf("water") != -1)) {
			try {
				StringBuffer query, query2;

				query << "SELECT DISTINCT rd.resource_name FROM `resource_data` rd "
				<< "INNER JOIN `resource_spawns` rs ON rs.resource_name = rd.resource_name "
				<< "WHERE rs.pool = 'random' and shiftedOut = 0 and ("
				<< "resource_type = '" << spawnMe->get(x) << "' OR "
				<< "class_1 = '" << spawnMe->get(x) << "' OR "
				<< "class_2 = '" << spawnMe->get(x) << "' OR "
				<< "class_3 = '" << spawnMe->get(x) << "' OR "
				<< "class_4 = '" << spawnMe->get(x) << "' OR "
				<< "class_5 = '" << spawnMe->get(x) << "' OR "
				<< "class_6 = '" << spawnMe->get(x) << "' OR "
				<< "class_7 = '" << spawnMe->get(x) << "')"
				<< "limit 1";

				ResultSet* res = ServerDatabase::instance()->executeQuery(query);

				numQueries++;

				if (res->size() > 0) {
					res->next();
					String resname = res->getString(0);

					query2 << "UPDATE resource_spawns "
					<< "SET pool = '" << pool << "' "
					<< "WHERE resource_name = '" << resname << "'";

					numQueries++;

					ServerDatabase::instance()->executeStatement(query2);

					spawnMe->remove(x);
					x--;
				}

				delete res;
			} catch (DatabaseException& e) {
				System::out << "Database error in ResourceManagerImplementation::getFromRandomPool\n";
				System::out << e.getMessage() << endl;
				break;
			} catch (...) {
				System::out << "unreported exception in ResourceManagerImplementation::getFromRandomPool\n";
				break;
			}
		}
	}
}

String ResourceManagerImplementation::getRandomResourceFromType(String restype, String exclusion) {
	numFunctions++;

	try {
		String outtype = "";

		StringBuffer query;
		query << "SELECT `resource_type`,`class_1`,`class_2`,"
		<< "`class_3`,`class_4`,`class_5`,`class_6`,`class_7`,`weight` "
		<< "FROM `resource_tree` "
		<< "WHERE (class_1 = '" << restype << "' OR "
		<< "class_2 = '" << restype << "' OR "
		<< "class_3 = '" << restype << "' OR "
		<< "class_4 = '" << restype << "' OR "
		<< "class_5 = '" << restype << "' OR "
		<< "class_6 = '" << restype << "' OR "
		<< "class_7 = '" << restype << "') AND ("
		<< "class_6 != 'JTL')" << exclusion;

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		numQueries++;

		// This is where the weighted code goes to spawn resource on
		// Rarity rather than jus t randomly

		int y = (System::random(res->size()-1));

		for (int x = 0; x < res->size(); x++) {
			res->next();

			if (x == y)
				return res->getString(0);
		}

		delete res;

	} catch (DatabaseException& e) {
		System::out << "Database error in ResourceManagerImplementation::getRandomResourceFromType\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception in ResourceManagerImplementation::getRandomResourceFromType\n";
	}

	return "";
}

void ResourceManagerImplementation::createResource(String restype, String pool, bool jtl) {
	numFunctions++;

	String resname;

	int planets[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int planet, therand, thex, they, numplanets, numspawns;

	ResourceTemplate* resource = new ResourceTemplate(restype);

	generateResourceStats(resource);

	if (resourceMap->get(resource->getName()) != NULL){
		resourceMap->drop(resource->getName());
		info("Resource " + resource->getName() + " already exists in map, removing");
	}

	insertResource(resource);

	if (isPlanetSpecific(resource->getType())) {
		planet = getPlanet(resource->getType());

		if (resource->getClass2() == "Creature Resources") {
			insertSpawn(resource, planet, 0, 0, 0, 0, pool, jtl);
		} else {
			for (int y = 0; y < (System::random(maxspawns - minspawns) + minspawns); y++) {
				thex = System::random(8192 * 2) - 8192;
				they = System::random(8192 * 2) - 8192;

				insertSpawn(resource, planet, thex, they, (System::random(maxradius - minradius) + minradius),
						(System::random(49) + 50), pool, jtl);
			}
		}
	} else {
		numplanets = System::random(resource->getMaxPool() - resource->getMinPool()) + resource->getMinPool();

		for (int x = 0; x < numplanets; x++) {
			for (int z = 0; z < 10; z++) {
				therand = System::random(9);
				planet = planets[therand];

				if (planet != 0) {
					planet--;
					planets[therand] = 0;
					break;
				}
			}

			numspawns = System::random(maxspawns - minspawns) + minspawns;

			for (int y = 0; y < numspawns; y++) {
				thex = System::random(8192 * 2) - 8192;
				they = System::random(8192 * 2) - 8192;

				insertSpawn(resource, planet, thex, they,
						(System::random(maxradius - minradius)+ minradius),
						(System::random(49) + 50), pool, jtl);
			}
		}
	}

	resourceIDNameMap->put(resource->getResourceID(), resource->getName());
	resourceMap->put(resource->getName(), resource);
	addToResourceTree(resource);
}

void ResourceManagerImplementation::generateResourceStats(ResourceTemplate* resource) {
	String resname;

	int stat1, stat2, stat3, stat4, stat5, stat6, stat7, stat8, stat9, stat10, stat11;

	try {
		String query = "SELECT * FROM resource_tree WHERE resource_type = \'" +
		resource->getType() + "\'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			if (res->size() == 1) {
				resource->setClass1(res->getString(2));
				resource->setClass2(res->getString(3));
				resource->setClass3(res->getString(4));
				resource->setClass4(res->getString(5));
				resource->setClass5(res->getString(6));
				resource->setClass6(res->getString(7));
				resource->setClass7(res->getString(8));

				resource->setMaxType(res->getInt(9));
				resource->setMinType(res->getInt(10));
				resource->setMinPool(res->getInt(11));
				resource->setMaxPool(res->getInt(12));

				resource->setAtt1("res_decay_resist");
				resource->setAtt2("res_quality");
				resource->setAtt3("res_flavor");
				resource->setAtt4("res_potential_energy");
				resource->setAtt5("res_malleability");
				resource->setAtt6("res_toughness");
				resource->setAtt7("res_shock_resistance");
				resource->setAtt8("res_cold_resist");
				resource->setAtt9("res_heat_resist");
				resource->setAtt10("res_conductivity");
				resource->setAtt11("entangle_resistance");

				resource->setAtt1Stat(0);
				resource->setAtt2Stat(0);
				resource->setAtt3Stat(0);
				resource->setAtt4Stat(0);
				resource->setAtt5Stat(0);
				resource->setAtt6Stat(0);
				resource->setAtt7Stat(0);
				resource->setAtt8Stat(0);
				resource->setAtt9Stat(0);
				resource->setAtt10Stat(0);
				resource->setAtt11Stat(0);

				stat1 =  randomize(res->getInt(24), res->getInt(25));
				setAttStat(resource, res->getString(13), stat1);

				stat2 =  randomize(res->getInt(26), res->getInt(27));
				setAttStat(resource, res->getString(14), stat2);

				stat3 =  randomize(res->getInt(28), res->getInt(29));
				setAttStat(resource, res->getString(15), stat3);

				stat4 =  randomize(res->getInt(30), res->getInt(31));
				setAttStat(resource, res->getString(16), stat4);

				stat5 =  randomize(res->getInt(32), res->getInt(33));
				setAttStat(resource, res->getString(17), stat5);

				stat6 =  randomize(res->getInt(34), res->getInt(35));
				setAttStat(resource, res->getString(18), stat6);

				stat7 =  randomize(res->getInt(36), res->getInt(37));
				setAttStat(resource, res->getString(19), stat7);

				stat8 =  randomize(res->getInt(38), res->getInt(39));
				setAttStat(resource, res->getString(20), stat8);

				stat9 =  randomize(res->getInt(40), res->getInt(41));
				setAttStat(resource, res->getString(21), stat9);

				stat10 =  randomize(res->getInt(42), res->getInt(43));
				setAttStat(resource, res->getString(22), stat10);

				stat11 =  randomize(res->getInt(44), res->getInt(45));
				setAttStat(resource, res->getString(23), stat11);

				resource->setContainer(res->getString(46));
				resource->setContainerCRC(res->getUnsignedInt(47));

				setObjectSubType(resource);
			} else {
				System::out << "Resource Database error generateResourceStats" << endl;
			}
		}

		makeResourceName(resname, resource->getClass1() == "Organic");

		resource->setName(resname);

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Resource Database error 2 generateResourceStats" << endl;
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::generateResourceStats\n";
	}
}

int ResourceManagerImplementation::randomize(int min, int max) {
	if (min == 0 && max == 0)
		return 0;

	float num = System::random(int(spawnThrottling + (.1f * spawnThrottling)));
	float realPercentage = num / float(spawnThrottling + (.1f * spawnThrottling));

	int value = int(float((max - min) * realPercentage) + min);

	/*if (realPercentage > 0)
		System::out << "Value = " << value << "  Min = " << min << "  Max = " << max << "  realPercentage = " << realPercentage << "  Percentage = " << num << endl;

	if (num > spawnThrottling)
		tempOver++;
	else
		tempUnder++;*/

	return value;
}

void ResourceManagerImplementation::setAttStat(ResourceTemplate* resource, String statTitle, int stat){
	if (statTitle == "res_decay_resist") {
		resource->setAtt1Stat(stat);
		return;
	}

	if (statTitle == "res_quality") {
		resource->setAtt2Stat(stat);
		return;
	}

	if (statTitle == "res_flavor") {
		resource->setAtt3Stat(stat);
		return;
	}

	if (statTitle == "res_potential_energy") {
		resource->setAtt4Stat(stat);
		return;
	}

	if (statTitle == "res_malleability") {
		resource->setAtt5Stat(stat);
		return;
	}

	if (statTitle == "res_toughness") {
		resource->setAtt6Stat(stat);
		return;
	}

	if (statTitle == "res_shock_resistance") {
		resource->setAtt7Stat(stat);
		return;
	}

	if (statTitle == "res_cold_resist") {
		resource->setAtt8Stat(stat);
		return;
	}

	if (statTitle == "res_heat_resist") {
		resource->setAtt9Stat(stat);
		return;
	}

	if (statTitle == "res_conductivity") {
		resource->setAtt10Stat(stat);
		return;
	}

	if (statTitle == "entangle_resistance") {
		resource->setAtt11Stat(stat);
		return;
	}

	if (statTitle != "")
		info("Something screwed up in finding stats to set in setAttStat: |" + statTitle + "| doesn't match");
}

void ResourceManagerImplementation::makeResourceTree() {
	numFunctions++;

	try {
		resourceTree = new ClassMap();
		String root = "root";
		resourceTree->setClassName(root);

		for (int i=0; i<resourceMap->size(); i++){
			ResourceTemplate* resTemp = resourceMap->get(i);

			resourceTree->addResource(resTemp);
		}

		//String class1 = "Inorganic";
		//Vector<String>* classes = resourceTree->getResourcesFromClass(class1);
		//for (int i=0; i<classes->size(); i++){
		//	System::out << classes->get(i) << endl;
		//}

	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::makeResourceTree()\n";
	}
}

void ResourceManagerImplementation::addToResourceTree(ResourceTemplate* resource){
	numFunctions++;

	try{

		resourceTree->addResource(resource);

	} catch (...){
		System::out << "unreported exception caught in ResourceManagerImplementation::addToResourceTree()\n";
	}
}

void ResourceManagerImplementation::makeMinimumPoolVector() {
	numFunctions++;

	try {
		minimumpool = new Vector<String>;
		minimumpool->add("Steel");
		minimumpool->add("Copper");
		minimumpool->add("Aluminum");
		minimumpool->add("Extrusive Ore");
		minimumpool->add("Intrusive Ore");
		minimumpool->add("Carbonate Ore");
		minimumpool->add("Crystalline Gemstone");
		minimumpool->add("Amorphous Gemstone");
		minimumpool->add("Known Radioactive");
		minimumpool->add("Solid Petrochem Fuel");
		minimumpool->add("Liquid Petrochem Fuel");
		minimumpool->add("Polymer");
		minimumpool->add("Polymer");
		minimumpool->add("Lubricating Oil");
		minimumpool->add("Lubricating Oil");
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::makeMinimumPoolVector()\n";
	}
}

void ResourceManagerImplementation::makeFixedPoolVector() {
	numFunctions++;

	fixedpool = new Vector<String>;
	fixedpool->add("steel_arveshian");
	fixedpool->add("steel_bicorbantium");
	fixedpool->add("copper_borocarbitic");
	fixedpool->add("ore_siliclastic_fermionic");
	fixedpool->add("aluminum_perovskitic");
	fixedpool->add("gas_reactive_organometallic");
	fixedpool->add("fiberplast_gravitonic");
	fixedpool->add("radioactive_polymetric");
}

void ResourceManagerImplementation::makeNativePoolVector() {
	numFunctions++;

	try {
		nativepool = new Vector<String>;

		numQueries++;

		StringBuffer query;
		query << "SELECT `resource_type` "
		<< "FROM `resource_tree` "
		<< "WHERE (class_1 = 'Organic' OR "
		<< "class_3 = 'Fiberplast' OR "
		<< "class_2 = 'Wind Energy' OR "
		<< "class_2 = 'Solar Energy' OR "
		<< "class_2 = 'Water') AND class_6 != 'JTL'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		String temp;

		while (res->next()) {
			nativepool->add(res->getString(0));
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in makeNativePoolVector\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::makeNativePoolVector()\n";
	}
}
bool ResourceManagerImplementation::isPlanetSpecific(const String type) {
	numFunctions++;

	if ((type.indexOf("corellia") == -1) && (type.indexOf("dantooine") == -1)
			&& (type.indexOf("yavin4") == -1) && (type.indexOf("dathomir") == -1)
			&& (type.indexOf("endor") == -1) && (type.indexOf("lok") == -1)
			&& (type.indexOf("naboo") == -1) && (type.indexOf("rori") == -1)
			&& (type.indexOf("talus") == -1) && (type.indexOf("tatooine") == -1))
		return false;
	else
		return true;
}
int ResourceManagerImplementation::getPlanet(const String type) {
	numFunctions++;

	if (type.indexOf("corellia") != -1)
		return 0;

	if (type.indexOf("dantooine") != -1)
		return 1;

	if (type.indexOf("dathomir") != -1)
		return 2;

	if (type.indexOf("endor") != -1)
		return 3;

	if (type.indexOf("lok") != -1)
		return 4;

	if (type.indexOf("naboo") != -1)
		return 5;

	if (type.indexOf("rori") != -1)
		return 6;

	if (type.indexOf("talus") != -1)
		return 7;

	if (type.indexOf("tatooine") != -1)
		return 8;

	if (type.indexOf("yavin4") != -1)
		return 9;

	return 99;
}
bool ResourceManagerImplementation::isType(ResourceTemplate* resource, String type) {
	numFunctions++;

	if (resource->getClass1() == type || resource->getClass2() == type
			|| resource->getClass3() == type || resource->getClass4() == type
			|| resource->getClass5() == type || resource->getClass6() == type
			|| resource->getClass7() == type)
		return true;
	else
		return false;
}

void ResourceManagerImplementation::insertResource(ResourceTemplate* resource) {
	numFunctions++;

	try {
		StringBuffer query;
		query << "INSERT INTO `resource_data` "
		<< "(`resource_name`,`resource_type`,`class_1`,"
		<< "`class_2`,`class_3`,`class_4`,"
		<< "`class_5`,`class_6`,`class_7`"
		<< checkInsertCategory(resource->getAtt1())
		<< checkInsertCategory(resource->getAtt2())
		<< checkInsertCategory(resource->getAtt3())
		<< checkInsertCategory(resource->getAtt4())
		<< checkInsertCategory(resource->getAtt5())
		<< checkInsertCategory(resource->getAtt6())
		<< checkInsertCategory(resource->getAtt7())
		<< checkInsertCategory(resource->getAtt8())
		<< checkInsertCategory(resource->getAtt9())
		<< checkInsertCategory(resource->getAtt10())
		<< checkInsertCategory(resource->getAtt11())
		<< ",`shiftedIn`,`container`, `containerCRC`)"
		<< " VALUES ('"
		<< resource->getName() << "','" << resource->getType() << "','"
		<< resource->getClass1() << "','" << resource->getClass2() << "','"
		<< resource->getClass3() << "','" << resource->getClass4() << "','"
		<< resource->getClass5() << "','" << resource->getClass6() << "','"
		<< resource->getClass7() << "'"
		<< checkInsertValue(resource->getAtt1Stat())
		<< checkInsertValue(resource->getAtt2Stat())
		<< checkInsertValue(resource->getAtt3Stat())
		<< checkInsertValue(resource->getAtt4Stat())
		<< checkInsertValue(resource->getAtt5Stat())
		<< checkInsertValue(resource->getAtt6Stat())
		<< checkInsertValue(resource->getAtt7Stat())
		<< checkInsertValue(resource->getAtt8Stat())
		<< checkInsertValue(resource->getAtt9Stat())
		<< checkInsertValue(resource->getAtt10Stat())
		<< checkInsertValue(resource->getAtt11Stat())
		<< ", " << (long)time(0) << ",'" << resource->getContainer()
		<< "'," << resource->getContainerCRC() << ")";

		ServerDatabase::instance()->executeStatement(query.toString());

		numInsert++;
	} catch (DatabaseException& e) {
		System::out << "Insert Resource Failed " << endl;
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::insertResource(ResourceTemplate* resource)" << endl;
	}
}
void ResourceManagerImplementation::insertSpawn(ResourceTemplate* resource, int planet_id,
		float x, float y, float radius, float max, String pool, bool& jtl) {
	numFunctions++;

	try {
		int upper, lower;

		if (resource->getClass1() == "Organic") {
			upper = 22;
			lower = 6;
		} else {
			if (jtl) {
				upper = 22;
				lower = 13;
			} else {
				upper = 11;
				lower = 6;
			}
		}

		long despawn = (long)time(0) + (System::random((aveduration * upper)-(aveduration * lower)))
		+ (aveduration* lower);

		StringBuffer query;
		query << "INSERT INTO `resource_spawns` "
		<< "(`resource_name`, `planet_id`,"
		<< "`x`,`y`,`radius`,"
		<< "`max`,`despawn`,`pool`)"
		<< " VALUES ('"
		<< resource->getName() << "'," << planet_id << ","
		<< x << "," << y << ","<< radius
		<< "," << max << "," << despawn << ",'" << pool << "')";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		uint64 id = res->getLastAffectedRow();

		SpawnLocation* sl = new SpawnLocation(id, planet_id, x, y, radius, max, despawn, pool);

		resource->addSpawn(sl);

		delete res;

		numInsert++;
	} catch (DatabaseException& e) {
		System::out << "Insert Spawn Failed " << endl;
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::insertSpawn" << endl;
	}
}

inline String ResourceManagerImplementation::checkInsertCategory(String inString) {
	numFunctions++;

	if (inString == "") {
		return "";
	} else {
		return ",`" + inString + "`";
	}
}

inline String ResourceManagerImplementation::checkInsertValue(int inval) {
	numFunctions++;

	if (inval == 0) {
		return ", 0";
	} else {
		return ", " + String::valueOf(inval);// + "`";
	}
}

void ResourceManagerImplementation::makeResourceName(String& resname, bool isOrganic) {
	numNameFunctions++;
	String randname;

	while (true) {
		randname = serv->getNameManager()->makeResourceName(isOrganic);

		if (checkResourceName(randname))
			break;
	}

	resname = randname;
}

bool ResourceManagerImplementation::checkResourceName(const String inString) {
	try {
		numFunctions++;

		StringBuffer query;
		query << "SELECT * from `resource_data` WHERE resource_name = \'" + inString + "\'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		numQueries++;

		int size = res->size();

		delete res;

		if (size == 0) {
			return true;
		} else {
			//System::out << "Duplicate Name, OMG?!?!" << endl;
			return false;
		}
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << endl;
		return false;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManageR::checkResourceName\n";
		return false;
	}

	return false;
}


bool ResourceManagerImplementation::isDumbPhrase(const String inname) {
	/*if ((inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("riy") == String::npos) &&
			(inname.find("anal") == String::npos))
		return true;
	else*/
	return false;
}

void ResourceManagerImplementation::setObjectSubType(ResourceTemplate* resImpl) {
	if (resImpl->getClass1() == "Inorganic") {
		if (resImpl->getClass2() == "Mineral") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICMINERAL);
			return;
		} else if (resImpl->getClass2() == "Chemical") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICCHEMICAL);
			return;
		} else if (resImpl->getClass2() == "Gas") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICGAS);
			return;
		} else if (resImpl->getClass2() == "Water") {
			resImpl->setObjectSubType(TangibleObjectImplementation::WATER);
			return;
		}
	} else if (resImpl->getClass1() == "Organic") {
		if (resImpl->getClass3() == "Flora Food") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICFOOD);
			return;
		} else if (resImpl->getClass3() == "Flora Structural") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICSTRUCTURAL);
			return;
		} else if (resImpl->getClass3() == "Creature Food") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICFOOD);
			return;
		} else if (resImpl->getClass3() == "Creature Structural") {
			if (resImpl->getClass4() == "Bone") {
				resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICSTRUCTURAL);
				return;
			} else if (resImpl->getClass4() == "Hide") {
				resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICHIDE);
				return;
			} else if (resImpl->getClass4() == "Horn") {
				resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICSTRUCTURAL);
				return;
			}
		}
	} else if (resImpl->getClass1() == "Energy") {
		if (resImpl->getClass2() == "Wind Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYLIQUID);
			return;
		} else if (resImpl->getClass2() == "Solar Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYLIQUID);
			return;
		} else if (resImpl->getClass2() == "Radioactive Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYRADIOACTIVE);
			return;
		}
	}
	info("Couldn't pick class for " + resImpl->getName());
	//resImpl->toString();

}

String& ResourceManagerImplementation::getResourceNameByID(uint64 rID) {
	if (resourceIDNameMap != NULL)
		return resourceIDNameMap->get(rID);

	return EMPTY;
}

void ResourceManagerImplementation::printResource(String name){
	lock();

	String resname;
	String query = "SELECT * FROM resource_data WHERE `resource_name` = '" +
	name + "'";
	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->size() == 1) {
			while (res->next()) {
				System::out << "Name = " << res->getString(1)<< "\n";
				System::out << "Type = " << res->getString(2) << "\n";
				System::out << "ID = " << res->getUnsignedLong(0) << "\n";
				System::out << "Class1 = " << res->getString(3) << "\n";
				System::out << "Class2 = " << res->getString(4) << "\n";
				System::out << "Class3 = " << res->getString(5) << "\n";
				System::out << "Class4 = " << res->getString(6) << "\n";
				System::out << "Class5 = " << res->getString(7) << "\n";
				System::out << "Class6 = " << res->getString(8) << "\n";
				System::out << "Class7 = " << res->getString(9) << "\n";
				System::out << "Decay Stat = " << res->getInt(10) << "\n";
				System::out << "Quality Stat = " << res->getInt(11) << "\n";
				System::out << "Flavor Stat = " << res->getInt(12) << "\n";
				System::out << "PE Stat = " << res->getInt(13) << "\n";
				System::out << "ME Stat = " << res->getInt(14) << "\n";
				System::out << "Toughness Stat = " << res->getInt(15) << "\n";
				System::out << "SR Stat = " << res->getInt(16) << "\n";
				System::out << "CR Stat = " << res->getInt(17) << "\n";
				System::out << "HR Stat = " << res->getInt(18) << "\n";
				System::out << "CD Stat = " << res->getInt(19) << "\n";
				System::out << "ER Stat = " << res->getInt(20) << "\n";
				System::out << "Container = " << res->getString(23) << "\n";
				System::out << "Bad CRC = " << res->getUnsignedInt(24) << "\n";
			}
		} else
			System::out << "Multiple Resource with name: Size = " << res->size() << "\n";

		delete res;
	} catch (DatabaseException& e) {
		System::out << "Database error in verifyMap\n";
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in ResourceManagerImplementation::printResource\n";
	}
}

void ResourceManagerImplementation::giveForageResource(Player* player, float foragex, float foragey, int forageplanet){
	ResourceList* resList;
	ResourceItem* resItem;
	String resName;
	int resQuantity = 14 + System::random(4);
	bool giveBackupResource = false;

	//Find resources near the player and randomly pick one.
    if (forageResource == true) { //Give flora resource.
    	resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::FLORA);

	    if (resList->size() > 0) { //Make sure there is a resource of this type near the player.
		    resItem = resList->get(System::random(resList->size() - 1));
		    resName = resItem->getName();
	    } else {
		    giveBackupResource = true; //No resources of this type, try to give something else.
	    }
	    forageResource = false;

    } else { //Give inorganic resource.
       switch (System::random(3)) {
          case 0:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::MINERAL);
    	      break;
          case 1:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::CHEMICAL);
    	      break;
          case 2:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::GAS);
    	      break;
          case 3:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::WATER);
    	      break;
       }
       if (resList->size() > 0) { //Make sure there is a resource of this type near the player.
    	   resItem = resList->get(System::random(resList->size() - 1));
    	   resName = resItem->getName();
       } else {
		   giveBackupResource = true; //No resources of this type, try to give something else.
       }
       forageResource = true;
    }

    //If there are no resources of the randomly selected type, give a different resource.
    if (giveBackupResource == true) { //Failed to find a resource of the type they were randomly selected to get.
       switch (0) {
    	  case 0:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::MINERAL);
    	      if (resList->size() > 0)
    	    	  break;
    	  case 1:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::CHEMICAL);
    	      if (resList->size() > 0)
    	          break;
    	  case 2:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::GAS);
    	      if (resList->size() > 0)
    	           break;
    	  case 3:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::WATER);
    	      if (resList->size() > 0)
    	          break;
    	  case 4:
    	      resList = getResourceListAtLocation(forageplanet, foragex, foragey, ResourceHarvestType::FLORA);
    	      if (resList->size() > 0)
    	      	 break;
       }
       if (resList->size() > 0) {
    	   resItem = resList->get(System::random(resList->size() - 1));
    	   resName = resItem->getName();
       }
    }

    //Give player the resource.
    if (resList->size() > 0) {
    	ResourceContainer* newRcno = createNewResourceContainer(player, resName, resQuantity);
    	player->addInventoryResource(newRcno);
    }
}
