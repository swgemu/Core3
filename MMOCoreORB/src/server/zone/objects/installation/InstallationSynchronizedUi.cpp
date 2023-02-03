#include "server/zone/objects/installation/InstallationSynchronizedUi.h"
#include "server/zone/objects/installation/InstallationResourceData.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

void InstallationSynchronizedUi::getResourceData(Vector<InstallationResourceData*>& resourceData) {
	printf("InstallationSynchronizedUi::getResourceData\n");
	Reference<SceneObject*> installation = owner.get();

	if (installation == nullptr)
		return;
printf("InstallationSynchronizedUi::getResourceData has owner\n");
	ManagedReference<Zone*> zone = installation->getZone();

	if (zone == nullptr)
		return;
printf("InstallationSynchronizedUi::getResourceData valid zone\n");
	String zoneName = zone->getZoneName();
	float posX = installation->getPositionX();
	float posY = installation->getPositionY();

	// Send all the resources on the planet
	for (int i = 0; i < resourcePools.size(); i++) {
		uint64 resourceId = resourcePools.get(i);
		resourceData.add(makeInstallationResourceData(installation, resourceId, posX, posY, zoneName));
	}
printf("InstallationSynchronizedUi::getResourceData added %i pools\n", resourceData.size());
	// Also send the resources in the hopper
	for (int i = 0; i < hopperContents.size(); i++) {
		uint64 resourceId = hopperContents.getKeyAt(i);
		resourceData.add(makeInstallationResourceData(installation, resourceId, posX, posY, zoneName));
	}
	printf("InstallationSynchronizedUi::getResourceData added %i pools\n", resourceData.size());
}

InstallationResourceData* InstallationSynchronizedUi::makeInstallationResourceData(SceneObject* installation, uint64 resourceId, float posX, float posY, String zoneName) {
	if (installation == nullptr || installation->getZone() == nullptr)
		return new InstallationResourceData("", resourceId, "", 0);

	ZoneServer* zoneServer = installation->getZoneServer();

	if (zoneServer == nullptr)
		return new InstallationResourceData("", resourceId, "", 0);

	Reference<ResourceSpawn*> resourceSpawn = zoneServer->getObject(resourceId).castTo<ResourceSpawn*>();

	if (resourceSpawn == nullptr)
		return new InstallationResourceData("", resourceId, "", 0);

	float spawnDensity = resourceSpawn->getDensityAt(installation->getZone()->getZoneName(), posX, posY);
	return new InstallationResourceData(resourceSpawn->getName(), resourceId, resourceSpawn->getType(), (uint8)(spawnDensity * 100.f));
}

void InstallationSynchronizedUi::clearResources() {
	resourcePools.removeAll();
	clearResourceTypes();

	resourcesModified = (uint8)(resourcesModified + 1);
}

void InstallationSynchronizedUi::clearResourceTypes() {
	resourceTypesId.removeAll();
	resourceTypesName.removeAll();
	resourceTypesParent.removeAll();
}

void InstallationSynchronizedUi::addResource(uint64 resourceId) {
	if (resourcePools.contains(resourceId))
		return;

	Reference<SceneObject*> installation = owner.get();

	if (installation == nullptr)
		return;

	ZoneServer* zoneServer = installation->getZoneServer();

	if (zoneServer == nullptr)
		return;

	Reference<ResourceSpawn*> resourceSpawn = zoneServer->getObject(resourceId).castTo<ResourceSpawn*>();

	if (resourceSpawn == nullptr || !resourceSpawn->inShift())
		return;

	resourcePools.add(resourceId);
	resourceTypesId.add(resourceId);
	resourceTypesName.add(resourceSpawn->getName());
	resourceTypesParent.add(resourceSpawn->getType());

	resourcesModified = (uint8)(resourcesModified + 1);
}

void InstallationSynchronizedUi::refresh() {
	printf("InstallationSynchronizedUi::refresh()\n");
	Reference<SceneObject*> installation = owner.get();

	if (installation == nullptr)
		return;

	ManagedReference<HarvesterObject*> harvester = installation.castTo<HarvesterObject*>();

	if (harvester == nullptr)
		return;

	ZoneServer* zoneServer = harvester->getZoneServer();

	if (zoneServer == nullptr)
		return;
printf("InstallationSynchronizedUi::refresh() 2\n");
	selectedResourcePoolId = harvester->getResourceType();
	active = harvester->isActive();
	addResource(selectedResourcePoolId);
	maxExtractionRate = harvester->getMaxExtractionRate();
	currentExtractionRate = harvester->getCurrentExtractionRate();
	installedExtractionRate = harvester->getInstalledExtractionRate();

	float conditionDamage = harvester->getConditionDamage();
	float maxCondition = harvester->getMaxCondition();
	int8 curPercent = (int8)(100 - (100 * (conditionDamage / maxCondition)));

	if (curPercent == 100 && conditionDamage > 0)
		curPercent = 99;

	condition = curPercent;
printf("InstallationSynchronizedUi::refresh() cond %i\n", curPercent);
	for (int i = resourcePools.size() - 1; i >= 0; i--) {
		uint64 resourceId = resourcePools.get(i);

		Reference<ResourceSpawn*> resourceSpawn = zoneServer->getObject(resourceId).castTo<ResourceSpawn*>();

		if (resourceSpawn == nullptr || !resourceSpawn->inShift()) {
			resourcePools.remove(i);
			resourcesModified = (uint8)(resourcesModified + 1);
		}
	}

	hopperContentsMax = harvester->getMaxHopperAmount();

	DeltaVectorMap<uint64, float> newHopperContents;
	float hopperTotal = harvester->getHopperContents(&newHopperContents);

	bool hopperModified = false;

	if (hopperContents.size() != newHopperContents.size()) {
		hopperModified = true;
	}

	for (int i = 0; i < hopperContents.size(); i++) {
		uint64 hopperKey = hopperContents.getKeyAt(i);
		float hopperValue = hopperContents.getValueAt(i);
		uint64 newHopperKey = newHopperContents.getKeyAt(i);
		float newHopperValue = newHopperContents.getValueAt(i);

		addResource(newHopperKey);

		if (hopperKey != newHopperKey || hopperValue != newHopperValue) {
			hopperModified = true;
		}
	}

	if (hopperModified) {
		hopperContentsModified = (uint8)(hopperContentsModified + 1);

		hopperContents.removeAll();

		for (int i = 0; i < newHopperContents.size(); i++) {
			uint64 hopperKey = newHopperContents.getKeyAt(i);
			float hopperValue = newHopperContents.getValueAt(i);
			hopperContents.set(hopperKey, hopperValue);
		}
	}

	hopperContentsCur = hopperTotal;
}

void InstallationSynchronizedUi::resetResourcePools() {
	printf("InstallationSynchronizedUi::resetResourcePools()\n");
	clearResources();

	Reference<SceneObject*> installation = owner.get();

	if (installation == nullptr)
		return;

	ManagedReference<HarvesterObject*> harvester = installation.castTo<HarvesterObject*>();

	if (harvester == nullptr)
		return;

	Vector<ManagedReference<ResourceSpawn*> > resourceList = harvester->getSurveyTypes();
	printf("InstallationSynchronizedUi::resetResourcePools() list size %i\n", resourceList.size());

	for (int i = 0; i < resourceList.size(); i++) {
		ManagedReference<ResourceSpawn*> spawn = resourceList.get(i);

		if (spawn == nullptr)
			continue;

		resourcePools.add(spawn->getObjectID());
		addResource(spawn->getObjectID());
	}

	refresh();
}