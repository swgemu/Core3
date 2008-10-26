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

#include "ResourceList.h"

#include "SpawnLocation.h"

class SpawnResourcesEvent;

class ClassMap;

class ResourceManagerImplementation : public ResourceManagerServant, public Mutex, public Lua  {
	ZoneProcessServerImplementation* serv;

	Event* spawnResourcesEvent;

	Vector<string>* minimumpool;
	Vector<string>* fixedpool;
	Vector<string>* nativepool;
	Vector<string>* itemStrings;

	VectorMap<string, ResourceTemplate*>* resourceMap;
	VectorMap<uint64, string>* resourceIDNameMap;

	ClassMap* resourceTree;

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

	string EMPTY;

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

	void sendSurveyMessage(Player* player, string& resourceName, bool doLock = true);
	void sendSampleMessage(Player* player, string& resourceName, bool doLock = true);

	void setResourceData(ResourceContainer* resContainer, bool doLock = true);

	bool sendSurveyResources(Player* player, int SurveyToolType, bool doLock = true);

	bool checkResource(Player* player, string& resourceName, int SurveyToolType, bool doLock = true);

	void getClassSeven(const string& resource, string& clas, bool doLock = true);
	void getResourceContainerName(const string& resource, string& name, bool doLock = true);

	void printResource(string resname);

	void harvestOrganics(Player* player, Creature* creature, int type);

	ResourceList* getResourceListAtLocation(int zone, float x, float y, int type);

	string& getResourceNameByID(uint64 rID);

	void generateSUI(Player* player, SuiListBox* sui);

	bool giveResource(Player* player, string& resourceName, int amount);

	bool containsResource(string& resourceName);

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

	void addToResourceTree(ResourceTemplate* resource);
	void makeResourceTree();
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

#include "../../objects/player/sui/listbox/SuiListBoxVector.h"

class SuiListBoxVector;

class ClassMap {
private:
	VectorMap<string, ClassMap*>* classTree;
	VectorMap<string, ResourceTemplate*>* resTree;
	Vector<string>* classList;
	string className;
	bool containsResources;
	int searchNum;

public:
	ClassMap(){
		classTree = new VectorMap<string, ClassMap*>();
		resTree = new VectorMap<string, ResourceTemplate*>();
		classList = new Vector<string>();
		className = "";
		init();
	}

