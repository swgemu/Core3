/*
 * Segment.h
 *
 *  Created on: 31/01/2010
 *  Author: victor
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_

#include "../TemplateVariable.h"

class Point3D {
public:
	Point3D() {
	}

	Point3D(float newX, float newY, float newZ) {
		x = newX;
		y = newY;
		z = newZ;
	}

	float x, z, y;

	float squaredDistanceTo(float locX, float locZ, float locY) {
		float deltaX = x - locX;
		float deltaZ = z - locZ;
		float deltaY = y - locY;

		return (deltaX * deltaX + deltaZ * deltaZ + deltaY * deltaY);
	}

	float squaredDistanceTo(float locX, float locY) {
		float deltaX = x - locX;
		float deltaY = y - locY;

		return (deltaX * deltaX + deltaY * deltaY);
	}

	float getX() {
		return x;
	}

	float getZ() {
		return z;
	}

	float getY() {
		return y;
	}
};

// #define DEBUG_AFFECTOR_ROAD

class Segment : public TemplateVariable<'SGMT'> {
	Vector<Point3D*> positions;
	bool flatRoad;

public:
	Segment() {
		flatRoad = false;
	}

	~Segment() {
		for (int i = 0; i < positions.size(); ++i)
			delete positions.get(i);

		positions.removeAll();
	}

	void createRoadwayHeights();
	void readObject(engine::util::IffStream* iffStream);
	bool hasInitialCoordinate(float x, float y);
	void findNearestHeight(float& baseValue, Vector3 worldPosition, Vector3 roadCenter, float direction);

	void setFlatRoad(bool val) {
		flatRoad = val;
	}

	bool isFlatRoad() {
		return flatRoad;
	}
};

#endif /* SEGMENT_H_ */
