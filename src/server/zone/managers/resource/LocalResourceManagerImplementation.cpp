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

#include "../../Zone.h"
#include "../../ZoneProcessServerImplementation.h"

#include "events/SpawnResourcesEvent.h"

#include "ResourceMap.h"
#include "LocalResourceManager.h"
#include "LocalResourceManagerImplementation.h"
#include "ResourceTemplate.h"
#include "ResourceTemplateImplementation.h"
#include "SpawnLocation.h"
#include "SpawnLocationImplementation.h"

#include "../../objects/tangible/resource/ResourceContainerImplementation.h"
#include "../../objects/tangible/surveytool/SurveyToolImplementation.h"

#include "../../packets.h"

LocalResourceManagerImplementation::LocalResourceManagerImplementation(Zone* zs, 
		ZoneProcessServerImplementation* inserv) : LocalResourceManagerServant(), Logger("LocalResourceManager") {
	zone = zs;
	server = inserv;
}

void LocalResourceManagerImplementation::init() {
	string query = "SELECT * FROM resource_data";
	ResultSet* res = ServerDatabase::instance()->executeQuery(query);
	int size = res->size();
	if (size < 500) {
		size = 750;
	}
	resourceMap = new ResourceMap(size * 2, .65);
	
	buildMap();
		
	stringstream ss;
	ss << "Zone " << zone->getZoneID() << " finished building hash table";
	info(ss.str());
}

void LocalResourceManagerImplementation::buildMap() {
	// Added by Ritter
	ResourceTemplateImplementation* resImpl;
	SpawnLocationImplementation* sl;
	string resname;
	
	try {
		string query = "SELECT * FROM resource_data";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		if (res->size() != 0) {
			while (res->next()) {
				resname = res->getString(1);
				resImpl = new ResourceTemplateImplementation(res->getString(2));
				resImpl->setName(resname);
				resImpl->setResourceID(res->getUnsignedLong(0));
				
				resImpl->setClass1(res->getString(3));
				resImpl->setClass2(res->getString(4));
				resImpl->setClass3(res->getString(5));
				resImpl->setClass4(res->getString(6));
				resImpl->setClass5(res->getString(7));
				resImpl->setClass6(res->getString(8));
				resImpl->setClass7(res->getString(9));
		
				resImpl->setMaxType(0);
				resImpl->setMinType(0);
				resImpl->setMinPool(0);
				resImpl->setMaxPool(0);
		
				resImpl->setAtt1("res_decay_resist");
				resImpl->setAtt2("res_quality");
				resImpl->setAtt3("res_flavor");
				resImpl->setAtt4("res_potential_energy");
				resImpl->setAtt5("res_malleability");
				resImpl->setAtt6("res_toughness");
				resImpl->setAtt7("res_shockresistance");
				resImpl->setAtt8("res_cold_resist");
				resImpl->setAtt9("res_heat_resist");
				resImpl->setAtt10("res_conductivity");
				resImpl->setAtt11("entangle_resistance");
		
				resImpl->setAtt1Stat(res->getInt(10));
				resImpl->setAtt2Stat(res->getInt(11));
				resImpl->setAtt3Stat(res->getInt(12));
				resImpl->setAtt4Stat(res->getInt(13));
				resImpl->setAtt5Stat(res->getInt(14));
				resImpl->setAtt6Stat(res->getInt(15));
				resImpl->setAtt7Stat(res->getInt(16));
				resImpl->setAtt8Stat(res->getInt(17));
				resImpl->setAtt9Stat(res->getInt(18));
				resImpl->setAtt10Stat(res->getInt(19));
				resImpl->setAtt11Stat(res->getInt(20));
		
				resImpl->setContainer(res->getString(23));
				resImpl->setContainerCRC(res->getUnsignedInt(24));
				
				setObjectSubType(resImpl);
				
				stringstream query2;
				query2 << "SELECT * FROM resource_spawns WHERE `resource_name` = '" << resname << "'";
				ResultSet* res2 = ServerDatabase::instance()->executeQuery(query2);
				if (res2->size() != 0) {
					while (res2->next()) {
						string pool = res2->getString(8);
						sl = new SpawnLocationImplementation(res2->getUnsignedLong(0), res2->getInt(2), res2->getFloat(3), res2->getFloat(4), res2->getFloat(5), res2->getFloat(6), pool);
						resImpl->addSpawn((SpawnLocation*)sl->deploy());
					}
				}
				delete res2;
				if (resourceMap->put(resname, resImpl) != NULL) {
					info("Hash collision occured");
				}
			}
		}
		delete res;
	} catch (DatabaseException& e) {
		cout << "Database error in buildMap\n";
	}
}

