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

#include "ResourceSpawn.h"

#include "ResourceList.h"

#include "SpawnLocation.h"

class SpawnResourcesEvent;

class ClassMap;

class ResourceManagerImplementation : public ResourceManagerServant, public Mutex, public Lua  {
	ZoneProcessServerImplementation* pserv;
	ZoneServer* server;

	Event* spawnResourcesEvent;

	Vector<String>* minimumpool;
	Vector<String>* fixedpool;

	Vector<String>* nativepool;

	Vector<String>* itemStrings;

	VectorMap<String, ResourceSpawn*>* resourceMap;
	VectorMap<uint64, String>* resourceIDNameMap;

	ClassMap* resourceTree;

	Vector<int> planets;

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
	int lowerGateOverride;

	bool forageResource;

	uint64 nextResourceID;

	String EMPTY;

	//int tempOver, tempUnder;
public:

	static const int RESOURCE_DEED_QUANTITY = 30000;

public:
	ResourceManagerImplementation(ZoneServer* inserver, ZoneProcessServerImplementation* inserv);
	~ResourceManagerImplementation();

	//LUA
	bool loadConfigFile();
	bool loadConfigData();

	void theShift();
	void stop();
	void clearResources();

	void sendSurveyMessage(Player* player, String& resourceName, bool doLock = true);
	void sendSampleMessage(Player* player, String& resourceName, bool doLock = true);

	bool useResourceDeed(Player* player, String& resourceName, int resourceQuantity);

	void setResourceData(ResourceContainer* resContainer, bool doLock = true);

	bool sendSurveyResources(Player* player, int SurveyToolType, bool doLock = true);

	bool checkResource(Player* player, String& resourceName, int SurveyToolType, bool doLock = true);

	void getClassSeven(const String& resource, String& clas, bool doLock = true);
	void getResourceContainerName(const String& resource, String& name, bool doLock = true);

	void printResource(String resname);

	void harvestOrganics(Player* player, Creature* creature, int type);

	ResourceList* getResourceListAtLocation(int zone, float x, float y, int type);

	String& getResourceNameByID(uint64 rID);

	void generateSUI(Player* player, SuiListBox* sui);

	bool containsResource(String& resourceName);

	void giveForageResource(Player* player, float foragex, float foragey, int forageplanet);

private:
	void init();
	void initSpawnZones();

	float getDensity(int planet, String& resname, float inx, float iny);

	float getDistanceFrom(float inx, float iny, float x, float y);

	void sendSurveyResourceStats(Player* player, Vector<String>* rList);
	bool isDuplicate(Vector<String>* rList, String& resource);

	void countResources();

	ResourceContainer* createNewResourceContainer(CreatureObject* creature, String& resourceName, int resourceQuantity);

	void buildResourceMap();

	void checkMinimumPool();
	void checkRandomPool();
	int randomPoolNeeds();
	void checkFixedPool();
	int fixedPoolIron();
	void checkNativePool();

	void poolNeeds(Vector<String> * invector, String pool, Vector<String>* outvector);

	void getFromRandomPool(Vector<String> * spawnMe, String pool);

	void removeExpiredResources();

	String getRandomResourceFromType(String restype, String exclusion);

	void insertResource(ResourceSpawn* resource);
	void insertSpawn(ResourceSpawn* resource, int planet_id, float x,
			float y, float radius, float max, String pool, bool& jtl);

	void addToResourceTree(ResourceSpawn* resource);
	void makeResourceTree();
	void makeMinimumPoolVector();
	void makeFixedPoolVector();
	void makeNativePoolVector();

	bool isPlanetSpecific(String type);
	int getPlanet(String type);

	void createResource(String restype, String pool, bool jtl);

	int randomize(int min, int max);

	void generateResourceStats(ResourceSpawn * resource);

	void setAttStat(ResourceSpawn* resource, String statTitle, int stat);

	bool isType(ResourceSpawn* resource, String type);

	String checkInsertCategory(String inString);
	String checkInsertValue(int inval);

	bool checkResourceName(const String inString);
	bool isDumbPhrase(const String inname);

	// Resource Naming Scheme
	void makeResourceName(String& resname, bool isOrganic);

	void setObjectType(ResourceSpawn* resImpl);

	String getCurrentNameFromType(String type);

	void getHarvestingType(CreatureObject* creatureObj, String& harvestType, int& harvestAmount, int type);

	uint64 getNextResourceID() {
		return nextResourceID++;
	}
};

#include "../../objects/player/sui/listbox/SuiListBoxVector.h"

class SuiListBoxVector;

