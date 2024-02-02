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

	void readObject(engine::util::IffStream* iffStream) {
		iffStream->openChunk('SGMT');

		int count = iffStream->getDataSize() / 12;

		for (int i = 0; i < count; i++) {
			Point3D* position = new Point3D();
			position->x = iffStream->getFloat();
			position->z = iffStream->getFloat();
			position->y = iffStream->getFloat();

			Logger::console.info(true) << "Segment - Adding Point3D #" << i << " X: " << position->getX() << " Z: " << position->getZ() << " Y: " << position->getY();

			positions.add(position);
		}

		iffStream->closeChunk('SGMT');
	}

	bool hasInitialCoordinate(float x, float y) {
		int positionsSize = positions.size();

		if (positionsSize == 0) {
			Logger::console.info(true) << "Segment::hasInitialCoordinate - returning false due to positionsSize.";

			return false;
		}

		Point3D* startPoint = positions.get(0);

		bool result = (startPoint->getX() == x && startPoint->getY() == y);

		Logger::console.info(true) << "Segment has initial coordinate: " << (result ? "TRUE" : "FALSE");
		Logger::console.info(true) << "Initial Coord X: " << startPoint->getX() << " Y: " <<startPoint->getY();

		return result;
	}

	void findNearestHeight(float& baseValue, float positionX, float positionY) {
		float newHeight = 0.f;
		float distSquared = 0.f;

		for (int i = 0; i < positions.size(); ++i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float deltaX = point->getX() - positionX;
			float deltaY = point->getY() - positionY;

			float thisDistSq = (deltaX * deltaX + deltaY * deltaY);

			Logger::console.info(true) << "Segment Checking position - Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;

			if (i != 0 && thisDistSq > distSquared)
				continue;

			newHeight = point->getZ();
			distSquared = thisDistSq;

			Logger::console.info(true) << "Current best height: " << newHeight;
		}

		if (newHeight != 0.f)
			baseValue = newHeight;
	}
};

#endif /* SGMT_H_ */
