#ifndef SHIPHARDPOINTDATA_H_
#define SHIPHARDPOINTDATA_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"

class ShipCollisionHardpoint {
protected:
	String appearanceName;
	String hardpointName;
	Sphere sphere;
	AABB box;

	const Matrix4* rotation;
public:
	ShipCollisionHardpoint() {
		rotation = nullptr;
	}

	ShipCollisionHardpoint(const String& hardpointAppearance, const String& hardpointSlotName, const Vector3& hardpointPosition, const Matrix4* hardpointRotation, float hardpointRange) {
		appearanceName = hardpointAppearance;
		hardpointName = hardpointSlotName;

		sphere = Sphere(hardpointPosition, hardpointRange);
		rotation = hardpointRotation;
	}

	const String& getAppearanceName() const {
		return appearanceName;
	}

	const String& getHardpointName() const {
		return hardpointName;
	}

	const Sphere& getSphere() const {
		return sphere;
	}

	const AABB& getBox() const {
		return box;
	}

	const Matrix4* getRotation() const {
		return rotation;
	}
};

class ShipCollisionData : public Object, public Logger {
private:
	const static constexpr float MeshCollisionThreshold = 32.f;

public:
	enum CollisionVolumeType : int {
		RADIUS = 0,
		MESH = 1,
		BOX = 2,
	};

protected:
	VectorMap<String, VectorMap<uint32, ShipCollisionHardpoint>> hardPointMap;
	VectorMap<uint32, uint32> slotWeights;

	Sphere boundingSphere;
	Sphere chassisSphere;
	AABB chassisBox;

	int volumeType;

public:
	ShipCollisionData(const String& shipName, const ShipChassisData* chassisData) : Object() {
		setLoggingName("ShipCollisionData");

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

		hardPointMap.setNoDuplicateInsertPlan();
		slotWeights.setNoDuplicateInsertPlan();
		slotWeights.setNullValue(0);
		volumeType = CollisionVolumeType::RADIUS;

		setVolumeType(shipTemplate);
		setBoundingData(shipTemplate);
		setCollisionData(shipTemplate, chassisData);
		setComponentData(shipTemplate, chassisData);
	}

	const BaseBoundingVolume* getCollisionVolume(SharedObjectTemplate* templateData) {
		auto appearance = templateData->getAppearanceTemplate();

		if (appearance == nullptr) {
			return nullptr;
		}

		return appearance->getCollisionVolume();
	}

	const BaseBoundingVolume* getBoundingVolume(SharedObjectTemplate* templateData) {
		auto appearance = templateData->getAppearanceTemplate();

		if (appearance == nullptr) {
			return nullptr;
		}

		return appearance->getBoundingVolume();
	}

	void setVolumeType(SharedObjectTemplate* templateData) {
		auto collisionVolume = getCollisionVolume(templateData);

		if (collisionVolume != nullptr) {
			if (collisionVolume->isBoundingSphere()) {
				volumeType = CollisionVolumeType::RADIUS;
			} else if (collisionVolume->isBoundingBox()) {
				volumeType = CollisionVolumeType::BOX;
			} else {
				volumeType = CollisionVolumeType::MESH;
			}

			return;
		}

		auto boundingVolume = getBoundingVolume(templateData);

		if (boundingVolume == nullptr) {
			return;
		}

		if (boundingVolume->getBoundingSphere().getRadius() >= MeshCollisionThreshold) {
			volumeType = CollisionVolumeType::MESH;
		} else {
			volumeType = CollisionVolumeType::RADIUS;
		}
	}

	void setBoundingData(SharedObjectTemplate* templateData) {
		auto boundingVolume = getBoundingVolume(templateData);

		if (boundingVolume == nullptr) {
			return;
		}

		const auto& sphere = boundingVolume->getBoundingSphere();
		float radius = sphere.getCenter().length() + sphere.getRadius();

		boundingSphere = Sphere(Vector3::ZERO, radius);
	}

	void setCollisionData(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData) {
		auto collisionVolume = getCollisionVolume(templateData);

		if (collisionVolume != nullptr) {
			chassisSphere = collisionVolume->getBoundingSphere();
			chassisBox = collisionVolume->getBoundingBox();
		} else {
			chassisSphere = boundingSphere;
		}
	}

