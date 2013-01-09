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

#include "engine/engine.h"

#include "ResourceManager.h"
#include "ResourceShiftTask.h"
#include "resourcespawner/SampleTask.h"
#include "resourcespawner/SampleResultsTask.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/resource/ResourceContainerObjectDeltaMessage3.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void ResourceManagerImplementation::initialize() {
	lua = new Lua();
	lua->init();

	if(!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	resourceSpawner->init();

	startResourceSpawner();
}

bool ResourceManagerImplementation::loadConfigFile() {
	return lua->runFile("scripts/managers/resource_manager.lua");
}

int ResourceManagerImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::POSTURECHANGED) {
		CreatureObject* creature = cast<CreatureObject*>( observable);
		// Cancel Sampling on posture change
		Reference<SampleTask*> task = cast<SampleTask*>( creature->getPendingTask("sample"));
		Reference<SampleResultsTask*> sampleResultsTask = cast<SampleResultsTask*>( creature->getPendingTask("sampleresults"));

		if (task != NULL) {

			task->stopSampling();
			//creature->removePendingTask("sample");

			if(sampleResultsTask != NULL) {
				sampleResultsTask->cancel();
				creature->removePendingTask("sampleresults");
			}

			creature->sendSystemMessage("@survey:sample_cancel");
		}
	}

	return 1;
}

bool ResourceManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;

	bool loadFromScript = lua->getGlobalInt("buildInitialResourcesFromScript");

	String zonesString = lua->getGlobalString("activeZones");

	StringTokenizer zonesTokens(zonesString);
	zonesTokens.setDelimeter(",");

	while(zonesTokens.hasMoreTokens()) {
		String zoneName;
		zonesTokens.getStringToken(zoneName);
		resourceSpawner->addZone(zoneName);
	}

	shiftInterval = lua->getGlobalInt("averageShiftTime");

	int aveduration = lua->getGlobalInt("aveduration");
	float spawnThrottling = float(lua->getGlobalInt("spawnThrottling")) / 100.0f;
	int lowerGateOverride = lua->getGlobalInt("lowerGateOverride");
	int maxSpawnQuantity = lua->getGlobalInt("maxSpawnQuantity");

	resourceSpawner->setSpawningParameters(loadFromScript, aveduration,
			spawnThrottling, lowerGateOverride, maxSpawnQuantity);

	String jtlResources = lua->getGlobalString("jtlresources");

	StringTokenizer jtlTokens(jtlResources);
	jtlTokens.setDelimeter(",");

	while(jtlTokens.hasMoreTokens()) {
		String token;
		jtlTokens.getStringToken(token);
		resourceSpawner->addJtlResource(token);
	}

	String minpoolinc = lua->getGlobalString("minimumpoolincludes");
	String minpoolexc = lua->getGlobalString("minimumpoolexcludes");
	resourceSpawner->initializeMinimumPool(minpoolinc, minpoolexc);

	String randpoolinc = lua->getGlobalString("randompoolincludes");
	String randpoolexc = lua->getGlobalString("randompoolexcludes");
	int randpoolsize = lua->getGlobalInt("randompoolsize");
	resourceSpawner->initializeRandomPool(randpoolinc, randpoolexc, randpoolsize);

	String fixedpoolinc = lua->getGlobalString("fixedpoolincludes");
	String fixedpoolexc = lua->getGlobalString("fixedpoolexcludes");
	resourceSpawner->initializeFixedPool(fixedpoolinc, fixedpoolexc);

	String natpoolinc = lua->getGlobalString("nativepoolincludes");
	String natpoolexc = lua->getGlobalString("nativepoolexcludes");
	resourceSpawner->initializeNativePool(natpoolinc, natpoolexc);

	return true;
}

void ResourceManagerImplementation::loadDefaultConfig() {

	resourceSpawner->addZone("corellia");
	resourceSpawner->addZone("lok");
	resourceSpawner->addZone("yavin4");
	resourceSpawner->addZone("dantooine");
	resourceSpawner->addZone("dathomir");
	resourceSpawner->addZone("naboo");
	resourceSpawner->addZone("rori");
	resourceSpawner->addZone("talus");
	resourceSpawner->addZone("tatooine");
	resourceSpawner->addZone("endor");

	shiftInterval = 7200000;
	resourceSpawner->setSpawningParameters(1, 86400, 90, 1000, 0);
}

