/*
 *	ResourceManagerImplementationStub
 */
#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "events/SpawnResourcesEvent.h"

#include "ResourceManager.h"
#include "ResourceManagerImplementation.h"

#include "../name/NameManager.h"

#include "../../objects/tangible/resource/ResourceContainerImplementation.h"
#include "../../objects/tangible/surveytool/SurveyToolImplementation.h"

#include "../../packets.h"

ResourceManagerImplementation::ResourceManagerImplementation(ZoneServer* inserver, 
		ZoneProcessServerImplementation* inserv) : ResourceManagerServant(), Logger("ResourceManager"), Mutex("ResourceManager") {
	init();
	
	serv = inserv;

	spawnResourcesEvent = new SpawnResourcesEvent(this);
	serv->addEvent(spawnResourcesEvent, 1000);
	//  This dictates the first time the spawner will run
	//  Spawner does take a good bit of time to populate an
	//  Empty database.
	
	setLogging(false);
	setGlobalLogging(true);
	
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
}


void ResourceManagerImplementation::init() {
	resourceMap = new VectorMap<string, ResourceTemplate*>();
	resourceMap->setNullValue(NULL);
	
	buildResourceMap();
	
	info("resources built from database.");
	
	averageShiftTime = 3 * 3600000; // In milliseconds
	//  This is the time between each time the Resource Manager schedules
	//  itself to run again.  
	//  *** Default is 1 hour (3600000) ***
	//  *** Good testing time is (15000) ***
	
	aveduration = 86400;  // In seconds
	// This is the modifier for how long spawns are in shift
	// Organics are in shift between (6 * aveduration) and  (22 * aveduration)
	// Inorganics are in shift between (6 * aveduration) and (11 * aveduration)
	// JTL resources are in shift between (13 * aveduration) and (22 * aveduration)
	//  *** Default is 1 day (86400) ***
	//  *** Good testing period is (40) ***
	
	maxspawns = 40;  //  Mmaximum number of spawns per planet
	minspawns = 25;  //  Minimum number of spawns per planet
	maxradius = 2000;   //  Maximum Spawn radius of resource on map
	minradius = 400;    //  Minimum Spawn radius of resource on map
	
	makeMinimumPoolVector();
	makeFixedPoolVector();
	makeNativePoolVector();
}

void ResourceManagerImplementation::stop() {
	lock();
	
	if (spawnResourcesEvent->isQueued())
		serv->removeEvent(spawnResourcesEvent);
	
	for (int i = 0; i < resourceMap->size(); ++i)
		delete resourceMap->get(i);
	
	resourceMap->removeAll();
	
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

	info("starting resource spawner");

	removeExpiredResources();

	checkMinimumPool();
	checkRandomPool();
	checkFixedPool();
	checkNativePool();

	info("Queries run = " + stringify(numQueries));
	info("Insert Queries run = " + stringify(numInsert));
	info("Functions run = " + stringify(numFunctions));
	info("Name functions run = " + stringify(numNameFunctions));
	
	countResources();
	
	info("resource Spawner Finished");
	
	serv->addEvent(spawnResourcesEvent, averageShiftTime);
	unlock();
}

void ResourceManagerImplementation::countResources() {  
	// This method pure supports out for the above method, is purely cosmetic
	try {
		stringstream query, query2, query3, query4;
		
		query << "SELECT DISTINCT resource_name FROM resource_spawns"
			  << " WHERE pool = 'minimum'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		info("Minimum Pool has " + stringify(res->size()) + "/15 resources");
		delete res;
		
		query2 << "SELECT DISTINCT resource_name FROM resource_spawns"
			   << " WHERE pool = 'random'";

		res = ServerDatabase::instance()->executeQuery(query2);
		
		info("Random Pool has " + stringify(res->size()) + "/24 resources");
		delete res;

		query3 << "SELECT DISTINCT resource_name FROM resource_spawns"
			   << " WHERE pool = 'fixed'";

		res = ServerDatabase::instance()->executeQuery(query3);
		
		info("Fixed Pool has " + stringify(res->size()) + "/22 resources");
		delete res;

		query4 << "SELECT DISTINCT resource_name FROM resource_spawns"
			   << " WHERE pool = 'native'";

		res = ServerDatabase::instance()->executeQuery(query4);
		
		info("Native Pool has " + stringify(res->size()) + "/420 resources");
		delete res;
		
		info("*** Extra resources expected ***");
	} catch(...) {
		cout << "Error in ResourceManagerImplementation::countResources()\n";
	}
}