float LocalResourceManagerImplementation::getDensity(int planet, unicode& resname, float inx, float iny) {
	try {
		float density = 0.0f, max_density = 0.0f;
		
		float x, y, radius, source, distance = 0.0f;
		
		SpawnLocation* sl;
		
		string name;
		resname.c_str(name);
		ResourceTemplateImplementation* resource = resourceMap->get(name);
		
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
		
		return max_density;
		
	} catch (...) {
		cout << "Database error in getDensity\n";

	}
}

void LocalResourceManagerImplementation::sendSurveyMessage(Player* player, unicode& resourceName) {
	// Added by Ritter
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
		
		WaypointObjectImplementation* wayImpl =	new WaypointObjectImplementation(player, player->getNewItemID());
		wayImpl->setName("Resource Survey");
		wayImpl->setPosition(wp_x, 0.0f, wp_y);

		WaypointObject* waypoint = (WaypointObject*) ObjectRequestBroker::instance()->deploy("Resource Survey", wayImpl);
		waypoint->changeStatus(true);
		
		player->setSurveyWaypoint(waypoint);
		player->addWaypoint(waypoint);
		
		// Send Waypoint System Message
		unicode ustr = "";
		ChatSystemMessage* endMessage = new ChatSystemMessage("survey", "survey_waypoint", ustr, 0, true);
		
		player->sendMessage(endMessage);
	}
}

void LocalResourceManagerImplementation::sendSampleMessage(Player* player, unicode& resourceName) {
	// Added by Ritter
	float density = getDensity(player->getZoneIndex(), resourceName, player->getPositionX(), player->getPositionY());
	
	if (density < 0.1f) {
		ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "density_below_threshold", resourceName, 0, false);
		
		player->sendMessage(sysMessage);
		
		player->changePosture(CreatureObjectImplementation::UPRIGHT_POSTURE);
	} else {
		int sampleRate = System::random(1000) + (5 * player->getSkillMod("surveying"));
		
		if (sampleRate >= 650) {
			int resQuantity = (sampleRate / 100) * 2 - System::random(13);
			
			if (!(resQuantity > 0))
				resQuantity = 1;
			
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_located", resourceName, resQuantity, false);
			
			player->getSurveyTool()->sendSampleEffect(player);

			bool rFlag = false;

			Inventory* inventory = player->getInventory();

			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);
				
				if (item->isResource()) {
					ResourceContainer* rco = (ResourceContainer*) item;
					
					if (rco->getName().c_str() == resourceName.c_str()) {
						if (rco->getContents() + resQuantity <= rco->getMaxContents()) {
							rco->setContents(rco->getContents() + resQuantity);
							rco->sendDeltas(player);
							rco->generateAttributes(player);
							
							rco->setUpdated(true);
							
							resQuantity = 0;
							
							rFlag = true;
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
							rco->generateAttributes(player);
							
							rco->setUpdated(true);
						}
					}
				}
			}
			
			if (!rFlag) {
				ResourceContainerImplementation* rco = new ResourceContainerImplementation(player->getNewItemID());
				rco->setResourceName(resourceName);
				rco->setContents(resQuantity);
				
				setResourceData(rco);
				
				player->addInventoryItem(rco->deploy());
				
				rco->sendTo(player);
				
				rco->setPersistent(false);
			}
			
			player->sendMessage(sysMessage);
		} else {
			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey", "sample_failed", resourceName, 0, false);
			
			player->getSurveyTool()->sendSampleEffect(player);
			
			player->sendMessage(sysMessage);
		}
	}
}

void LocalResourceManagerImplementation::setResourceData(ResourceContainerImplementation* resContainer) {
	// Added by Ritter
	string name;
	resContainer->getName().c_str(name);
	ResourceTemplateImplementation* resource = resourceMap->get(name);
	resContainer->setResourceID(resource->getResourceID());
	resContainer->setColdResistance(resource->getAtt1Stat());
	resContainer->setConductivity(resource->getAtt2Stat());
	resContainer->setDecayResistance(resource->getAtt3Stat());
	resContainer->setHeatResistance(resource->getAtt4Stat());
	resContainer->setMalleability(resource->getAtt5Stat());
	resContainer->setFlavor(resource->getAtt6Stat());
	resContainer->setPotentialEnergy(resource->getAtt7Stat());
	resContainer->setQuality(resource->getAtt8Stat());
	resContainer->setShockResistance(resource->getAtt9Stat());
	resContainer->setToughness(resource->getAtt10Stat());
	resContainer->setEntangleResistance(resource->getAtt11Stat());
	resContainer->setContainerFile(resource->getType());
	resContainer->setObjectCRC(resource->getContainerCRC());
}

bool LocalResourceManagerImplementation::checkResource(Player* player, unicode& resourceName, int SurveyToolType) {
	// Added by Ritter
	string name;
	resourceName.c_str(name);
	ResourceTemplateImplementation* resource = resourceMap->get(name);
	if (resource != NULL) {
		for(int i = resource->getSpawnSize() - 1; i >= 0; i--) {
			SpawnLocation* sl = resource->getSpawn(i);
			if (sl->getPlanet() == player->getZoneID()) {
				return true;
			}
		}
	}
	return false;
}

