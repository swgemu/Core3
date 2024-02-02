/*
 * Sgmt.h
 *
 *  Created on: 31/01/2010
 *      Author: victor
 */

#ifndef SGMT_H_
#define SGMT_H_

#include "../TemplateVariable.h"

class Point3D {
public:
	float x, z, y;

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

class Segment : public TemplateVariable<'SGMT'> {
	Vector<Point3D*> positions;

public:
	~Segment() {
		for (int i = 0; i < positions.size(); ++i)
			delete positions.get(i);
	}

	void averageRoadHeights() {
		if (positions.size() < 3)
			return;

		Vector<Point3D*> newPositions = positions;
		positions.removeAll();

		// Add the first point, we use that to find our roadway segment
		positions.add(newPositions.get(0));

		int totalPositions = newPositions.size();

		for (int i = 1; i < totalPositions - 1; ++i) {
			Point3D* position1 = newPositions.get(i - 1);

			float currentZ = position1->getZ();

			Point3D* position2 = newPositions.get(i);
			currentZ += position2->getZ();

			Point3D* position3 = newPositions.get(i + 1);
			currentZ += position3->getZ();

			position1->z = (currentZ / 3.00f);
			positions.add(position1);
		}
	}

	void readObject(engine::util::IffStream* iffStream) {
		iffStream->openChunk('SGMT');

		int count = iffStream->getDataSize() / 12;

		for (int i = 0; i < count; i++) {
			Point3D* position = new Point3D();
			position->x = iffStream->getFloat();
			position->z = iffStream->getFloat();
			position->y = iffStream->getFloat();

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment - Adding Point3D #" << i << " X: " << position->getX() << " Z: " << position->getZ() << " Y: " << position->getY();
#endif
			positions.add(position);
		}

		iffStream->closeChunk('SGMT');

		averageRoadHeights();
	}

	bool hasInitialCoordinate(float x, float y) {
		int positionsSize = positions.size();

		if (positionsSize == 0) {
#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment::hasInitialCoordinate - returning false due to positionsSize.";
#endif
			return false;
		}

		Point3D* startPoint = positions.get(0);

		bool result = (startPoint->getX() == x && startPoint->getY() == y);

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Segment has initial coordinate: " << (result ? "TRUE" : "FALSE");
		Logger::console.info(true) << "Initial Coord X: " << startPoint->getX() << " Y: " <<startPoint->getY();
#endif
		return result;
	}

	void findNearestHeight(float& baseValue, float positionX, float positionY) {
		float newHeight = 0.f;
		float distSquared = 0.f;
		float previousZ = 0.f;

		for (int i = 1; i < positions.size(); ++i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float deltaX = point->getX() - positionX;
			float deltaY = point->getY() - positionY;

			float thisDistSq = (deltaX * deltaX + deltaY * deltaY);

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Checking position - Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;
#endif
			if (i != 0 && thisDistSq > distSquared)
				continue;

			previousZ = newHeight;
			newHeight = point->getZ();
			distSquared = thisDistSq;

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Current best height: " << newHeight << " Previous Height: " << previousZ;
#endif
		}

		if (newHeight != 0.f) {
			if (previousZ != 0)
				newHeight = (newHeight + previousZ) / 2.0f;

			baseValue = newHeight;
		}

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Height Returned: " << baseValue;
#endif
	}
};

#endif /* SGMT_H_ */