void ResourceManagerImplementation::clearResources() {
	lock();
	try {
		numFunctions++;
		
		stringstream query;
		query << "TRUNCATE TABLE `resource_spawns`;";
		query << "TRUNCATE TABLE `resource_data`;";
		
		ServerDatabase::instance()->executeStatement(query);
		
		numQueries++;
	} catch (...) {
		cout << "Error in clearResources\n";
	}
	unlock();
}

float ResourceManagerImplementation::getDensity(int planet, string& resname, float inx, float iny) {
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
				
				if (inx > (x - radius) && inx < (x + radius) && iny > (y - radius) && iny < (y + radius)) {
					distance = sqrt(((inx - x) * (inx - x)) 
							+ ((iny - y) * (iny - y)));

					density = ((((radius - distance) / radius) * source) / 100.0f);
					
					if (density > max_density)
						max_density = density;
				}
			}
		}
	} catch (...) {
		cout << "Database error in getDensity\n";
	}
	
	return max_density;
}

void ResourceManagerImplementation::sendSurveyMessage(Player* player, string& resourceName, bool doLock) {
	// Added by Ritter
	if (player->getSurveyTool() == NULL)
		return;
		
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
			
			if (res_percent > max_res_percent) {
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
		unicode ustr = "";
		ChatSystemMessage* endMessage = new ChatSystemMessage("survey", "survey_waypoint", ustr, 0, true);
		
		player->sendMessage(endMessage);
	}
	unlock(doLock);
}

void ResourceManagerImplementation::sendSampleMessage(Player* player, string& resourceName, bool doLock) {
	// Added by Ritter
	lock(doLock);
	
	float density = getDensity(player->getZoneIndex(), resourceName, player->getPositionX(), player->getPositionY());
	
	if (density < 0.1f) {
		ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "density_below_threshold", resourceName, 0, false);
		
		player->sendMessage(sysMessage);
		
		player->changePosture(CreatureObjectImplementation::UPRIGHT_POSTURE);
	} else {
		if (player->getSurveyTool() == NULL) {
			unlock(doLock);
			return;
		}
			
		int sampleRate = System::random(1000) + (5 * player->getSkillMod("surveying"));
		
		if (sampleRate >= 650) {
			int resQuantity = (sampleRate / 100) * 2 - System::random(13);
			
			if (!(resQuantity > 0))
				resQuantity = 1;
			
			player->getSurveyTool()->sendSampleEffect(player);
			
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_located", resourceName, resQuantity, false);
			player->sendMessage(sysMessage);
			
			bool makeNewResource = true;

			Inventory* inventory = player->getInventory();
			
			ResourceContainer* rco;
			
			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);
				if (item != NULL && item->isResource() && strcmp(((ResourceContainer*)item)->getResourceName().c_str(), resourceName.c_str()) == 0) {
					rco = (ResourceContainer*) item;
					
					if (rco->getContents() + resQuantity <= rco->getMaxContents()) {
						rco->setContents(rco->getContents() + resQuantity);
						rco->sendDeltas(player);
						
						rco->setUpdated(true);
						
						resQuantity = 0;
						
						makeNewResource = false;
						break;
					} else if (rco->getContents() < rco->getMaxContents()) {
						int diff = (rco->getMaxContents() - rco->getContents());
						
						if (resQuantity <= diff) {
							rco->setContents(rco->getContents() + resQuantity);
						} else {
							rco->setContents(rco->getContents() + diff);
							resQuantity = resQuantity - diff;
						}
						
						rco->sendDeltas(player);
						
						rco->setUpdated(true);
					}
				}
			}
			
			if (makeNewResource) {
				// NOTE: Figure out how to get max inventory size...
				if (inventory->getObjectCount() >= 80) {
					ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "no_inv_spc");
					player->sendMessage(sysMessage);
					unlock(doLock);
					return;
				}
				
				rco = new ResourceContainer(player->getNewItemID());

				string contName;
				getResourceContainerName(resourceName, contName, false);
				
				unicode cName = unicode(contName.c_str());
				rco->setName(cName);
				rco->setResourceName(resourceName);
				rco->setContents(resQuantity);
				
				setResourceData(rco, false);
				
				player->addInventoryItem(rco);
				
				rco->sendTo(player);
				
				rco->setPersistent(false);
			}
			
			if (rco->getObjectSubType() == TangibleObjectImplementation::ENERGYRADIOACTIVE) {
				int wound = (sampleRate / 70) - System::random(9);
				if (wound > 0) {
					player->changeHealthWoundsBar(wound, false);
					player->changeActionWoundsBar(wound, false);
					player->changeMindWoundsBar(wound, false);
				}
			}
			
		} else {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_failed", resourceName, 0, false);
			
			player->getSurveyTool()->sendSampleEffect(player);
			
			player->sendMessage(sysMessage);
		}
	}
	
	unlock(doLock);
}

