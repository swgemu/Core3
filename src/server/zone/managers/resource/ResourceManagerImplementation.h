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
#include "ResourceTemplate.h"
#include "ResourceTemplate.h"
#include "SpawnLocation.h"

class SpawnResourcesEvent;

class ResourceManagerImplementation : public ResourceManagerServant, public Logger, public Mutex {
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
	
public:
	ResourceManagerImplementation(ZoneServer* inserver, ZoneProcessServerImplementation* inserv);
	
	void theShift();
	void stop();
	void clearResources();
	
	void sendSurveyMessage(Player* player, string& resourceName, bool doLock = true);
	void sendSampleMessage(Player* player, string& resourceName, bool doLock = true);
	
	void setResourceData(ResourceContainerImplementation* resContainer, bool doLock = true);
	
	bool sendSurveyResources(Player* player, int SurveyToolType, bool doLock = true);
	
	bool checkResource(Player* player, string& resourceName, int SurveyToolType, bool doLock = true);
	
	void getClassSeven(const string& resource, string& clas);
private:
	void init();
	
	float getDensity(int planet, string& resname, float inx, float iny);
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
	
	void generateResourceStats(ResourceTemplate * resource);

	bool isType(ResourceTemplate* resource, string type);

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
	
	void setObjectSubType(ResourceTemplate* resImpl);
};

#endif /*ResourceManagerImplementation_*/
