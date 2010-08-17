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

void ResourceManagerImplementation::initialize() {
	Lua::init();

	info("building resource tree");
	resourceSpawner = new ResourceSpawner(zoneServer, processor, objectManager);

	info("loading configuration");
	if(!loadConfigData()) {

		loadDefaultConfig();

		info("***** ERROR in configuration, using default values");
	}

	info("starting resource spawner");
	startResourceSpawner();
	info("resource manager initialized");

}

bool ResourceManagerImplementation::loadConfigFile() {
	return runFile("scripts/resources/config.lua");
}

int ResourceManagerImplementation::notifyObserverEvent(uint32 eventType, Observable* observable, ManagedObject* arg1, int64 arg2) {
	if (eventType == ObserverEventType::POSTURECHANGED) {
		CreatureObject* creature = (CreatureObject*) observable;
		// Cancel Sampling on posture change
		Reference<SampleTask*> task = (SampleTask*) creature->getPendingTask("sample");
		Reference<SampleResultsTask*> sampleResultsTask = (SampleResultsTask*) creature->getPendingTask("sampleresults");

		if (task != NULL) {

			task->stopSampling();
			creature->removePendingTask("sample");

			if(sampleResultsTask != NULL) {
				sampleResultsTask->cancel();
				creature->removePendingTask("sampleresults");
			}

			ChatSystemMessage* sysMessage = new ChatSystemMessage("survey","sample_cancel");
			creature->sendSystemMessage("survey", "sample_cancel");
		}
	}

	return 1;
}

bool ResourceManagerImplementation::loadConfigData() {
	if (!loadConfigFile())
		return false;

	String zonesString = getGlobalString("activeZones");

	StringTokenizer zonesTokens(zonesString);
	zonesTokens.setDelimeter(",");

	while(zonesTokens.hasMoreTokens()) {
		int token = zonesTokens.getIntToken();
		resourceSpawner->addPlanet(token);
	}

	shiftInterval = getGlobalInt("averageShiftTime");

	int aveduration = getGlobalInt("aveduration");
	float spawnThrottling = float(getGlobalInt("spawnThrottling")) / 100.0f;
	int lowerGateOverride = getGlobalInt("lowerGateOverride");
	int maxSpawnQuantity = getGlobalInt("maxSpawnQuantity");

	resourceSpawner->setSpawningParameters(aveduration,
			spawnThrottling, lowerGateOverride, maxSpawnQuantity);

	String minpoolinc = getGlobalString("minimumpoolincludes");
	String minpoolexc = getGlobalString("minimumpoolexcludes");
	resourceSpawner->initializeMinimumPool(minpoolinc, minpoolexc);

	String randpoolinc = getGlobalString("randompoolincludes");
	String randpoolexc = getGlobalString("randompoolexcludes");
	int randpoolsize = getGlobalInt("randompoolsize");
	resourceSpawner->initializeRandomPool(randpoolinc, randpoolexc, randpoolsize);

	String fixedpoolinc = getGlobalString("fixedpoolincludes");
	String fixedpoolexc = getGlobalString("fixedpoolexcludes");
	resourceSpawner->initializeFixedPool(fixedpoolinc, fixedpoolexc);

	String natpoolinc = getGlobalString("nativepoolincludes");
	String natpoolexc = getGlobalString("nativepoolexcludes");
	resourceSpawner->initializeNativePool(natpoolinc, natpoolexc);

	return true;
}

void ResourceManagerImplementation::loadDefaultConfig() {
	for(int i = 0;i < 10; ++i) {
		resourceSpawner->addPlanet(i);
	}

	shiftInterval = 7200000;
	resourceSpawner->setSpawningParameters(86400, 90, 1000, 0);
}

void ResourceManagerImplementation::stop() {


}

void ResourceManagerImplementation::startResourceSpawner() {
	Locker _locker(_this);

	resourceSpawner->start();

	ResourceShiftTask* resourceShift = new ResourceShiftTask(_this);
	resourceShift->schedule(shiftInterval);
}

void ResourceManagerImplementation::shiftResources() {
	Locker _locker(_this);

	resourceSpawner->shiftResources();

	ResourceShiftTask* resourceShift = new ResourceShiftTask(_this);
	resourceShift->schedule(shiftInterval);
}