void ResourceManagerImplementation::setResourceData(ResourceContainer* resContainer, bool doLock) {
	// Added by Ritter
	lock(doLock);
	
	string resourceName = resContainer->getResourceName().c_str();
	ResourceTemplate* resource = resourceMap->get(resourceName);
	
	if (resource == NULL) {
		unlock(doLock);
		return;
	}

	string contName;
	getResourceContainerName(resourceName, contName, false);
	unicode cName = unicode(contName.c_str());
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
	
	unlock(doLock);
}

bool ResourceManagerImplementation::checkResource(Player* player, string& resourceName, int SurveyToolType, bool doLock) {
	// Added by Ritter
	
	lock(doLock);
	
	ResourceTemplate* resource = resourceMap->get(resourceName);
	
	string surveyType, class2, class2re = "";
	switch(SurveyToolType) {
	case SurveyToolImplementation::SOLAR:
		class2 = "Solar Energy";
		break;
	case SurveyToolImplementation::CHEMICAL:
		class2 = "Chemical";
		break;
	case SurveyToolImplementation::FLORA:
		class2 = "Flora";
		break;
	case SurveyToolImplementation::GAS:
		class2 = "Gas";
		break;
	case SurveyToolImplementation::GEOTHERMAL:
		class2 = "Geothermal Energy";
		break;
	case SurveyToolImplementation::MINERAL:
		class2 = "Mineral";
		class2re = "Radioactive Energy";
		break;
	case SurveyToolImplementation::WATER:
		class2 = "Water";
		break;
	case SurveyToolImplementation::WIND:
		class2 = "Wind Energy";
		break;
	default:
		player->error("Invalid Tool");
		unlock(doLock);
		return false;
	}
	
	if (resource != NULL) {
		if (strcmp(resource->getClass2().c_str(), class2.c_str()) == 0 || strcmp(resource->getClass2().c_str(), class2re.c_str()) == 0) {		
			for(int i = resource->getSpawnSize() - 1; i >= 0; i--) {
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
	Vector<string>* resourceList = new Vector<string>();
	
	string surveyType, class2, class2re = "";
	switch(SurveyToolType) {
	case SurveyToolImplementation::SOLAR:
		class2 = "Solar Energy";
		surveyType = "energy_renewable_unlimited_solar";
		break;
	case SurveyToolImplementation::CHEMICAL:
		class2 = "Chemical";
		surveyType = "chemical";
		break;
	case SurveyToolImplementation::FLORA:
		class2 = "Flora";
		surveyType = "flora_resources";
		break;
	case SurveyToolImplementation::GAS:
		class2 = "Gas";
		surveyType = "gas";
		break;
	case SurveyToolImplementation::GEOTHERMAL:
		class2 = "Geothermal Energy";
		surveyType = "enegy_renewable_site_limited_geothermal";
		break;
	case SurveyToolImplementation::MINERAL:
		class2 = "Mineral";
		class2re = "Radioactive Energy";
		surveyType = "mineral";
		break;
	case SurveyToolImplementation::WATER:
		class2 = "Water";
		surveyType = "water";
		break;
	case SurveyToolImplementation::WIND:
		class2 = "Wind Energy";
		surveyType = "enegy_renewable_unlimited_wind";
		break;
	default:
		player->error("Invalid Tool");
		delete resourceList;
		unlock(doLock);
		return false;
	}
	
	ResourceListForSurvey* packet = new ResourceListForSurvey();
	
	ResourceTemplate* resource;

	for(int i = resourceMap->size() - 1; i > 0; i--) {
		resource = resourceMap->get(i);
		if (resource->getSpawnSize() > 0 && (strcmp(resource->getClass2().c_str(), class2.c_str()) == 0 || strcmp(resource->getClass2().c_str(), class2re.c_str()) == 0)) {
			for(int i = resource->getSpawnSize() - 1; i >= 0; i--) {
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

void ResourceManagerImplementation::sendSurveyResourceStats(Player* player, Vector<string>* rList) {
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

void ResourceManagerImplementation::getClassSeven(const string& resource, string& clas, bool doLock) {
	lock(doLock);
	
	ResourceTemplate* resTemp = resourceMap->get(resource);
	
	if (resTemp != NULL)
		clas = resTemp->getClass7();
		
	unlock(doLock);
}

void ResourceManagerImplementation::getResourceContainerName(const string& resource, string& name, bool doLock) {
	lock(doLock);
	
	ResourceTemplate* resTemp = resourceMap->get(resource);
	
	if (resTemp != NULL)
		if ( resTemp->getClass6() != "" )
			name = resTemp->getClass6();
		else if ( resTemp->getClass5() != "" )
			name = resTemp->getClass5();
		else if ( resTemp->getClass4() != "" )
			name = resTemp->getClass4();
		else if ( resTemp->getClass3() != "" )
			name = resTemp->getClass3();
		else if ( resTemp->getClass2() != "" )
			name = resTemp->getClass2();
		else if ( resTemp->getClass1() != "" )
			name = resTemp->getClass1();
			
	unlock(doLock);
}

bool ResourceManagerImplementation::isDuplicate(Vector<string>* rList, string& resource) {
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
	string resname;
	string query = "SELECT * FROM resource_data";
	
	try {
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		if (res->size() != 0) {
			while (res->next()) {
				resname = res->getString(1);
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
				resTemp->setAtt7("res_shockresistance");
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
				
				stringstream query2;
				query2 << "SELECT * FROM resource_spawns WHERE `resource_name` = '" << resname << "'";
				ResultSet* res2 = ServerDatabase::instance()->executeQuery(query2);
				if (res2->size() != 0) {
					while (res2->next()) {
						string pool = res2->getString(8);
						SpawnLocation* sl = new SpawnLocation(res2->getUnsignedLong(0), res2->getInt(2), res2->getFloat(3), res2->getFloat(4), res2->getFloat(5), res2->getFloat(6), pool);
						resTemp->addSpawn(sl);
					}
				}
				delete res2;
				resourceMap->put(resname, resTemp);
			}
		}
		delete res;
	} catch (DatabaseException& e) {
		cout << "Database error in buildMap\n";
	}
}

void ResourceManagerImplementation::removeExpiredResources() {
	try {
		numFunctions++;

		stringstream query, query2, query3;
		uint64 now = time(0);
		
		query << "SELECT `INDEX`, `resource_name` FROM resource_spawns WHERE despawn < " << now;
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		if (res->size() != 0) {
			while (res->next()) {
				uint64 sid = res->getUnsignedLong(0);
				string rname = res->getString(1);
				ResourceTemplate* resource = resourceMap->get(rname);
				if (resource != NULL) {
					SpawnLocation* sl = resource->removeSpawn(sid);
				} else {
					info("Error removing spawn location.");
				}
			}
		
			stringstream ss;
			ss << "Resources to be despawned: " << res->size();
			info(ss.str());
			
			delete res;
			
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
		numQueries++;
	} catch (...) {
		cout << "Database error in removeExpiredResources\n";
	}
}

void ResourceManagerImplementation::checkMinimumPool() {
	numFunctions++;
	
	string restype;
	string exclusion = "";
	
	Vector<string> spawnMe;

	poolNeeds(minimumpool, "minimum", &spawnMe);

	info("Minimum pool spawns = " + stringify(spawnMe.size()));

	getFromRandomPool(&spawnMe, "minimum");

	for (int x = 0; x < spawnMe.size(); x++) {
		restype = getRandomResourceFromType(spawnMe.get(x), exclusion);
		createResource(restype, "minimum", false);
	}
}

void ResourceManagerImplementation::checkRandomPool() {
	numFunctions++;
	
	string restype;
	string exclusion = " AND (class_1 != 'Organic' and class_5 != 'Iron' and class_3 != 'Fiberplast')";
	string type = "Inorganic";

	int spawnMe = randomPoolNeeds();

	info("Random pool spawns = " + stringify(spawnMe));

	for (int x = 0; x < spawnMe; x++) {
		restype = getRandomResourceFromType(type, exclusion);
		createResource(restype, "random", false);
	}
}

int ResourceManagerImplementation::randomPoolNeeds() {
	stringstream query;
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
	
	string restype;
	int ironCount = fixedPoolIron();
	
	info("Fixed pool iron spawns = " + stringify(ironCount));

	for (int x = 0; x < ironCount; x++) {
		restype = getRandomResourceFromType(string("Iron"),	string(" AND class_2 != 'Energy'"));
		createResource(restype, "fixed", false);
	}

	Vector<string> spawnMe;

	poolNeeds(fixedpool, "fixed", &spawnMe);
	
	info("Fixed pool JTL spawns = " + stringify(spawnMe.size()));

	for (int x = 0; x < spawnMe.size(); x++) {
		createResource(spawnMe.get(x), "fixed", true);
	}
}

int ResourceManagerImplementation::fixedPoolIron() {
	numFunctions++;
	
	stringstream query;
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
	
	string restype;
	string exclusion = " AND (class_1 = 'Organic')";
	string type = "Organic";
	
	Vector<string> spawnMe;

	poolNeeds(nativepool, "native", &spawnMe);

	info("Native pool spawns = " + stringify(spawnMe.size()));

	getFromRandomPool(&spawnMe, "native");
	
	for (int x = 0; x < spawnMe.size(); x++) {
		//cout << spawnMe[x] << endl;
		createResource(spawnMe.get(x), "native", false);
	}
}

void ResourceManagerImplementation::poolNeeds(Vector<string>* invector, string pool, Vector<string>* needs) {
	try {
		numFunctions++;
		
		stringstream query;

		Vector<string> has;
		
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
			for(int y = 0; y < has.size(); y++) {

				if(has.get(y) == invector->get(x)) {

					hasItem = true;
					break;

				}
			}
			
			if(!hasItem) {
				needs->add(invector->get(x));
			}
		}
		delete res;
	} catch (...) {
		cout << "Database error in poolNeeds\n";
	}
}

void ResourceManagerImplementation::getFromRandomPool(Vector<string> * spawnMe,	string pool) {
	numFunctions++;
	
	for (int x = 0; x < spawnMe->size(); x++) {
		if (pool != "native" || (spawnMe->get(x).find("water") != string::npos)) {
			try {
				stringstream query, query2;

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
					string resname = res->getString(0);

					query2 << "UPDATE resource_spawns "
						   << "SET pool = '" << pool << "' "
						   << "WHERE resource_name = '" << resname << "'";

					numQueries++;

					ServerDatabase::instance()->executeStatement(query2);

					spawnMe->remove(x);
					x--;
				}
				
				delete res;
			} catch (...) {
				cout << "Database error in getFromRandomPool\n";
				break;
			}
		}
	}
}

string ResourceManagerImplementation::getRandomResourceFromType(string restype, string exclusion) {
	numFunctions++;
	
	try {
		string outtype = "";
		
		stringstream query;
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
		
	} catch (...) {
		cout << "Database error in getRandomResourceFromType\n";
	}
	
	return "";
}

void ResourceManagerImplementation::createResource(string restype, string pool, bool jtl) {
	numFunctions++;
	
	string resname;
	
	int planets[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	int planet, therand, thex, they, numplanets, numspawns;

	ResourceTemplate* resource = new ResourceTemplate(restype);

	generateResourceStats(resource);

	insertResource(resource);

	if (isPlanetSpecific(resource->getType())) {
		planet = getPlanet(resource->getType());

		if (resource->getClass2()== "Creature Resources") {
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
	resourceMap->put(resource->getName(), resource);
}

void ResourceManagerImplementation::generateResourceStats(ResourceTemplate* resource) {
	string resname;

	try {
		string query = "SELECT * FROM resource_tree WHERE resource_type = \'" +
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

				resource->setAtt1(res->getString(13));
				resource->setAtt2(res->getString(14));
				resource->setAtt3(res->getString(15));
				resource->setAtt4(res->getString(16));
				resource->setAtt5(res->getString(17));
				resource->setAtt6(res->getString(18));
				resource->setAtt7(res->getString(19));
				resource->setAtt8(res->getString(20));
				resource->setAtt9(res->getString(21));
				resource->setAtt10(res->getString(22));
				resource->setAtt11(res->getString(23));

				resource->setAtt1Stat((System::random(res->getInt(25) - res->getInt(24)) + res->getInt(24)));
				resource->setAtt2Stat((System::random(res->getInt(27) - res->getInt(26)) + res->getInt(26)));
				resource->setAtt3Stat((System::random(res->getInt(29) - res->getInt(28)) + res->getInt(28)));
				resource->setAtt4Stat((System::random(res->getInt(31) - res->getInt(30)) + res->getInt(30)));
				resource->setAtt5Stat((System::random(res->getInt(33) - res->getInt(32)) + res->getInt(32)));
				resource->setAtt6Stat((System::random(res->getInt(35) - res->getInt(34)) + res->getInt(34)));
				resource->setAtt7Stat((System::random(res->getInt(37) - res->getInt(36)) + res->getInt(36)));
				resource->setAtt8Stat((System::random(res->getInt(39) - res->getInt(38)) + res->getInt(38)));
				resource->setAtt9Stat((System::random(res->getInt(41) - res->getInt(40)) + res->getInt(40)));
				resource->setAtt10Stat((System::random(res->getInt(43) - res->getInt(42)) + res->getInt(42)));
				resource->setAtt11Stat((System::random(res->getInt(45) - res->getInt(44)) + res->getInt(44)));

				resource->setContainer(res->getString(46));
				resource->setContainerCRC(res->getUnsignedInt(47));
			} else {
				cout << "Resouce Database error" << endl;
			}
		}
		
		makeResourceName(resname, resource->getClass1() == "Organic");
		
		resource->setName(resname);

		delete res;
	} catch (DatabaseException& e) {
	}
}

void ResourceManagerImplementation::makeMinimumPoolVector() {
	numFunctions++;
	
	try {
		minimumpool = new Vector<string>;
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
		cout << "Error in makeMinimumPoolVector\n";
	}
}

void ResourceManagerImplementation::makeFixedPoolVector() {
	numFunctions++;
	
	fixedpool = new Vector<string>;
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
		nativepool = new Vector<string>;

		numQueries++;

		stringstream query;
		query << "SELECT `resource_type` "
			  << "FROM `resource_tree` "
			  << "WHERE (class_1 = 'Organic' OR "
			  << "class_3 = 'Fiberplast' OR "
			  << "class_2 = 'Wind Energy' OR "
			  << "class_2 = 'Solar Energy' OR "
			  << "class_2 = 'Water') AND class_6 != 'JTL'";
		
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		string temp;
		
		while (res->next()) {
			nativepool->add(res->getString(0));
		}
		
		delete res;
	} catch (...) {
		cout << "Database error in makeNativePoolVector\n";
	}
}
bool ResourceManagerImplementation::isPlanetSpecific(const string type) {
	numFunctions++;
	
	if ((type.find("corellia", 0) == string::npos) && (type.find("dantooine", 0) == string::npos) 
			&& (type.find("yavin4", 0) == string::npos) && (type.find("dathomir", 0) == string::npos) 
			&& (type.find("endor", 0) == string::npos) && (type.find("lok", 0) == string::npos) 
			&& (type.find("naboo", 0) == string::npos) && (type.find("rori", 0) == string::npos)
			&& (type.find("talus", 0) == string::npos) && (type.find("tatooine", 0) == string::npos))
		return false;
	else
		return true;
}
int ResourceManagerImplementation::getPlanet(const string type) {
	numFunctions++;
	
	if (type.find("corellia", 0) != string::npos)
		return 0;
	
	if (type.find("dantooine", 0) != string::npos)
		return 1;
	
	if (type.find("dathomir", 0) != string::npos)
		return 2;
	
	if (type.find("endor", 0) != string::npos)
		return 3;
	
	if (type.find("lok", 0) != string::npos)
		return 4;
	
	if (type.find("naboo", 0) != string::npos)
		return 5;
	
	if (type.find("rori", 0) != string::npos)
		return 6;
	
	if (type.find("talus", 0) != string::npos)
		return 7;
	
	if (type.find("tatooine", 0) != string::npos)
		return 8;
	
	if (type.find("yavin4", 0) != string::npos)
		return 9;
	
	return 99;
}
bool ResourceManagerImplementation::isType(ResourceTemplate* resource, string type) {
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
		stringstream query;
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
			  << "'," << resource->getContainerCRC()<< ")";

		ServerDatabase::instance()->executeStatement(query);
		
		numInsert++;
	} catch (...) {
		cout << "Insert Resource Failed " << endl;
	}
}
void ResourceManagerImplementation::insertSpawn(ResourceTemplate* resource, int planet_id, 
		float x, float y, float radius, float max, string pool, bool& jtl) {
	numFunctions++;
	
	try {
		int upper, lower;
		
		if (resource->getClass1() == "Organic") {
			upper = 22;
			lower = 6;
		} else {
			if(jtl) {
				upper = 22;
				lower = 13;
			} else {
				upper = 11;
				lower = 6;
			}
		}
		
		long despawn = (long)time(0) + (System::random((aveduration * upper)-(aveduration * lower)))
			+ (aveduration* lower);
		
		stringstream query;
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
		
		resource->addSpawn(new SpawnLocation(id, planet_id, x, y, radius, max, pool));
		
		numInsert++;
	} catch (...) {
		cout << "Insert Spawn Failed " << endl;
	}
}

inline string ResourceManagerImplementation::checkInsertCategory(string instring) {
	numFunctions++;

	if (instring == "") {
		return "";
	} else {
		return ",`" + instring + "`";
	}
}

inline string ResourceManagerImplementation::checkInsertValue(int inval) {
	numFunctions++;
	
	if (inval == 0) {
		return "";
	} else {
		return ", " + stringify(inval);// + "`";
	}
}

void ResourceManagerImplementation::makeResourceName(string& resname, bool isOrganic) {
	numNameFunctions++;
	string randname;
		
	while(true) {
		randname = serv->getNameManager()->makeResourceName(isOrganic);
		if(checkResourceName(randname))
			break;
	}
	resname = randname;
}

bool ResourceManagerImplementation::checkResourceName(const string instring) {
	try {
		numFunctions++;
		
		stringstream query;
		query << "SELECT * from `resource_data` WHERE resource_name = \'" + instring + "\'";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		numQueries++;
		
		int size = res->size();
		
		delete res;
		
		if (size == 0) {
			return true;
		} else {
			//cout << "Duplicate Name, OMG?!?!" << endl;
			return false;
		}
	} catch (DatabaseException& e) {
		return false;
	}
}


bool ResourceManagerImplementation::isDumbPhrase(const string inname) {
	/*if ((inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("riy") == string::npos) && 
			(inname.find("anal") == string::npos))
		return true;
	else*/
		return false;
}

inline string ResourceManagerImplementation::stringify(const int x) {
	numNameFunctions++;
	ostringstream o;

	if (!(o << x))
		return "";
	else
		return o.str();
}

void ResourceManagerImplementation::setObjectSubType(ResourceTemplate* resImpl) {
	if (resImpl->getClass1() == "Inorganic") {
		if (resImpl->getClass2() == "Mineral") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICMINERAL);
		} else if (resImpl->getClass2() == "Chemical") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICCHEMICAL);
		} else if (resImpl->getClass2() == "Gas") {
			resImpl->setObjectSubType(TangibleObjectImplementation::INORGANICGAS);
		} else if (resImpl->getClass2() == "Water") {
			resImpl->setObjectSubType(TangibleObjectImplementation::WATER);
		}
	} else if (resImpl->getClass1() == "Organic") {
		if (resImpl->getClass3() == "Flora Food") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICFOOD);
		} else if (resImpl->getClass3() == "Flora Structural") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICSTRUCTURAL);
		} else if (resImpl->getClass3() == "Creature Food") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICFOOD);
		} else if (resImpl->getClass3() == "Creature Structural") {
			if (resImpl->getClass4() == "Bone") {
				resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICSTRUCTURAL);
			} else if (resImpl->getClass4() == "Hide") {
				resImpl->setObjectSubType(TangibleObjectImplementation::ORGANICHIDE);
			}
		}
	} else if (resImpl->getClass1() == "Energy") {
		if (resImpl->getClass2() == "Wind Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYLIQUID);
		} else if (resImpl->getClass2() == "Solar Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYLIQUID);
		} else if (resImpl->getClass2() == "Radioactive Energy") {
			resImpl->setObjectSubType(TangibleObjectImplementation::ENERGYRADIOACTIVE);
		}
	}
}
