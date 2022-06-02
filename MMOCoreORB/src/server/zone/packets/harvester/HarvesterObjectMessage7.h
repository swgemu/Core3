#ifndef HARVESTEROBJECTMESSAGE7_H_
#define HARVESTEROBJECTMESSAGE7_H_

#include "server/zone/packets/BaseLineMessage.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/installation/InstallationSynchronizedUi.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/Zone.h"

class HarvesterObjectMessage7 : public BaseLineMessage {
public:
	HarvesterObjectMessage7(HarvesterObject* hino, InstallationSynchronizedUi* uiData)
			: BaseLineMessage(hino->getObjectID(), 0x48494E4F, 7, 0x05) {

		insertByte(uiData->getResourcesModified());

		const DeltaVector<uint64>* resourcePools = uiData->getResourcePools();
		resourcePools->insertToMessage(this);

		const DeltaVector<uint64>* resourceTypesId = uiData->getResourceTypesId();
		resourceTypesId->insertToMessage(this);

		const DeltaVector<String>* resourceTypesName = uiData->getResourceTypesName();
		resourceTypesName->insertToMessage(this);

		const DeltaVector<String>* resourceTypesParent = uiData->getResourceTypesParent();
		resourceTypesParent->insertToMessage(this);

		insertLong(uiData->getSelectedResourcePoolId());
		insertByte(uiData->isActive());
		insertInt(uiData->getMaxExtractionRate());
		insertFloat(uiData->getCurrentExtractionRate());

		insertFloat(uiData->getInstalledExtractionRate());

		insertFloat(uiData->getHopperContentsCur());
		insertInt(uiData->getHopperContentsMax());

		insertByte(uiData->getHopperContentsModified());

		const DeltaVectorMap<uint64, float>* hopperContents = uiData->getHopperContents();
		hopperContents->insertToMessage(this);

		insertByte(uiData->getCondition());

		setSize();

	}
};

#endif /*HARVESTEROBJECTMESSAGE7_H_*/
