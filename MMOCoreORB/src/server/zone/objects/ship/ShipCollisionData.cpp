#include "server/zone/objects/ship/ShipCollisionData.h"
#include "templates/manager/DataArchiveStore.h"

ShipCollisionData::ShipCollisionData(const String& shipName, const ShipChassisData* chassisData) : Object() {
	setLoggingName("ShipCollisionData " + shipName);

	const String& templatePath = getShipFileName(shipName);

	if (templatePath == "") {
		return;
	}

	auto templateData = TemplateManager::instance()->getTemplate(templatePath.hashCode());

	if (templateData == nullptr) {
		return;
	}

	auto shipTemplate = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (shipTemplate == nullptr) {
		return;
	}

	hardpointMap.setNoDuplicateInsertPlan();
	slotWeights.setNoDuplicateInsertPlan();
	slotWeights.setNullValue(0);
	volumeType = INVALID;

	setCollisionData(shipTemplate);
	setClientData(shipTemplate);
	setComponentData(shipTemplate, chassisData);
	setSlotWeights(shipTemplate, chassisData);

	for (int i = 0; i < hardpointMap.size(); ++i) {
		hardpointSize += hardpointMap.elementAt(i).getValue().size();
	}
}

void ShipCollisionData::setCollisionData(SharedShipObjectTemplate* templateData) {
	appearance = templateData->getAppearanceTemplate();

	if (appearance == nullptr || templateData->getAppearanceFilename() == "") {
		auto portalLayout = templateData->getPortalLayout();

		if (portalLayout != nullptr && portalLayout->getCellTotalNumber() > 0) {
			appearance = portalLayout->getAppearanceTemplate(0);
		}
	}

	if (appearance == nullptr) {
		return;
	}

	auto boundingVolume = appearance->getBoundingVolume();

	if (boundingVolume == nullptr) {
		return;
	}

	auto collisionVolume = appearance->getCollisionVolume();

	if (collisionVolume == nullptr) {
		collisionVolume = boundingVolume;
	}

	boundingSphere = getChassisBoundingSphere(boundingVolume);
	chassisSphere = collisionVolume->getBoundingSphere();
	chassisBox = collisionVolume->getBoundingBox();
	volumeType = getBoundingVolumeType(collisionVolume);
}

void ShipCollisionData::setClientData(SharedShipObjectTemplate* shipTemplate) {
	auto clientDataPath = shipTemplate->getClientDataFile();

	if (clientDataPath == "") {
		return;
	}

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile(clientDataPath.toLowerCase());

	if (iffStream == nullptr || iffStream->getNextFormType() != 'CLDF') {
		return;
	}

	try {

	iffStream->openForm('CLDF');
	int wingCount = 0;

	if (iffStream->getNextFormType() == '0000') {
		iffStream->openForm('0000');

		for (int i = 0; i < iffStream->getSubChunksNumber(); ++i) {
			auto chunk = iffStream->openChunk();
			if (chunk == nullptr) {
				break;
			}

			uint32 chunkID = chunk->getChunkID();

			if (chunkID == 'HOBJ') {
				String attachmentName = chunk->readString();
				String hardpointName = chunk->readString();

				addCollisionHardpoint(shipTemplate, "chassis", attachmentName, hardpointName, Components::CHASSIS, -1.f);
			}

			iffStream->closeChunk();
		}

		iffStream->closeForm('0000');
	}

	} catch (Exception& e) {
		error() << e.what();
		e.printStackTrace();
	}

	iffStream->closeForm('CLDF');
	delete iffStream;
}

void ShipCollisionData::setComponentData(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData) {
	auto appearance = templateData->getAppearanceTemplate();

	if (appearance == nullptr) {
		return;
	}

	const auto& hardpointTransforms = appearance->getHardpoints();

	if (hardpointTransforms.size() == 0) {
		return;
	}

	for (uint32 slot = 0; slot <= Components::CAPITALSLOTMAX; ++slot) {
		auto slotData = chassisData->getComponentSlotData(slot);

		if (slotData == nullptr) {
			continue;
		}

		const auto& compData = slotData->getComponentHardpoints();

		for (int i = 0; i < compData.size(); ++i) {
			const auto& componentName = compData.elementAt(i).getKey();
			const auto& componentEntry = compData.elementAt(i).getValue();

			for (int ii = 0; ii < componentEntry.size(); ++ii) {
				auto componentHardpoint = componentEntry.get(ii);

				if (componentHardpoint == nullptr) {
					continue;
				}

				const auto& attachmentName = componentHardpoint->getTemplateName();
				const auto& hardpointName = componentHardpoint->getHardpointName();
				float hardpointRadius = componentHardpoint->getRange();

				if (hardpointRadius <= 0.f) {
					continue;
				}

				String attachmentFileName = "";

				if (attachmentName != "") {
					String attachmentPath = getAttachmentTemplatePath(attachmentName, slot);
					auto attachmentTemplate = TemplateManager::instance()->getTemplate(attachmentPath.hashCode());

					if (attachmentTemplate != nullptr) {
						attachmentFileName = attachmentTemplate->getAppearanceFilename();
					}
				}

				if (attachmentFileName != "") {
					addCollisionHardpoint(templateData, componentName, attachmentFileName, hardpointName, slot, hardpointRadius);
				} else {
					addCollisionHardpoint(templateData, componentName, hardpointName, slot, hardpointRadius);
				}
			}
		}
	}
}