class ClassMap {
private:
	VectorMap<String, ClassMap*>* classTree;
	VectorMap<String, ResourceSpawn*>* resTree;
	Vector<String>* classList;
	String className;
	bool containsResources;
	int searchNum;

public:
	ClassMap(){
		classTree = new VectorMap<String, ClassMap*>();
		classTree->setNullValue(NULL);
		resTree = new VectorMap<String, ResourceSpawn*>();
		resTree->setNullValue(NULL);
		classList = new Vector<String>();
		className = "";
		init();
	}

	~ClassMap(){
		if (classTree!=NULL){
			delete classTree;
			classTree=NULL;
		}
		if (resTree!=NULL){
			delete resTree;
			resTree=NULL;
		}
		delete classList;
	}

	void init(){
		classTree->setNullValue(NULL);
		resTree->setNullValue(NULL);
		containsResources = false;
		searchNum=0;
	}

	/*
	 * Returns the name of the class.
	 */
	void setClassName(String name){
		className = name;
	}

	/*
	 * Sets the name of the class.
	 */
	String getClassName(){
		return className;
	}

	/*
	 * Adds a resource and all of its subclasses to the tree
	 */
	void addResource(ResourceSpawn* resTemp){
		String classToAdd = resTemp->getClass1();
		ClassMap* temp = this;
		temp = temp->addClass(classToAdd);

		if (resTemp->getClass2()!=""){
			classToAdd = resTemp->getClass2();
			temp = temp->addClass(classToAdd);
		}

		if (resTemp->getClass3()!=""){
			classToAdd = resTemp->getClass3();
			temp = temp->addClass(classToAdd);
		}

		if (resTemp->getClass4()!=""){
			classToAdd = resTemp->getClass4();
			temp = temp->addClass(classToAdd);
		}

		if (resTemp->getClass5()!=""){
			classToAdd = resTemp->getClass5();
			temp = temp->addClass(classToAdd);
		}

		if (resTemp->getClass6()!=""){
			classToAdd = resTemp->getClass6();
			temp = temp->addClass(classToAdd);
		}

		if (resTemp->getClass7()!=""){
			classToAdd = resTemp->getClass7();
			temp = temp->addClass(classToAdd);
		}

		temp->addChildResource(resTemp);
	}

	/*
	 * Returns the size of the contained Vector<String>
	 * NO class should have a classTree AND resTree populated
	 * So if this class contains classes, the size is of the classTree
	 * if this class contains resources, the size is of the resTree
	 */
	int size(){
		if (classTree->size()>0)
			return classTree->size();
		else
			return resTree->size();
	}

	/*
	 * Gets the list of classes for the current ClassMap
	 */
	Vector<String>* getClassList(){
		return classList;
	}

	/*
	 * Tree traversal algorithm to return the class list of a passed in className
	 * ex. resourceTree->getClassesFromClass("Flora");
	 * returns a vector<String> with "Flora Food" and "Flora Structural"
	 */
	Vector<String>* getClassesFromClass(String className){
		ClassMap* temp = this;
		Vector<String>* classes = new Vector<String>();
		classes->removeAll();
		if (getClassName()==className){
			for (int i=0; i<classTree->size(); i++){
				classes->add(classTree->get(i)->getClassName());
			}
			return classes;
		}
		else{
			if (searchNum < classTree->size()){
				while (classes->size()==0){
					temp = classTree->get(searchNum);
					classes = temp->getClassesFromClass(className);
					searchNum++;
					if (searchNum >= classTree->size()){
						searchNum=0;
						return classes;
					}
				}
				searchNum=0;
				return classes;
			}
			else{
				searchNum=0;
				return classes;
			}
		}
	}

	/*
	 * Gets a list of ResourceTemplates that are a child of a particular class
	 * Ex. resourceTree->getResourcesFromClass("Flora");
	 * returns every ResourceTemplate that is of type "Flora"
	 */
	Vector<ResourceSpawn*>* getResourcesFromClass(String className){
		ClassMap* temp = this;
		Vector<ResourceSpawn*>* resources = new Vector<ResourceSpawn*>();
		resources->removeAll();
		if (getClassName()==className){
			temp->findResourcesFromClass(resources, className);
			return resources;
		}
		else{
			if (searchNum < classTree->size()){
				while (resources->size()==0){
					temp = classTree->get(searchNum);
					resources = temp->getResourcesFromClass(className);
					searchNum++;
					if (searchNum >= classTree->size()){
						searchNum=0;
						return resources;
					}
				}
				searchNum=0;
				return resources;
			}
			else{
				searchNum=0;
				return resources;
			}
		}
	}

