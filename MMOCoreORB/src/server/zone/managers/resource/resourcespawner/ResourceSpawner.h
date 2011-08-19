/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

/**
 * \file ResourceSpawner.h
 * \author Kyle Burkhardt
 * \date 5-03-10
 */

#ifndef RESOURCESPAWNER_H_
#define RESOURCESPAWNER_H_

#include "engine/db/ObjectDatabase.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "resourcetree/ResourceTree.h"
#include "resourcemap/ResourceMap.h"

#include "resourcepool/MinimumPool.h"
#include "resourcepool/FixedPool.h"
#include "resourcepool/RandomPool.h"
#include "resourcepool/NativePool.h"
#include "resourcepool/ManualPool.h"

namespace server {
namespace zone {
namespace objects {
namespace player {
namespace sui {
namespace listbox {
	class SuiListBox;
}
}
}
}
}
}

using namespace server::zone::objects::player::sui::listbox;

/**
 * The ResourceSpawner class represents all the functions related to ResourceSpawns
 * Including spawning, despawning rules,
 */
class ResourceSpawner : public Logger, public Object {
private:
	ManagedReference<ZoneServer* > server;
	ManagedReference<ZoneProcessServer*> processor;

	NameManager* nameManager;
	ObjectManager* objectManager;

	ResourceTree* resourceTree;
	ObjectDatabaseManager* databaseManager;

	ResourceMap* resourceMap;

	Vector<String> jtlResources;
	Vector<String> activeResourceZones;

	MinimumPool* minimumPool;
	FixedPool* fixedPool;
	RandomPool* randomPool;
	NativePool* nativePool;
	ManualPool* manualPool;

	int shiftDuration, lowerGateOverride, maxSpawnAmount;
	float spawnThrottling;

	int samplingMultiplier;

public:
	ResourceSpawner(ManagedReference<ZoneServer* > serv,
			ZoneProcessServer* impl, ObjectManager* objMan);
	~ResourceSpawner();

	void init();

	void initializeMinimumPool(const String& includes, const String& excludes);
	void initializeFixedPool(const String& includes, const String& excludes);
	void initializeRandomPool(const String& includes, const String& excludes, const int size);
	void initializeNativePool(const String& includes, const String& excludes);

	void addPlanet(const String& planetName);
	void addJtlResource(const String& resourceName);
	void setSpawningParameters(const int dur, const float throt,
			const int override, const int spawnquantity);

	void start();
	void shiftResources();

	ResourceSpawn* createResourceSpawn(const String& type, const String& zonerestriction = "");
	ResourceSpawn* createResourceSpawn(const String& type, const Vector<String>& excludes, const String& zonerestriction = "");
	ResourceSpawn* createResourceSpawn(const Vector<String>& includes, const Vector<String>& excludes = 0, const String& zonerestriction = "");

	ResourceSpawn* manualCreateResourceSpawn(const String& type);

	void sendResourceListForSurvey(CreatureObject* player, const int toolType, const String& surveyType);

	void sendSurvey(CreatureObject* player, const String& resname);
	void sendSample(CreatureObject* player, const String& resname, const String& sampleAnimation);
	void sendSampleResults(CreatureObject* player, const float density, const String& resname);

	ResourceContainer* harvestResource(CreatureObject* player, const String& type, const int quantity);
	void harvestResource(CreatureObject* player, ResourceSpawn* resourceSpawn, int quantity);
	void addResourceToPlayerInventory(CreatureObject* player, ResourceSpawn* resourceSpawn, int unitsExtracted);

	ResourceSpawn* getCurrentSpawn(const String& restype, const String& zoneName);

	ResourceSpawn* getFromRandomPool(const String& type);

	void addNodeToListBox(SuiListBox* sui, const String& nodeName);
	String addParentNodeToListBox(SuiListBox* sui, const String& currentNode);

	inline ResourceMap* getResourceMap() {
		return resourceMap;
	}

private:

	void loadResourceSpawns();
	String makeResourceName(bool isOrganic);
	int randomizeValue(int min, int max);
	long getRandomExpirationTime(ResourceTreeEntry* resourceEntry);
	long getRandomUnixTimestamp(int min, int max);

	Vector<String>& getJtlResources();
	Vector<String>& getActiveResourceZones();

	friend class ResourceTree;
	friend class ResourceManager;
	friend class NativePool;
};

#endif /* RESOURCESPAWNER_H_ */
