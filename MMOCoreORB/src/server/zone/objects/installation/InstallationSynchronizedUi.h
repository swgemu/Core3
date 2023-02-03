/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLATIONSYNCHRONIZEDUI_H_
#define INSTALLATIONSYNCHRONIZEDUI_H_

#include "engine/engine.h"
#include "system/util/VectorMap.h"
#include "system/lang/String.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/installation/InstallationResourceData.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/scene/variables/DeltaVectorMap.h"

#include "engine/util/json_utils.h"

class InstallationSynchronizedUi : public Object {
	uint8 resourcesModified;
	DeltaVector<uint64> resourcePools;
	DeltaVector<uint64> resourceTypesId;
	DeltaVector<String> resourceTypesName;
	DeltaVector<String> resourceTypesParent;

	uint64 selectedResourcePoolId;
	bool active;

	int maxExtractionRate;
	float currentExtractionRate;
	float installedExtractionRate;

	int hopperContentsMax;
	uint8 hopperContentsModified;
	DeltaVectorMap<uint64, float> hopperContents;
	float hopperContentsCur;
	int8 condition;

	ManagedWeakReference<SceneObject*> owner;


public:
	InstallationSynchronizedUi(SceneObject* newOwner) : Object() {
		resourcesModified = 0;
		selectedResourcePoolId = 0;
		active = false;
		maxExtractionRate = 0;
		currentExtractionRate = 0.0f;
		installedExtractionRate = 0.0f;
		hopperContentsMax = 0;
		hopperContentsModified = 0;
		hopperContentsCur = 0.0f;
		condition = 0;
		owner = newOwner;

		resetResourcePools();
	}

	InstallationSynchronizedUi(const InstallationSynchronizedUi& data) : Object() {
		resourcesModified = data.resourcesModified;
		resourcePools = data.resourcePools;
		resourceTypesId = data.resourceTypesId;
		resourceTypesName = data.resourceTypesName;
		resourceTypesParent = data.resourceTypesParent;
		selectedResourcePoolId = data.selectedResourcePoolId;
		active = data.active;
		maxExtractionRate = data.maxExtractionRate;
		currentExtractionRate = data.currentExtractionRate;
		installedExtractionRate = data.installedExtractionRate;
		hopperContentsMax = data.hopperContentsMax;
		hopperContentsModified = data.hopperContentsModified;
		hopperContents = data.hopperContents;
		hopperContentsCur = data.hopperContentsCur;
		condition = data.condition;
	}

	InstallationSynchronizedUi& operator=(const InstallationSynchronizedUi& data) {
		if (this == &data)
			return *this;

		resourcesModified = data.resourcesModified;
		resourcePools = data.resourcePools;
		resourceTypesId = data.resourceTypesId;
		resourceTypesName = data.resourceTypesName;
		resourceTypesParent = data.resourceTypesParent;
		selectedResourcePoolId = data.selectedResourcePoolId;
		active = data.active;
		maxExtractionRate = data.maxExtractionRate;
		currentExtractionRate = data.currentExtractionRate;
		installedExtractionRate = data.installedExtractionRate;
		hopperContentsMax = data.hopperContentsMax;
		hopperContentsModified = data.hopperContentsModified;
		hopperContents = data.hopperContents;
		hopperContentsCur = data.hopperContentsCur;
		condition = data.condition;

		return *this;
	}

	friend void to_json(nlohmann::json& j, const InstallationSynchronizedUi& data) {
		j["resourcesModified"] = data.resourcesModified;
		j["resourcePools"] = data.resourcePools;
		j["resourceTypesId"] = data.resourceTypesId;
		j["resourceTypesName"] = data.resourceTypesName;
		j["resourceTypesParent"] = data.resourceTypesParent;
		j["selectedResourcePoolId"] = data.selectedResourcePoolId;
		j["active"] = data.active;
		j["maxExtractionRate"] = data.maxExtractionRate;
		j["currentExtractionRate"] = data.currentExtractionRate;
		j["installedExtractionRate"] = data.installedExtractionRate;
		j["hopperContentsMax"] = data.hopperContentsMax;
		j["hopperContentsModified"] = data.hopperContentsModified;
		j["hopperContents"] = data.hopperContents;
		j["hopperContentsCur"] = data.hopperContentsCur;
		j["condition"] = data.condition;
	}

	inline uint8 getResourcesModified() {
		return resourcesModified;
	}

	const DeltaVector<uint64>* getResourcePools() {
		return &resourcePools;
	}

	const DeltaVector<uint64>* getResourceTypesId() {
		return &resourceTypesId;
	}

	const DeltaVector<String>* getResourceTypesName() {
		return &resourceTypesName;
	}

	const DeltaVector<String>* getResourceTypesParent() {
		return &resourceTypesParent;
	}

	inline uint64 getSelectedResourcePoolId() {
		return selectedResourcePoolId;
	}

	inline bool isActive() {
		return active;
	}

	inline int getMaxExtractionRate() {
		return maxExtractionRate;
	}

	inline float getCurrentExtractionRate() {
		return currentExtractionRate;
	}

	inline float getInstalledExtractionRate() {
		return installedExtractionRate;
	}

	inline int getHopperContentsMax() {
		return hopperContentsMax;
	}

	inline uint8 getHopperContentsModified() {
		return hopperContentsModified;
	}

	const DeltaVectorMap<uint64, float>* getHopperContents() {
		return &hopperContents;
	}

	inline float getHopperContentsCur() {
		return hopperContentsCur;
	}

	inline int8 getCondition() {
		return condition;
	}

	void setOwner(SceneObject* newOwner) {
		owner = newOwner;
	}

	void getResourceData(Vector<InstallationResourceData*>& resourceData);
	InstallationResourceData* makeInstallationResourceData(SceneObject* installation, uint64 resourceId, float posX, float posY, String zoneName);
	void clearResources();
	void clearResourceTypes();
	void addResource(uint64 resourceId);
	void refresh();
	void resetResourcePools();
};

#endif /*INSTALLATIONSYNCHRONIZEDUI_H_*/