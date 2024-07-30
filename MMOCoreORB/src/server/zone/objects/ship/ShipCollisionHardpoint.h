#ifndef SHIPCOLLISIONHARDPOINT_H_
#define SHIPCOLLISIONHARDPOINT_H_

#include "engine/engine.h"

class ShipCollisionHardpoint : public Object {
protected:
	const AppearanceTemplate* appearance;
	String componentName;
	String hardpointName;

	Vector3 position;
	Sphere sphere;
	AABB box;

	Reference<Matrix4*> rotation;
	int volumeType;
	float radius;
	int slot;

public:
	ShipCollisionHardpoint() {
		appearance = nullptr;
		rotation = nullptr;

		volumeType = -1;
		radius = -1.f;
		slot = -1;
	}

	ShipCollisionHardpoint(const String& componentNameValue, const String& hardpointNameValue) : ShipCollisionHardpoint() {
		componentName = componentNameValue;
		hardpointName = hardpointNameValue;
	}

	void setAppearanceTemplate(const AppearanceTemplate* value) {
		appearance = value;
	}

	void setComponentName(const String& value) {
		componentName = value;
	}

	void setHardpointName(const String& value) {
		hardpointName = value;
	}

	void setPosition(const Vector3& value) {
		position = value;
	}

	void setSphere(const Sphere& value) {
		sphere = value;
	}

	void setBox(const AABB& value) {
		box = value;
	}

	void setRotation(Matrix4* value) {
		rotation = value;
	}

	void setVolumeType(int value) {
		volumeType = value;
	}

	void setRadius(float value) {
		radius = value;
	}

	void setSlot(int value) {
		slot = value;
	}

	const AppearanceTemplate* getAppearanceTemplate() const {
		return appearance;
	}

	const String& getComponentName() const {
		return componentName;
	}

	const String& getHardpointName() const {
		return hardpointName;
	}

	const Vector3& getPosition() const {
		return position;
	}

	const Sphere& getSphere() const {
		return sphere;
	}

	const AABB& getBox() const {
		return box;
	}

	const Matrix4* getRotation() const {
		return rotation.get();
	}

	int getVolumeType() const {
		return volumeType;
	}

	float getRadius() const {
		return radius;
	}

	int getSlot() const {
		return slot;
	}

	String toDebugString() const {
		StringBuffer msg;

		msg
		<< " appearanceName: " << (appearance ? appearance->getFileName() : "") << endl
		<< " componentName:  " << componentName << endl
		<< " hardpointName:  " << hardpointName << endl
		<< " position:       " << position.toString() << endl
		<< " rotation:       " << matrixToDebugString() << endl
		<< " sphere:         " << sphere.getCenter().toString() << ", " << sphere.getRadius() << endl
		<< " box:            " << box.getMinBound()->toString() << ", " << box.getMaxBound()->toString() << endl
		<< " volumeType:     " << volumeType << endl
		<< " slot:           " << Components::shipComponentSlotToString(slot) << endl
		<< "--------------------------------" << endl;

		return msg.toString();
	}

	String matrixToDebugString() const {
		const Matrix4& matrix = rotation ? *rotation : Matrix4();
		StringBuffer msg;

		msg << endl
		<< " " << matrix[0][0] << " " << matrix[0][1] << " " << matrix[0][2] << " " << matrix[0][3] << endl
		<< " " << matrix[1][0] << " " << matrix[1][1] << " " << matrix[1][2] << " " << matrix[1][3] << endl
		<< " " << matrix[2][0] << " " << matrix[2][1] << " " << matrix[2][2] << " " << matrix[2][3] << endl
		<< " " << matrix[3][0] << " " << matrix[3][1] << " " << matrix[3][2] << " " << matrix[3][3];

		return msg.toString();
	}
};

#endif // SHIPCOLLISIONHARDPOINT_H_