bool LocalResourceManagerImplementation::sendSurveyResources(Player* player, int SurveyToolType) {
	// Added by Ritter
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
		return false;
	}
	
	ResourceListForSurvey* packet = new ResourceListForSurvey();
	
	ResourceTemplateImplementation* resource;
	
	resourceMap->resetIterator();
	
	while(resourceMap->hasNext()) {
		resource = resourceMap->getNextValue();
		if (resource->getSpawnSize() > 0 && (resource->getClass2() == class2 || resource->getClass2() == class2re)) {
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
	
	return true;
}

void LocalResourceManagerImplementation::sendSurveyResourceStats(Player* player, Vector<string>* rList) {
	// Added by Ritter
	ResourceTemplateImplementation* resource;
	
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

bool LocalResourceManagerImplementation::isDuplicate(Vector<string>* rList, string& resource) {
	// Added by Ritter
	if (rList->isEmpty()) {
		rList->add(resource);
		return false;
	}
	
	for (int i = rList->size() - 1; i >= 0; i--) {
		if (rList->get(i) == resource)
			return true;
	}
	
	rList->add(resource);
	
	return false;
}

void LocalResourceManagerImplementation::addResource(ResourceTemplate* resource) {
	ResourceTemplateImplementation* rti;
	rti = cloneResource(resource);
	if (resourceMap->put(rti->getName(), rti) != NULL) {
		info("Hash collision occured");
	}
}

SpawnLocation* LocalResourceManagerImplementation::despawnResource(string& resourceName, uint64 sid) {
	ResourceTemplateImplementation* resource = resourceMap->get(resourceName);
	if (resource != NULL) {
		SpawnLocation* sl = resource->removeSpawn(sid);
		return sl;
	} else {
		stringstream ss;
		ss << "Spawn removal for for " << resourceName << " FAILED! (Zone " << zone->getZoneID() << ", Table Size " << resourceMap->size() << ")";
		info(ss.str());
	}
	return NULL;
}

ResourceTemplateImplementation* LocalResourceManagerImplementation::cloneResource(ResourceTemplate* in) {
	ResourceTemplateImplementation* resImpl = new ResourceTemplateImplementation(in->getType());
	
	resImpl->setAtt1(in->getAtt1());
	resImpl->setAtt2(in->getAtt2());
	resImpl->setAtt3(in->getAtt3());
	resImpl->setAtt4(in->getAtt4());
	resImpl->setAtt5(in->getAtt5());
	resImpl->setAtt6(in->getAtt6());
	resImpl->setAtt7(in->getAtt7());
	resImpl->setAtt8(in->getAtt8());
	resImpl->setAtt9(in->getAtt9());
	resImpl->setAtt10(in->getAtt10());
	resImpl->setAtt11(in->getAtt11());
	
	resImpl->setAtt1Stat(in->getAtt1Stat());
	resImpl->setAtt2Stat(in->getAtt2Stat());
	resImpl->setAtt3Stat(in->getAtt3Stat());
	resImpl->setAtt4Stat(in->getAtt4Stat());
	resImpl->setAtt5Stat(in->getAtt5Stat());
	resImpl->setAtt6Stat(in->getAtt6Stat());
	resImpl->setAtt7Stat(in->getAtt7Stat());
	resImpl->setAtt8Stat(in->getAtt8Stat());
	resImpl->setAtt9Stat(in->getAtt9Stat());
	resImpl->setAtt10Stat(in->getAtt10Stat());
	resImpl->setAtt11Stat(in->getAtt11Stat());
	
	resImpl->setClass1(in->getClass1());
	resImpl->setClass2(in->getClass2());
	resImpl->setClass3(in->getClass3());
	resImpl->setClass4(in->getClass4());
	resImpl->setClass5(in->getClass5());
	resImpl->setClass6(in->getClass6());
	resImpl->setClass7(in->getClass7());
	
	resImpl->setName(in->getName());
	resImpl->setContainer(in->getContainer());
	resImpl->setContainerCRC(in->getContainerCRC());
	resImpl->setResourceID(in->getResourceID());
	resImpl->setObjectSubType(in->getObjectSubType());
	
	setObjectSubType(resImpl);
	
	for (int i = in->getSpawnSize() - 1; i >= 0; i--) {
		resImpl->addSpawn(in->getSpawn(i));
	}
	
	return resImpl;
}

void LocalResourceManagerImplementation::setObjectSubType(ResourceTemplateImplementation* resImpl) {
	resImpl->setObjectSubType(TangibleObjectImplementation::RESOURCECONTAINER);
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

string& LocalResourceManagerImplementation::getClassSeven(const string& resource) {
	ResourceTemplateImplementation* resImpl = resourceMap->get(resource);
	return resImpl->getClass7();
}