void ResourceManagerImplementation::stop() {


}

void ResourceManagerImplementation::startResourceSpawner() {
	Locker _locker(_this.get());

	resourceSpawner->start();

	Reference<ResourceShiftTask*> resourceShift = new ResourceShiftTask(_this.get().get());
	resourceShift->schedule(shiftInterval);
}

void ResourceManagerImplementation::shiftResources() {
	Locker _locker(_this.get());

	resourceSpawner->shiftResources();

	Reference<ResourceShiftTask*> resourceShift = new ResourceShiftTask(_this.get().get());
	resourceShift->schedule(shiftInterval);
}

void ResourceManagerImplementation::sendResourceListForSurvey(CreatureObject* playerCreature, const int toolType, const String& surveyType) {
	rlock();

	try {
		resourceSpawner->sendResourceListForSurvey(playerCreature, toolType, surveyType);
	} catch (...) {
		runlock();

		throw;
	}

	runlock();
}

ResourceContainer* ResourceManagerImplementation::harvestResource(CreatureObject* player, const String& type, const int quantity) {
	return resourceSpawner->harvestResource(player, type, quantity);
}
void ResourceManagerImplementation::harvestResourceToPlayer(CreatureObject* player, ResourceSpawn* resourceSpawn, const int quantity) {
	resourceSpawner->harvestResource(player, resourceSpawn, quantity);
}

void ResourceManagerImplementation::sendSurvey(CreatureObject* playerCreature, const String& resname) {
	resourceSpawner->sendSurvey(playerCreature, resname);
}

void ResourceManagerImplementation::sendSample(CreatureObject* playerCreature, const String& resname, const String& sampleAnimation) {
	resourceSpawner->sendSample(playerCreature, resname, sampleAnimation);

	playerCreature->registerObserver(ObserverEventType::POSTURECHANGED, _this.get());
}

void ResourceManagerImplementation::createResourceSpawn(CreatureObject* playerCreature, const String& restype) {
	Locker _locker(_this.get());

	ResourceSpawn* resourceSpawn = resourceSpawner->manualCreateResourceSpawn(restype);

	if (resourceSpawn != NULL) {
		StringBuffer buffer;
		buffer << "Spawned " << resourceSpawn->getName() << " of type " << resourceSpawn->getType();

		playerCreature->sendSystemMessage(buffer.toString());
	} else {
		playerCreature->sendSystemMessage("Could not create spawn " + restype);
	}

}

ResourceSpawn* ResourceManagerImplementation::getResourceSpawn(const String& spawnName) {
	ResourceSpawn* spawn = NULL;

	rlock();

	try {
		ResourceMap* resourceMap = resourceSpawner->getResourceMap();

		spawn = resourceMap->get(spawnName.toLowerCase());
	} catch (...) {
		runlock();

		throw;
	}

	runlock();

	return spawn;
}

ResourceSpawn* ResourceManagerImplementation::getCurrentSpawn(const String& restype, const String& zoneName) {
	return resourceSpawner->getCurrentSpawn(restype, zoneName);
}

void ResourceManagerImplementation::getResourceListByType(Vector<ManagedReference<ResourceSpawn*> >& list, int type, const String& zoneName) {
	list.removeAll();

	rlock();

	ManagedReference<ResourceSpawn*> resourceSpawn;

	try {
		ResourceMap* resourceMap = resourceSpawner->getResourceMap();

		ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(zoneName);

		if (zoneMap != NULL) {
			for (int i = 0; i < zoneMap->size(); ++i) {
				resourceSpawn = zoneMap->get(i);

				if (type == 9){
					if (resourceSpawn->isType("radioactive"))
						list.add(resourceSpawn);
				}

				else if (resourceSpawn->getSurveyToolType() == type) {
					list.add(resourceSpawn);
				}
			}

		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	} catch (...) {
		runlock();

		throw;
	}

	runlock();
}

uint32 ResourceManagerImplementation::getAvailablePowerFromPlayer(CreatureObject* player) {
	SceneObject* inventory = player->getSlottedObject("inventory");
	uint32 power = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		ManagedReference<SceneObject*> obj = cast<SceneObject*>( inventory->getContainerObject(i));

		if (obj == NULL || !obj->isResourceContainer())
			continue;

		ResourceContainer* rcno = cast<ResourceContainer*>( obj.get());
		ManagedReference<ResourceSpawn*> spawn = rcno->getSpawnObject();

		if (spawn == NULL || !spawn->isEnergy())
			continue;

		int quantity = rcno->getQuantity();
		int pe = spawn->getValueOf(CraftingManager::PE); // potential energy

		float modifier = MAX(1.0f, pe / 500.0f);

		power += (uint32) (modifier * quantity);
	}

	return power;
}

