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

	void createRoadwayHeights() {
		// If the road is short or the road is flat do not average
		if (flatRoad || positions.size() < 3)
			return;

		Vector<Point3D*> newPositions = positions;
		positions.removeAll();

		// Add the first point, we use that to find our roadway segment but it is not accounted for in segment positions
		positions.add(newPositions.get(0));

		int totalPositions = newPositions.size();
		float zAverage = 0.f;
		Vector3 lastNewLoc(0.f, 0.f, 0.f);

		Point3D* endPoint = newPositions.get(totalPositions - 1);

		// We are getting sets of 3 road Z coords and averaging them together to create a new z point
		for (int i = 1; i < totalPositions - 1; ++i) {
			// Position1
			Point3D* position1 = newPositions.get(i - 1);
			zAverage += position1->getZ();

			// Position2
			Point3D* position2 = newPositions.get(i);
			zAverage +=  position2->getZ();

			// Position3
			Point3D* position3 = newPositions.get(i + 1);
			zAverage += position3->getZ();

			zAverage /= 3.0f;

			// If the next avgerage Z is greater than 2m difference we are going to add in another averaged point between
			if (lastNewLoc.getZ() != 0 && fabs(lastNewLoc.getZ() - zAverage) > 1.0f) {
				Vector3 loc1(position2->getX(), position2->getY(), position2->getZ());

				// Get the distance between the last point and our next new one
				float distance = loc1.distanceTo(lastNewLoc);
				float betweenDist = distance / 2.f;

				float deltaX = loc1.getX() - lastNewLoc.getX();
				float deltaY = loc1.getY() - lastNewLoc.getY();

				// Set a point between the last and the next new point
				loc1.setX(lastNewLoc.getX() + (betweenDist * (deltaX / distance)));
				loc1.setY(lastNewLoc.getY() + (betweenDist * (deltaY / distance)));
				loc1.setZ((lastNewLoc.getZ() + zAverage) / 2.0f); // This is outputting nice z steps down

				// Add it to our new list of positions
				positions.add(new Point3D(loc1.getX(), loc1.getY(), loc1.getZ()));

				lastNewLoc.setX(loc1.getX());
				lastNewLoc.setZ(loc1.getZ());
				lastNewLoc.setY(loc1.getY());

#ifdef DEBUG_AFFECTOR_ROAD
				Logger::console.info(true) << "Segment ADDITIONAL segmentPoint - X: " << lastNewLoc.getX() << " Z: " << lastNewLoc.getZ() << " Y: " << lastNewLoc.getY();
#endif
			}

			lastNewLoc.setX(position2->getX());
			lastNewLoc.setZ(zAverage);
			lastNewLoc.setY(position2->getY());

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Adding averaged segmentPoint - X: " << lastNewLoc.getX() << " Z: " << lastNewLoc.getZ() << " Y: " << lastNewLoc.getY();
#endif
			positions.add(new Point3D(lastNewLoc.getX(), lastNewLoc.getY(), lastNewLoc.getZ()));

			zAverage = 0.f;
		}

		// Add in the other end of the road
		positions.add(endPoint);

		newPositions.removeAll();
	}

	void readObject(engine::util::IffStream* iffStream) {
		iffStream->openChunk('SGMT');

		int count = iffStream->getDataSize() / 12;
		float lastZ = 0.f;

		for (int i = 0; i < count; i++) {
			Point3D* position = new Point3D();
			position->x = iffStream->getFloat();
			position->z = iffStream->getFloat();
			position->y = iffStream->getFloat();

			if (position->getZ() == lastZ)
				flatRoad = true;
			else
				flatRoad = false;

			lastZ = position->getZ();

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment - Adding Point3D #" << i << " X: " << position->getX() << " Z: " << position->getZ() << " Y: " << position->getY();
#endif
			positions.add(position);
		}

		iffStream->closeChunk('SGMT');

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Segment - flatRoad: " << (flatRoad ? "TRUE" : "FALSE");
#endif

		createRoadwayHeights();
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
		int positionsSize = positions.size();

		if (positionsSize < 3 || flatRoad) {
			baseValue = positions.get(0)->getZ();
			return;
		}

		float newHeight = 0.f;
		float previousZ = 0.f;
		float distSquared = 0.f;

		// If the point to check for is closer to the front end of the road we start our iteration there, if not we will run it reverse
		if (positions.get(0)->squaredDistanceTo(positionX, positionY) < positions.get(positionsSize - 1)->squaredDistanceTo(positionX, positionY)) {
			for (int i = 1; i < positionsSize; ++i) {
				Point3D* point = positions.get(i);

				if (point == nullptr)
					continue;

				float thisDistSq = point->squaredDistanceTo(positionX, positionY);

	#ifdef DEBUG_AFFECTOR_ROAD
				Logger::console.info(true) << "Segment Checking position - Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;
	#endif
				if (i != 1 && distSquared != 0 && thisDistSq > distSquared) {
					continue;
				}

				previousZ = newHeight;
				newHeight = point->getZ();
				distSquared = thisDistSq;

	#ifdef DEBUG_AFFECTOR_ROAD
				Logger::console.info(true) << "Current best height: " << newHeight << " Previous Height: " << previousZ;
	#endif
			}
		// Run the vector of segments reverse
		} else {
			for (int i = positionsSize - 1; i > 0; --i) {
				Point3D* point = positions.get(i);

				if (point == nullptr)
					continue;

				float thisDistSq = point->squaredDistanceTo(positionX, positionY);

	#ifdef DEBUG_AFFECTOR_ROAD
				Logger::console.info(true) << "Segment Checking position - Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;
	#endif
				if (i != positionsSize - 1 && distSquared != 0 && thisDistSq > distSquared) {
					continue;
				}

				previousZ = newHeight;
				newHeight = point->getZ();
				distSquared = thisDistSq;

	#ifdef DEBUG_AFFECTOR_ROAD
				Logger::console.info(true) << "Current best height: " << newHeight << " Previous Height: " << previousZ;
	#endif
			}
		}

		if (newHeight != 0.f) {
			baseValue = newHeight;
		}

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Height Returned: " << baseValue;
#endif
	}
};

#endif /* SEGMENT_H_ */
