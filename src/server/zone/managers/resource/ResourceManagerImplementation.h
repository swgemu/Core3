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

#include "ResourceManager.h"
#include "ResourceImplementation.h"

class SpawnResourcesEvent;

class ResourceManagerImplementation : public ResourceManagerServant, public Logger {
	ZoneProcessServerImplementation* serv;
	
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
	ResourceManagerImplementation(ZoneServer* inserver, ZoneProcessServerImplementation* inserv);
	
	void theShift();
	void clearResources();
	
	float getDensity(int planet, unicode& resname, float inx, float iny);
	void sendSurveyMessage(Player* player, unicode& resource_name);
	void sendSampleMessage(Player* player, unicode& resource_name);
	void setResourceData(ResourceContainerImplementation* resContainer);
	
	void sendResourceStats(Player* player, int SurveyToolType);
	bool sendResourceList(Player* player, int SurveyToolType);
	bool checkResource(Player* player, unicode& resource_name, int SurveyToolType);
	
	
private:
	bool isDuplicate(Vector<string>& rList, string& resource);
	
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

	void insertResource(ResourceImplementation* resource);
	void insertSpawn(ResourceImplementation* resource, int planet_id, float x,
			float y, float radius, float max, string pool, bool& jtl);

	void makeMinimumPoolVector();
	void makeFixedPoolVector();
	void makeNativePoolVector();

	bool isPlanetSpecific(string type);
	int getPlanet(string type);

	void createResource(string restype, string pool, bool jtl);
	
	void generateResourceStats(ResourceImplementation * resource);

	bool isType(ResourceImplementation* resource, string type);

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

#endif /*ResourceManagerImplementation_*/
