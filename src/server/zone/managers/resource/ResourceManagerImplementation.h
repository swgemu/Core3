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

#ifndef RESOURCEMANAGERIMPLEMENTATION_H_
#define RESOURCEMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../ZoneServer.h"
#include "../../ZoneProcessServerImplementation.h"

#include "../../objects/player/Player.h"

#include "../../objects/tangible/Inventory.h"

#include "../../objects/waypoint/WaypointObjectImplementation.h"

#include "../../objects/tangible/surveytool/SurveyTool.h"

#include "../../objects/tangible/resource/ResourceContainer.h"

#include "ResourceManager.h"
#include "ResourceTemplate.h"
#include "ResourceTemplateImplementation.h"
#include "SpawnLocation.h"

class SpawnResourcesEvent;
class Zone;
class LocalResourceManager;

class ResourceManagerImplementation : public ResourceManagerServant, public Logger {
	ZoneServer* zoneserver;
	ZoneProcessServerImplementation* server;
	
	Event* spawnResourcesEvent;
	
	Vector<string>* minimumpool;
	Vector<string>* fixedpool;
	Vector<string>* nativepool;
	
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
	
public:
	ResourceManagerImplementation(ZoneServer* planet, ZoneProcessServerImplementation* serv);
	
	void theShift();
	void clearResources();
	
	inline void stop() {
		if (spawnResourcesEvent != NULL) {
			server->removeEvent(spawnResourcesEvent);
		}
	}
	
	/*
	float getDensity(int planet, unicode& resname, float inx, float iny);
	void sendSurveyMessage(Player* player, unicode& resource_name);
	void sendSampleMessage(Player* player, unicode& resource_name);
	void setResourceData(ResourceContainerImplementation* resContainer);
	
	bool sendSurveyResources(Player* player, int SurveyToolType);
	bool checkResource(Player* player, unicode& resource_name, int SurveyToolType);
	*/
private:
	/*
	void sendSurveyResourceStats(Player* player, Vector<string>* rList);
	bool isDuplicate(Vector<string>* rList, string& resource);
	
	void buildMap();
	*/
	
	void init();
	
	void countResources();

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

	void insertResource(ResourceTemplateImplementation* resource);
	void insertSpawn(ResourceTemplateImplementation* resource, int planet_id, float x,
			float y, float radius, float max, string pool, bool& jtl);

	void makeMinimumPoolVector();
	void makeFixedPoolVector();
	void makeNativePoolVector();

	bool isPlanetSpecific(string type);
	int getPlanet(string type);

	void createResource(string restype, string pool, bool jtl);
	
	void generateResourceStats(ResourceTemplateImplementation * resource);

	bool isType(ResourceTemplateImplementation* resource, string type);

	string checkInsertCategory(string instring);
	string checkInsertValue(int inval);

	bool checkResourceName(const string instring);
	bool isProfanity(const string inname);
	bool isDumbPhrase(const string inname);

	// Resource Naming Scheme
	void makeResourceName(string& resname, bool isOrganic);

	bool isVowel(const char inChar);

	char chooseNextLetter(const char lastLetter, const char letterBeforeLast);
	char chooseLetterExcluding(const char exclude[]);

	int addPrefix(char* name);
	void addSuffix(char* name, int location);

	string stringify(const int x);
};

#endif /*RESOURCEMANAGERIMPLEMENTATION_H_*/