void ShipCollisionData::setSlotWeights(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData) {
	for (uint32 slot = 0; slot <= Components::CAPITALSLOTMAX; ++slot) {
		auto slotData = chassisData->getComponentSlotData(slot);

		if (slotData == nullptr) {
			continue;
		}

		int slotWeight = slotData->getHitWeight();

		if (slotData->getHitWeight() != 0) {
			slotWeights.put(slot, slotWeight);
		}
	}
}

void ShipCollisionData::addCollisionHardpoint(SharedShipObjectTemplate* shipTemplate, const String& componentName, const String& hardpointName, int slot, float radius) {
	auto shipAppearance = shipTemplate->getAppearanceTemplate();

	if (shipAppearance == nullptr || hardpointName == "") {
		return;
	}

	const auto& hardpointTransforms = shipAppearance->getHardpoints();

	Matrix4 hardpointRotation = hardpointTransforms.get(hardpointName);
	Vector3 hardpointPosition = Vector3(hardpointRotation[3][0], hardpointRotation[3][1], hardpointRotation[3][2]);
	hardpointRotation.setTranslation(0,0,0);

	Sphere hardpointSphere = getHardpointBoundingSphere(Sphere(Vector3::ZERO, radius), hardpointPosition, hardpointRotation);
	const auto& slotName = Components::shipComponentSlotToString(slot);

	if (!hardpointMap.contains(slotName)) {
		auto hardPoints = VectorMap<uint32, ShipCollisionHardpoint>();
		hardPoints.setAllowDuplicateInsertPlan();
		hardpointMap.put(slotName, std::move(hardPoints));
	}

	auto collisionEntry = ShipCollisionHardpoint(componentName, hardpointName);
	collisionEntry.setPosition(hardpointPosition);
	collisionEntry.setSphere(hardpointSphere);
	collisionEntry.setVolumeType(RADIUS);
	collisionEntry.setRadius(radius);
	collisionEntry.setSlot(slot);

	auto hardPointEntry = &hardpointMap.get(slotName);
	hardPointEntry->put(componentName.hashCode(), std::move(collisionEntry));
}

void ShipCollisionData::addCollisionHardpoint(SharedShipObjectTemplate* shipTemplate, const String& componentName, const String& attachmentName, const String& hardpointName, int slot, float radius) {
	auto shipAppearance = shipTemplate->getAppearanceTemplate();

	if (shipAppearance == nullptr || attachmentName == "" || hardpointName == "") {
		return;
	}

	auto hardpointAppearance = TemplateManager::instance()->getAppearanceTemplate(attachmentName.replaceAll("shared_", ""));

	if (hardpointAppearance == nullptr) {
		return;
	}

	auto boundingVolume = hardpointAppearance->getBoundingVolume();

	if (boundingVolume == nullptr) {
		return;
	}

	auto collisionVolume = hardpointAppearance->getCollisionVolume();

	if (collisionVolume == nullptr) {
		collisionVolume = boundingVolume;
	}

	const AABB& box = collisionVolume->getBoundingBox();
	const Sphere& boundingSphere = collisionVolume->getBoundingSphere();
	const Vector3& boundingPosition = boundingSphere.getCenter();
	float boundingRadius = boundingSphere.getRadius();

	const auto& hardpointTransforms = shipAppearance->getHardpoints();

	Matrix4 hardpointRotation = hardpointTransforms.get(hardpointName);
	Vector3 hardpointPosition = Vector3(hardpointRotation[3][0], hardpointRotation[3][1], hardpointRotation[3][2]);

	hardpointRotation.setTranslation(0,0,0);

	const auto& attachmentTransforms = hardpointAppearance->getHardpoints();

	if (attachmentTransforms.contains("turretpitch1")) {
		auto attachmentRotation = attachmentTransforms.get("turretpitch1");
		auto attachmentPosition = Vector3(attachmentRotation[3][0], attachmentRotation[3][1], attachmentRotation[3][2]);

		attachmentRotation.setTranslation(0,0,0);
		hardpointRotation = hardpointRotation * attachmentRotation;
	}

	Sphere hardpointSphere = getHardpointBoundingSphere(Sphere(Vector3::ZERO, boundingRadius), hardpointPosition, hardpointRotation);
	AABB hardpointBox = getHardpointBoundingBox(box, hardpointPosition, hardpointRotation);
	int hardpointType = getBoundingVolumeType(collisionVolume);
	float hardpointRadius = Math::max(boundingRadius, radius);

	if (hardpointType == BOX) {
		hardpointSphere = getHardpointBoundingSphere(box, hardpointPosition, hardpointRotation);
	}

	const auto& slotName = Components::shipComponentSlotToString(slot);

	if (!hardpointMap.contains(slotName)) {
		auto hardPoints = VectorMap<uint32, ShipCollisionHardpoint>();
		hardPoints.setAllowDuplicateInsertPlan();
		hardpointMap.put(slotName, std::move(hardPoints));
	}

	auto collisionEntry = ShipCollisionHardpoint(componentName, hardpointName);
	collisionEntry.setAppearanceTemplate(hardpointAppearance);
	collisionEntry.setPosition(hardpointPosition);
	collisionEntry.setSphere(hardpointSphere);
	collisionEntry.setBox(hardpointBox);
	collisionEntry.setVolumeType(hardpointType);
	collisionEntry.setRadius(hardpointRadius);
	collisionEntry.setSlot(slot);

	if (!isIdentityMatrix(hardpointRotation)) {
		collisionEntry.setRotation(new Matrix4(hardpointRotation));
	}

	auto hardPointEntry = &hardpointMap.get(slotName);
	hardPointEntry->put(componentName.hashCode(), std::move(collisionEntry));
}
