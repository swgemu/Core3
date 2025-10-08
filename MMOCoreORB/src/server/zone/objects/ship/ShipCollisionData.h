#ifndef SHIPCOLLISIONDATA_H_
#define SHIPCOLLISIONDATA_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/objects/ship/ShipChassisData.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/ShipCollisionHardpoint.h"

class ShipCollisionData : public Object, public Logger {
public:
	enum CollisionVolumeType : int {
		INVALID = -1,
		RADIUS = 0,
		SPHERE = 1,
		MESH = 2,
		BOX = 3,
	};

protected:
	VectorMap<String, VectorMap<uint32, ShipCollisionHardpoint>> hardpointMap;
	VectorMap<uint32, uint32> slotWeights;
	Vector<uint32> targetableSlots;
	int hardpointSize;

	const AppearanceTemplate* appearance;
	Sphere boundingSphere;
	Sphere chassisSphere;
	AABB chassisBox;
	int volumeType;

public:
	ShipCollisionData(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData);

	void setCollisionData(SharedShipObjectTemplate* templateData);

	void setClientData(SharedShipObjectTemplate* shipTemplate);

	void setComponentData(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData);

	void setSlotWeights(SharedShipObjectTemplate* templateData, const ShipChassisData* chassisData);

	void addCollisionHardpoint(SharedShipObjectTemplate* shipTemplate, const String& componentName, const String& hardpointName, int slot, float radius);

	void addCollisionHardpoint(SharedShipObjectTemplate* shipTemplate, const String& componentName, const String& attachmentName, const String& hardpointName, int slot, float radius);

	int getBoundingVolumeType(const BaseBoundingVolume* volume) const {
		if (volume->isBoundingSphere()) { return SPHERE; }
		if (volume->isBoundingBox()) { return BOX; }
		return MESH;
	}

	bool isIdentityMatrix(const Matrix4& matrix) const {
		return matrix[0][0] == 1.f && matrix[1][1] == 1.f && matrix[2][2] == 1.f && matrix[3][3] == 1.f
			&& matrix[0][1] == 0.f && matrix[0][2] == 0.f && matrix[0][3] == 0.f
			&& matrix[1][0] == 0.f && matrix[1][2] == 0.f && matrix[1][3] == 0.f
			&& matrix[2][0] == 0.f && matrix[2][1] == 0.f && matrix[2][3] == 0.f
			&& matrix[3][0] == 0.f && matrix[3][1] == 0.f && matrix[3][2] == 0.f;
	}

	Sphere getChassisBoundingSphere(const BaseBoundingVolume* volume) const {
		const auto& sphere = volume->getBoundingSphere();
		float radius = sphere.getCenter().length() + sphere.getRadius();

		return Sphere(Vector3::ZERO, radius);
	}

	Sphere getHardpointBoundingSphere(const Sphere& sphere, const Vector3& position, const Matrix4& rotation) const {
		Vector3 spherePosition = position + (sphere.getCenter() * rotation);

		return Sphere(spherePosition, sphere.getRadius());
	}

	Sphere getHardpointBoundingSphere(const AABB& box, const Vector3& position, const Matrix4& rotation) const {
		const Vector3& boxCenter = box.center();
		float radius = (boxCenter - *box.getMinBound()).length();
		Vector3 transformedCenter = position + (boxCenter * rotation);

		return Sphere(transformedCenter, radius);
	}

	AABB getHardpointBoundingBox(const AABB& box, const Vector3& position, const Matrix4& rotation) const {
		auto maxBound = position + (*box.getMaxBound() * rotation);
		auto minBound = position + (*box.getMinBound() * rotation);

		float maxX = Math::max(minBound.getX(), maxBound.getX());
		float maxY = Math::max(minBound.getY(), maxBound.getY());
		float maxZ = Math::max(minBound.getZ(), maxBound.getZ());

		float minX = Math::min(minBound.getX(), maxBound.getX());
		float minY = Math::min(minBound.getY(), maxBound.getY());
		float minZ = Math::min(minBound.getZ(), maxBound.getZ());

		return AABB(Vector3(minX, minY, minZ), Vector3(maxX, maxY, maxZ));
	}

	String getAttachmentTemplatePath(const String& attachmentName, int slot) const {
		switch (slot) {
			case Components::CHASSIS: return "object/tangible/ship/attachment/wing/" + attachmentName + ".iff";
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
		return hardpointMap.get(slotName);
	}

	const VectorMap<uint32, ShipCollisionHardpoint>& getHardpoints(uint32 slot) const {
		return hardpointMap.get(Components::shipComponentSlotToString(slot));
	}

	const Vector<uint32>& getTargetableSlots() const {
		return targetableSlots;
	}

	int getSlotWeight(uint32 slot) const {
		return slotWeights.get(slot);
	}

	const AppearanceTemplate* getAppearanceTemplate() const {
		return appearance;
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

	int getHardpointSize() const {
		return hardpointSize;
	}

	String toDebugString(bool includeHardpoints = true) const {
		StringBuffer msg;

		msg
		<< "  apearanceName:  " << (appearance ? appearance->getFileName() : "") << endl
		<< "  boundingSphere: " << boundingSphere.getCenter().toString() << endl
		<< "  boundingRadius: " << boundingSphere.getRadius() << endl
		<< "  chassisSphere:  " << chassisSphere.getCenter().toString() << endl
		<< "  chassisRadius:  " << chassisSphere.getRadius() << endl
		<< "  chassisBox:     " << chassisBox.getMinBound()->toString() << " " << chassisBox.getMaxBound()->toString() << endl
		<< "  volumeType:     " << volumeType << endl
		<< "--------------------------------" << endl;

		if (includeHardpoints) {
			for (int i = 0; i < hardpointMap.size(); ++i) {
				auto harpdoints = hardpointMap.elementAt(i).getValue();

				for (int ii = 0; ii < harpdoints.size(); ++ii) {
					msg << harpdoints.elementAt(ii).getValue().toDebugString() << endl;
				}
			}
		}

		return msg.toString();
	}
};

#endif // SHIPCOLLISIONDATA_H_