void ResourceManagerImplementation::sendResourceListForSurvey(PlayerCreature* playerCreature, const int toolType, const String& surveyType) {
	rlock();

	try {
		resourceSpawner->sendResourceListForSurvey(playerCreature, toolType, surveyType);
	} catch (...) {
		error("unreported exception caught in ResourceManagerImplementation::sendResourceListForSurvey");
	}

	runlock();
}

ResourceContainer* ResourceManagerImplementation::harvestResource(PlayerCreature* player, const String& type, const int quantity) {
	return resourceSpawner->harvestResource(player, type, quantity);
}

void ResourceManagerImplementation::sendSurvey(PlayerCreature* playerCreature, const String& resname) {
	resourceSpawner->sendSurvey(playerCreature, resname);
}

void ResourceManagerImplementation::sendSample(PlayerCreature* playerCreature, const String& resname, const String& sampleAnimation) {
	resourceSpawner->sendSample(playerCreature, resname, sampleAnimation);

	playerCreature->registerObserver(ObserverEventType::POSTURECHANGED, _this);
}

void ResourceManagerImplementation::createResourceSpawn(PlayerCreature* playerCreature, const String& restype) {
	Locker _locker(_this);

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

		spawn = resourceMap->get(spawnName);
	} catch (...) {

	}

	runlock();

	return spawn;
}

void ResourceManagerImplementation::getResourceListByType(Vector<ManagedReference<ResourceSpawn*> >& list, int type, int zoneid) {
	list.removeAll();

	rlock();

	ManagedReference<ResourceSpawn*> resourceSpawn;

	try {
		ResourceMap* resourceMap = resourceSpawner->getResourceMap();

		ZoneResourceMap* zoneMap = resourceMap->getZoneResourceList(zoneid);

		if (zoneMap != NULL) {
			for (int i = 0; i < zoneMap->size(); ++i) {
				resourceSpawn = zoneMap->get(i);

				if (resourceSpawn->getSurveyToolType() == type) {
					list.add(resourceSpawn);
				}
			}

		}

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in void ResourceManagerImplementation::getResourceListByType(Vector<ManagedReference<ResourceSpawn*> >& list, int type, int zoneid)");
	}

	runlock();
}

uint64 ResourceManagerImplementation::getAvailablePowerFromPlayer(PlayerCreature* player) {
	SceneObject* inventory = player->getSlottedObject("inventory");
	uint64 power = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		ManagedReference<SceneObject*> tano = (SceneObject*) inventory->getContainerObject(i);

		if (tano->isResourceContainer()) {
			ResourceContainer* rcno = (ResourceContainer*) tano.get();
			ResourceSpawn* spawn = rcno->getSpawnObject();

			if (spawn->isEnergy()) {
				int PE = spawn->getValueOf(3); // potential energy

				if (PE > 500)
					power += (unsigned long long) ( (PE /* * 1.0 */) / 500.0 * (rcno->getQuantity() /* * 1.0 */) );
				else
					power += rcno->getQuantity();
			}
		}
	}

	return power;
}

void ResourceManagerImplementation::removePowerFromPlayer(PlayerCreature* player, uint64 power) {
	if (power == 0)
		return;

	SceneObject* inventory = player->getSlottedObject("inventory");

	uint64 containerPower = 0;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++ && power > 0) {
		ManagedReference<SceneObject*> tano = inventory->getContainerObject(i);

		if (tano->isResourceContainer()) {
			ResourceContainer* rcno = (ResourceContainer*)tano.get();
			ResourceSpawn* spawn = rcno->getSpawnObject();

			if (spawn->isEnergy()) {
				int PE = spawn->getAttributeValue(3); // potential energy

				if (PE > 500)
					containerPower = (unsigned long long) ( (PE  /* * 1.0 */) / 500.0 * (rcno->getQuantity() /* * 1.0*/) );
				else
					containerPower = rcno->getQuantity();

				if (containerPower > power) {
					// remove
					uint64 consumedUnits = (unsigned long long) ( (power /* * 1.0 */) / ( (containerPower /* * 1.0*/) / rcno->getQuantity() ) );
					power = 0; // zero it down

					rcno->setQuantity(rcno->getQuantity() - consumedUnits);
				} else {
					power -= containerPower;

					inventory->removeObject(rcno, true);
					rcno->destroyObjectFromDatabase(true);
				}
			}
		}

	}
}