	void setComponentData(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData) {
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

			auto hardPoints = VectorMap<uint32, ShipCollisionHardpoint>();
			hardPoints.setAllowDuplicateInsertPlan();

			const auto& compData = slotData->getComponentHardpoints();

			for (int i = 0; i < compData.size(); ++i) {
				const auto& componentName = compData.elementAt(i).getKey();
				const auto& componentEntry = compData.elementAt(i).getValue();

				for (int ii = 0; ii < componentEntry.size(); ++ii) {
					auto componentHardpoint = componentEntry.get(ii);

					if (componentHardpoint == nullptr) {
						continue;
					}

					float hardpointRadius = componentHardpoint->getRange();
					if (hardpointRadius <= 0.f && slot <= Components::FIGHTERSLOTMAX) {
						continue;
					}

					const auto& attachmentName = componentHardpoint->getTemplateName();
					const auto& hardpointName = componentHardpoint->getHardpointName();

					auto transformRotation = hardpointTransforms.get(hardpointName);
					auto transformPosition = Vector3(transformRotation[3][0], transformRotation[3][1], transformRotation[3][2]);

					auto hardpointPosition = transformPosition;
					transformRotation.setTranslation(0,0,0);

					if (attachmentName != "") {
						String templatePath = getAppearanceFileName(attachmentName, slot);

						if (templatePath != "") {
							auto attachmentTemplate = TemplateManager::instance()->getTemplate(templatePath.hashCode());

							if (attachmentTemplate != nullptr) {
								auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(attachmentTemplate);

								if (shot != nullptr) {
									auto shotAppearance = shot->getAppearanceTemplate();

									if (shotAppearance != nullptr) {
										auto hardpointBounding = shotAppearance->getBoundingVolume();

										if (hardpointBounding != nullptr) {
											const auto& attachmentSphere = hardpointBounding->getBoundingSphere();

											float phiY = atan2(-transformRotation[1][1], sqrt(transformRotation[1][0] * transformRotation[1][0] + transformRotation[1][2] * transformRotation[1][2]));

											if (phiY > 0.f) {
												hardpointPosition = transformPosition + ((attachmentSphere.getCenter() * 2.f) * transformRotation);
											} else {
												hardpointPosition = transformPosition + (attachmentSphere.getCenter() * transformRotation);
											}

											hardpointRadius = attachmentSphere.getRadius();

											const auto& attachmentTransforms = shotAppearance->getHardpoints();

											if (attachmentTransforms.contains("turretpitch1")) {
												auto attachmentRotation = attachmentTransforms.get("turretpitch1");
												auto attachmentPosition = Vector3(attachmentRotation[3][0], attachmentRotation[3][1], attachmentRotation[3][2]);

												transformRotation = transformRotation * attachmentRotation;
												transformRotation.setTranslation(0,0,0);

												float phiP = atan2(-transformRotation[1][1], sqrt(transformRotation[1][0] * transformRotation[1][0] + transformRotation[1][2] * transformRotation[1][2]));

												if (phiP > 0.f) {
													hardpointPosition = transformPosition + ((attachmentSphere.getCenter() * 2.f) * transformRotation);
												} else {
													hardpointPosition = transformPosition + (attachmentSphere.getCenter() * transformRotation);
												}
											}
										}
									}
								}
							}
						}
					}

					if (hardpointRadius == 0.f) {
						continue;
					}

					auto hardpointRotation = new Matrix4(transformRotation);

					hardPoints.put(componentName.hashCode(), ShipCollisionHardpoint(attachmentName, hardpointName, hardpointPosition, hardpointRotation, hardpointRadius));
				}
			}

			if (hardPoints.size() > 0) {
				hardPointMap.put(Components::shipComponentSlotToString(slot), hardPoints);
			}

			int slotWeight = slotData->getHitWeight();

			if (slotData->getHitWeight() != 0) {
				slotWeights.put(slot, slotWeight);
			}
		}
	}

	String getAppearanceFileName(const String& attachmentName, int slot) const {
		switch (slot) {
			case Components::ENGINE:  return "object/tangible/ship/attachment/engine/" + attachmentName + ".iff";
			case Components::SHIELD0:
			case Components::SHIELD1:  return "object/tangible/ship/attachment/shield/" + attachmentName + ".iff";
			case Components::BOOSTER:  return "object/tangible/ship/attachment/booster/" + attachmentName + ".iff";
			case Components::BRIDGE:  return "object/tangible/ship/attachment/bridge/" + attachmentName + ".iff";
			case Components::HANGAR:  return "object/tangible/ship/attachment/hangar/" + attachmentName + ".iff";
			default: {
				if (slot >= Components::WEAPON_START) {
					return "object/tangible/ship/attachment/weapon/" + attachmentName + ".iff";
				}
			}
		}

		return "";
	}

	String getShipFileName(const String& shipName) const {
		String chassisName = shipName.replaceAll("shared_", "");

		if (!chassisName.contains(".iff")) {
			String path = chassisName.contains("player_") ? "object/ship/player/" : "object/ship/";
			chassisName = path + chassisName + ".iff";
		}

		return chassisName;
	}

	const VectorMap<uint32, ShipCollisionHardpoint>& getHardpoints(const String& slotName) const {
		return hardPointMap.get(slotName);
	}

	int getSlotWeight(uint32 slot) const {
		return slotWeights.get(slot);
	}

	const Sphere& getBoundingSphere() const {
		return boundingSphere;
	}

	const Sphere& getChassisSphere() const {
		return chassisSphere;
	}

	const AABB& getChassisBox() const {
		return chassisBox;
	}

	int getVolumeType() const {
		return volumeType;
	}
};

#endif // SHIPHARDPOINTDATA_H_