void ResourceManagerImplementation::removePowerFromPlayer(CreatureObject* player, uint32 power) {
	if (power == 0)
		return;

	SceneObject* inventory = player->getSlottedObject("inventory");

	uint32 containerPower = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize() && power > 0; ++i) {
		ManagedReference<SceneObject*> obj = inventory->getContainerObject(i);

		if (obj == NULL || !obj->isResourceContainer())
			continue;

		ResourceContainer* rcno = cast<ResourceContainer*>( obj.get());
		ManagedReference<ResourceSpawn*> spawn = rcno->getSpawnObject();

		if (spawn == NULL || !spawn->isEnergy())
			continue;

		int quantity = rcno->getQuantity();
		int pe = spawn->getValueOf(CraftingManager::PE); // potential energy

		float modifier = MAX(1.0f, pe / 500.0f);

		containerPower = modifier * quantity;

		if (containerPower > power) {
			uint32 consumedUnits = (uint64) power / modifier;
			rcno->setQuantity(quantity - consumedUnits);

			ResourceContainerObjectDeltaMessage3* drcno3 = new ResourceContainerObjectDeltaMessage3(rcno);
			drcno3->updateQuantity();
			drcno3->close();
			player->sendMessage(drcno3);
			return;
		} else {
			rcno->destroyObjectFromWorld(true);
			rcno->destroyObjectFromDatabase(true);
		}

		power -= containerPower;
	}
}
void ResourceManagerImplementation::givePlayerResource(CreatureObject* playerCreature, const String& restype, const int quantity) {
	ManagedReference<ResourceSpawn* > spawn = getResourceSpawn(restype);

	if(spawn == NULL) {
		playerCreature->sendSystemMessage("Selected spawn does not exist.");
		return;
	}

	ManagedReference<SceneObject*> inventory = playerCreature->getSlottedObject("inventory");

	if(inventory != NULL && !inventory->hasFullContainerObjects()) {

		ResourceContainer* newResource = spawn->createResource(quantity);

		if(newResource != NULL) {
			spawn->extractResource("", quantity);
			inventory->broadcastObject(newResource, true);
			inventory->transferObject(newResource, -1, true);
		}
	}
}

/// Resource Deed Methods
void ResourceManagerImplementation::addNodeToListBox(SuiListBox* sui, const String& nodeName) {
	resourceSpawner->addNodeToListBox(sui, nodeName);
}

String ResourceManagerImplementation::addParentNodeToListBox(SuiListBox* sui, const String& currentNode) {
	return resourceSpawner->addParentNodeToListBox(sui, currentNode);
}

void ResourceManagerImplementation::listResourcesForPlanetOnScreen(CreatureObject* creature, const String& planet) {
	resourceSpawner->listResourcesForPlanetOnScreen(creature, planet);
}

String ResourceManagerImplementation::healthCheck() {
	return resourceSpawner->healthCheck();
}

String ResourceManagerImplementation::dumpResources() {
	Locker locker(_this.get());
	return resourceSpawner->dumpResources();
}

String ResourceManagerImplementation::despawnResource(String& resourceName) {

	ManagedReference<ResourceSpawn*> spawn = getResourceSpawn(resourceName);
	if(spawn == NULL) {
		return "Spawn not Found";
	}

	spawn->setDespawned(time(0) - 1);
	resourceSpawner->shiftResources();

	return resourceName + " despawned.";
}
