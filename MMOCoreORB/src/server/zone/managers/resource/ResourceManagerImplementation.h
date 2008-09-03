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

#ifndef RESOURCEMANAGERIMPLEMENTATION_
#define RESOURCEMANAGERIMPLEMENTATION_

#include <vector>

#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "../../objects/player/Player.h"

#include "../../objects/tangible/Inventory.h"

#include "../../objects/waypoint/WaypointObjectImplementation.h"

#include "../../objects/tangible/surveytool/SurveyTool.h"

#include "../../objects/tangible/resource/ResourceContainer.h"

#include "../../objects/creature/Creature.h"
#include "../../objects/creature/CreatureObject.h"

#include "ResourceManager.h"

#include "ResourceTemplate.h"

#include "SpawnLocation.h"

class SpawnResourcesEvent;

class ResourceManagerImplementation : public ResourceManagerServant, public Mutex, public Lua  {
	ZoneProcessServerImplementation* serv;

	Event* spawnResourcesEvent;

	Vector<string>* minimumpool;
	Vector<string>* fixedpool;
	Vector<string>* nativepool;

	VectorMap<string, ResourceTemplate*>* resourceMap;

	//  The following 4 variable are for testing, and provide no functionality
	//  Used to help increase efficiency in code
	int numQueries;
	int numInsert;
	int numFunctions;
	int numNameFunctions;

	long averageShiftTime;
	int maxspawns;
	int minspawns;
	int maxradius;
	int minradius;
	int aveduration;

	float spawnThrottling;


	//int tempOver, tempUnder;


public:
	ResourceManagerImplementation(ZoneServer* inserver, ZoneProcessServerImplementation* inserv);
	~ResourceManagerImplementation();

	//LUA
	bool loadConfigFile();
	bool loadConfigData();

	void theShift();
	void stop();
	void clearResources();

	void sendSurveyMessage(Player* player, string& resourceName, bool doLock = true);
	void sendSampleMessage(Player* player, string& resourceName, bool doLock = true);

	void setResourceData(ResourceContainer* resContainer, bool doLock = true);

	bool sendSurveyResources(Player* player, int SurveyToolType, bool doLock = true);

	bool checkResource(Player* player, string& resourceName, int SurveyToolType, bool doLock = true);

	void getClassSeven(const string& resource, string& clas, bool doLock = true);
	void getResourceContainerName(const string& resource, string& name, bool doLock = true);

	void printResource(string resname);

	void harvestOrganics(Player* player, Creature* creature, int type);

private:
	void init();

	float getDensity(int planet, string& resname, float inx, float iny);

	float getDistanceFrom(float inx, float iny, float x, float y);

	void sendSurveyResourceStats(Player* player, Vector<string>* rList);
	bool isDuplicate(Vector<string>* rList, string& resource);

	void countResources();

	void buildResourceMap();

	void checkMinimumPool();
	void checkRandomPool();
	int randomPoolNeeds();
	void checkFixedPool();
	int fixedPoolIron();
	void checkNativePool();

	void poolNeeds(Vector<string> * invector, string pool, Vector<string>* outvector);

	void getFromRandomPool(Vector<string> * spawnMe, string pool);

	void removeExpiredResources();

	string getRandomResourceFromType(string restype, string exclusion);

	void insertResource(ResourceTemplate* resource);
	void insertSpawn(ResourceTemplate* resource, int planet_id, float x,
			float y, float radius, float max, string pool, bool& jtl);

	void makeMinimumPoolVector();
	void makeFixedPoolVector();
	void makeNativePoolVector();

	bool isPlanetSpecific(string type);
	int getPlanet(string type);

	void createResource(string restype, string pool, bool jtl);

	int randomize(int min, int max);

	void generateResourceStats(ResourceTemplate * resource);

	void setAttStat(ResourceTemplate* resource, string statTitle, int stat);

	bool isType(ResourceTemplate* resource, string type);

	string checkInsertCategory(string instring);
	string checkInsertValue(int inval);

	bool checkResourceName(const string instring);
	bool isDumbPhrase(const string inname);

	// Resource Naming Scheme
	void makeResourceName(string& resname, bool isOrganic);

	string stringify(const int x);

	void setObjectSubType(ResourceTemplate* resImpl);

	void verifyResourceMap();
	void verifyResourceData(int i, ResourceTemplate* resTemp);

	string getCurrentNameFromType(string type);

	void getHarvestingType(CreatureObject* creatureObj, string& harvestType, int& harvestAmount, int type);

};

#endif /*ResourceManagerImplementation_*/
