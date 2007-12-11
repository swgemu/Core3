#ifndef RESOURCEMANAGERIMPLEMENTATION_
#define RESOURCEMANAGERIMPLEMENTATION_

#include "engine/engine.h"

#include "ResourceManager.h"

class ZoneServer;
class ResourceManager;

class ResourceManagerImplementation : public ResourceManagerServant, public Mutex {
	int nameLength;
	
public:
	ResourceManagerImplementation(ZoneServer* server);
	
	void shiftOutResources();
	void shiftInResources();
	
	void makeResourceName(string& resname, bool isOrganic);

private:
	bool isVowel(const char inChar);
	
	char chooseNextLetter(const char lastLetter, const char letterBeforeLast);
	char chooseLetterExcluding(const char exclude[]);
	
	int addPrefix(char* name);
	void addSuffix(char* name, int location);

	string stringify(const int x);
	
};


#endif /*ResourceManagerImplementation_*/