	~ClassMap(){
		if(classTree!=NULL){
			delete classTree;
			classTree=NULL;
		}
		if(resTree!=NULL){
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
	void setClassName(string name){
		className = name;
	}

	/*
	 * Sets the name of the class.
	 */
	string getClassName(){
		return className;
	}

	/*
	 * Adds a resource and all of its subclasses to the tree
	 */
	void addResource(ResourceTemplate* resTemp){
		string classToAdd = resTemp->getClass1();
		ClassMap* temp = this;
		temp = temp->addClass(classToAdd);

		if(resTemp->getClass2()!=""){
			classToAdd = resTemp->getClass2();
			temp = temp->addClass(classToAdd);
		}

		if(resTemp->getClass3()!=""){
			classToAdd = resTemp->getClass3();
			temp = temp->addClass(classToAdd);
		}

		if(resTemp->getClass4()!=""){
			classToAdd = resTemp->getClass4();
			temp = temp->addClass(classToAdd);
		}

		if(resTemp->getClass5()!=""){
			classToAdd = resTemp->getClass5();
			temp = temp->addClass(classToAdd);
		}

		if(resTemp->getClass6()!=""){
			classToAdd = resTemp->getClass6();
			temp = temp->addClass(classToAdd);
		}

		if(resTemp->getClass7()!=""){
			classToAdd = resTemp->getClass7();
			temp = temp->addClass(classToAdd);
		}

		temp->addChildResource(resTemp);
	}

	/*
	 * Returns the size of the contained Vector<string>
	 * NO class should have a classTree AND resTree populated
	 * So if this class contains classes, the size is of the classTree
	 * if this class contains resources, the size is of the resTree
	 */
	int size(){
		if(classTree->size()>0)
			return classTree->size();
		else
			return resTree->size();
	}

	/*
	 * Gets the list of classes for the current ClassMap
	 */
	Vector<string>* getClassList(){
		return classList;
	}

	/*
	 * Tree traversal algorithm to return the class list of a passed in className
	 * ex. resourceTree->getClassesFromClass("Flora");
	 * returns a vector<string> with "Flora Food" and "Flora Structural"
	 */
	Vector<string>* getClassesFromClass(string className){
		ClassMap* temp = this;
		Vector<string>* classes = new Vector<string>();
		classes->removeAll();
		if(getClassName()==className){
			for(int i=0; i<classTree->size(); i++){
				classes->add(classTree->get(i)->getClassName());
			}
			return classes;
		}
		else{
			if(searchNum < classTree->size()){
				while(classes->size()==0){
					temp = classTree->get(searchNum);
					classes = temp->getClassesFromClass(className);
					searchNum++;
					if(searchNum >= classTree->size()){
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
	Vector<ResourceTemplate*>* getResourcesFromClass(string className){
		ClassMap* temp = this;
		Vector<ResourceTemplate*>* resources = new Vector<ResourceTemplate*>();
		resources->removeAll();
		if(getClassName()==className){
			temp->findResourcesFromClass(resources, className);
			return resources;
		}
		else{
			if(searchNum < classTree->size()){
				while(resources->size()==0){
					temp = classTree->get(searchNum);
					resources = temp->getResourcesFromClass(className);
					searchNum++;
					if(searchNum >= classTree->size()){
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
	Vector<string>* getSuiMenuList(SuiListBoxVector* choicesList){
		ClassMap* temp = this;
		for(int i=0; i<choicesList->size(); i++){
			if(temp->containsClass(choicesList->get(i)))
				temp = temp->getClass(choicesList->get(i));
			else{
				if(temp->hasResource(choicesList->get(i)))
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
		for(int i=0; i<choicesList->size(); i++){
			if(temp->containsClass(choicesList->get(i)))
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
	bool findResourcesFromClass(Vector<ResourceTemplate*>* resources, string className){
		ClassMap* temp = this;
		if(classTree->size()==0){
			for(int i=0; i<resTree->size(); i++){
				resources->add(resTree->get(i));
			}
			return true;
		}
		else{
			while(searchNum < classTree->size()){
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
	Vector<string>* getResourceStatsList(string& resourceName){
		ResourceTemplate* resTemp = resTree->get(resourceName);
		Vector<string>* resStats = new Vector<string>();
		resStats->removeAll();
		string temp = ("Resource Name = " + resTemp->getName());
		resStats->add(temp);
		if(resTemp->getAtt1Stat()>0){
			stringstream numstream;
			numstream << "Decay Resistance = " << resTemp->getAtt1Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt2Stat()>0){
			stringstream numstream;
			numstream << "Overall Quality = " << resTemp->getAtt2Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt3Stat()>0){
			stringstream numstream;
			numstream << "Flavor = " << resTemp->getAtt3Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt4Stat()>0){
			stringstream numstream;
			numstream << "Potential Energy = " << resTemp->getAtt4Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt5Stat()>0){
			stringstream numstream;
			numstream << "Malleability = " << resTemp->getAtt5Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt6Stat()>0){
			stringstream numstream;
			numstream << "Unit Toughness = " << resTemp->getAtt6Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt7Stat()>0){
			stringstream numstream;
			numstream << "Shock Resistance = " << resTemp->getAtt7Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt8Stat()>0){
			stringstream numstream;
			numstream << "Cold Resistance = " << resTemp->getAtt8Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt9Stat()>0){
			stringstream numstream;
			numstream << "Heat Resistance = " << resTemp->getAtt9Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt10Stat()>0){
			stringstream numstream;
			numstream << "Conductivity = " << resTemp->getAtt10Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		if(resTemp->getAtt11Stat()>0){
			stringstream numstream;
			numstream << "Entangle Resistance = " << resTemp->getAtt11Stat();
			temp = numstream.str();
			resStats->add(temp);
		}
		return resStats;
	}

	ClassMap* getClass(string& name){
		return classTree->get(name);
	}

	ResourceTemplate* getResourceTemplate(string& name){
		return resTree->get(name);
	}

	bool hasResources(){
		return containsResources;
	}

	bool hasResource(string& resourceName){
		return resTree->contains(resourceName);
	}

	bool containsClass(string& className){
		return classTree->contains(className);
	}

	/*
	 * this adds a class to the tree for
	 * more classes or resource to be added to it
	 */
	ClassMap* addClass(string& classToAdd){
		if(!classTree->contains(classToAdd)){
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
	void addChildResource(ResourceTemplate* resTemp){
		if(!resTree->contains(resTemp->getName())){
			resTree->put(resTemp->getName(), resTemp);
			classList->add(resTemp->getName());
			containsResources=true;
		}
	}

};

#endif /*ResourceManagerImplementation_*/