	/*
	 * Gets the menu of next classes for a given list of sui box choices by the player
	 */
	Vector<String>* getSuiMenuList(SuiListBoxVector* choicesList){
		ClassMap* temp = this;
		for (int i=0; i<choicesList->size(); i++){
			if (temp->containsClass(choicesList->get(i)))
				temp = temp->getClass(choicesList->get(i));
			else{
				if (temp->hasResource(choicesList->get(i)))
					return temp->getResourceStatsList(choicesList->get(i));
				else
					return NULL;
			}
		}
		return temp->getClassList();
	}

	/*
	 * Pass in a list of previous sui box choices and
	 * Returns true if the current class contains resources
	 * Returns false if the current class contains more classes
	 */
	bool classContainsResources(SuiListBoxVector* choicesList){
		ClassMap* temp = this;
		for (int i=0; i<choicesList->size(); i++){
			if (temp->containsClass(choicesList->get(i)))
				temp = temp->getClass(choicesList->get(i));
			else
				return false;
		}
		return temp->hasResources();
	}

private:

	/*
	 * part of the getResourcesFromClass tree traversal
	 * Starts at the class you specified as the "root"
	 * and then adds all child resources based off of that root to a vector
	 */
	bool findResourcesFromClass(Vector<ResourceSpawn*>* resources, String className){
		ClassMap* temp = this;
		if (classTree->size()==0){
			for (int i=0; i<resTree->size(); i++){
				resources->add(resTree->get(i));
			}
			return true;
		}
		else{
			while (searchNum < classTree->size()){
				temp = classTree->get(searchNum);
				temp->findResourcesFromClass(resources, className);
				searchNum++;
			}
			searchNum=0;
			return false;
		}
	}

	/*
	 * Gets the stats of a resource and adds them to a vector to be
	 * displayed in a SUI for the resourceDeed
	 */
	Vector<String>* getResourceStatsList(String& resourceName){
		ResourceSpawn* resTemp = resTree->get(resourceName);
		Vector<String>* resStats = new Vector<String>();
		resStats->removeAll();
		String temp = ("Resource Name = " + resTemp->getName());
		resStats->add(temp);
		if (resTemp->getAtt1Stat()>0){
			StringBuffer numstream;
			numstream << "Decay Resistance = " << resTemp->getAtt1Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt2Stat()>0){
			StringBuffer numstream;
			numstream << "Overall Quality = " << resTemp->getAtt2Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt3Stat()>0){
			StringBuffer numstream;
			numstream << "Flavor = " << resTemp->getAtt3Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt4Stat()>0){
			StringBuffer numstream;
			numstream << "Potential Energy = " << resTemp->getAtt4Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt5Stat()>0){
			StringBuffer numstream;
			numstream << "Malleability = " << resTemp->getAtt5Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt6Stat()>0){
			StringBuffer numstream;
			numstream << "Unit Toughness = " << resTemp->getAtt6Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt7Stat()>0){
			StringBuffer numstream;
			numstream << "Shock Resistance = " << resTemp->getAtt7Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt8Stat()>0){
			StringBuffer numstream;
			numstream << "Cold Resistance = " << resTemp->getAtt8Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt9Stat()>0){
			StringBuffer numstream;
			numstream << "Heat Resistance = " << resTemp->getAtt9Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt10Stat()>0){
			StringBuffer numstream;
			numstream << "Conductivity = " << resTemp->getAtt10Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		if (resTemp->getAtt11Stat()>0){
			StringBuffer numstream;
			numstream << "Entangle Resistance = " << resTemp->getAtt11Stat();
			temp = numstream.toString();
			resStats->add(temp);
		}
		return resStats;
	}

	ClassMap* getClass(String& name){
		return classTree->get(name);
	}

	ResourceSpawn* getResourceTemplate(String& name){
		return resTree->get(name);
	}

	bool hasResources(){
		return containsResources;
	}

	bool hasResource(String& resourceName){
		return resTree->contains(resourceName);
	}

	bool containsClass(String& className){
		return classTree->contains(className);
	}

	/*
	 * this adds a class to the tree for
	 * more classes or resource to be added to it
	 */
	ClassMap* addClass(String& classToAdd){
		if (!classTree->contains(classToAdd)){
			ClassMap* temp = new ClassMap();
			temp->setClassName(classToAdd);
			classTree->put(classToAdd, temp);
			classList->add(classToAdd);
			return temp;
		}
		return classTree->get(classToAdd);
	}

	/*
	 * this adds a resource to the end of a class "branch"
	 * of the tree
	 */
	void addChildResource(ResourceSpawn* resTemp){
		if (!resTree->contains(resTemp->getName())){
			resTree->put(resTemp->getName(), resTemp);
			classList->add(resTemp->getName());
			containsResources=true;
		}
	}

};

#endif /*ResourceManagerImplementation_*/
