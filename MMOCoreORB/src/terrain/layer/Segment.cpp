/*
 * Segment.cpp
*/

#include "Segment.h"

void Segment::createRoadwayHeights() {
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

		/*
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
		}*/

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

void Segment::readObject(engine::util::IffStream* iffStream) {
	iffStream->openChunk('SGMT');

	int count = iffStream->getDataSize() / 12;
	float lastZ = 0.f;

	for (int i = 0; i < count; i++) {
		Point3D* position = new Point3D();
		position->x = iffStream->getFloat();
		position->z = iffStream->getFloat();
		position->y = iffStream->getFloat();

		if (position->getZ() == lastZ)
			setFlatRoad(true);
		else
			setFlatRoad(false);

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

bool Segment::hasInitialCoordinate(float x, float y) {
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

void Segment::findNearestHeight(float& baseValue, Vector3 worldPosition) {
	int positionsSize = positions.size();

	if (positionsSize < 3 || flatRoad) {
		baseValue = positions.get(0)->getZ();
		return;
	}

	float positionX = worldPosition.getX();
	float positionY = worldPosition.getY();

	float newHeight = 0.f;
	float previousZ = 0.f;
	float distSquared = 0.f;
	int heightSegment = -1;

	// If the point to check for is closer to the front end of the road we start our iteration there, if not we will run it reverse
	if (positions.get(0)->squaredDistanceTo(positionX, positionY) < positions.get(positionsSize - 1)->squaredDistanceTo(positionX, positionY)) {
		for (int i = 1; i < positionsSize; ++i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float thisDistSq = point->squaredDistanceTo(positionX, positionY);

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Checking position " << i << " - X: " << point->getX() << " Y: " << point->getY() << " Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;
#endif
			if (i != 1 && thisDistSq > distSquared) {
				heightSegment = i - 1;

				break;
			}

			previousZ = newHeight;
			newHeight = point->getZ();
			distSquared = thisDistSq;

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Current best height: " << newHeight << " Previous Height: " << previousZ;
#endif
		}
	// Iterate the vector of segments in reverse since we are closer to the other end of the road
	} else {
		for (int i = positionsSize - 1; i > 0; --i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float thisDistSq = point->squaredDistanceTo(positionX, positionY);

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Checking position " << i << " - X: " << point->getX() << " Y: " << point->getY() << " Last Distance: " << distSquared << " thisDistSq: " << thisDistSq;
#endif
			if (i != positionsSize - 1 && thisDistSq > distSquared) {
				heightSegment = i + 1;

				break;
			}

			previousZ = newHeight;
			newHeight = point->getZ();
			distSquared = thisDistSq;

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Current best height: " << newHeight << " Previous Height: " << previousZ;
#endif
		}
	}

	if (heightSegment > 0 && heightSegment < (positionsSize - 1)) {
#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Adjust Z Height for heightSegment: " << heightSegment;
#endif

		// Get the points before and after the closest segment so we can find if the point is above or below our segment
		Point3D* segmentBefore = positions.get(heightSegment - 1);
		Point3D* ourSegment = positions.get(heightSegment);
		Point3D* segmentAfter = positions.get(heightSegment + 1);

		// Get the distance sq for both the point before and after, so we can find the closest next segment
		float distSq1 = segmentBefore->squaredDistanceTo(positionX, positionY);
		float distSq2 = segmentAfter->squaredDistanceTo(positionX, positionY);

		// The Segment before needs to always be the line segment ahead of the player on the roadway
		segmentBefore = (distSq1 < distSq2 ? segmentBefore : ourSegment);
		ourSegment = (distSq1 < distSq2 ? ourSegment : segmentAfter);

		Vector3 closestSeg(segmentBefore->getX(), segmentBefore->getY(), 0.f);

		float beforeSegZ = segmentBefore->getZ();
		float ourSegZ = ourSegment->getZ();

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "World Positon - X = " << positionX << " Y = " << positionY;
		Logger::console.info(true) << "segmentAfter - X: " << segmentAfter->getX() << " Z: " << segmentAfter->getZ() << " Y: " << segmentAfter->getY() << " Distance Sq: " << distSq2;

		Logger::console.info(true) << "segmentBefore - X: " << segmentBefore->getX() << " Z: " << beforeSegZ << " Y: " << segmentBefore->getY() << " Distance Sq: " << distSq1;
		Logger::console.info(true) << "ourSegment - X: " << ourSegment->getX() << " Z: " << ourSegZ << " Y: " << ourSegment->getY();
#endif

		Vector3 direction(ourSegment->getX() - closestSeg.getX(), ourSegment->getY() - closestSeg.getY(), 0.f);
		Vector3 difference = worldPosition - closestSeg;

		float dotProduct = difference.dotProduct(direction);
		float sqrDistance = direction.squaredLength();

		float intersection = Math::clamp(0.f, dotProduct / sqrDistance, 1.f);
		Vector3 position = (direction * intersection) + closestSeg;

		float posDistanceSq = closestSeg.squaredDistanceTo(position);

		float distanceVar = posDistanceSq / sqrDistance;
		float segmentDiff = beforeSegZ - ourSegZ;

		newHeight = beforeSegZ + (distanceVar * segmentDiff);

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "dotProduct: " << dotProduct << " sqrDistance: " << sqrDistance << " intersection: " << intersection << " posDistanceSq: " << posDistanceSq << " Position: " << position.toString();
		Logger::console.info(true) << " distanceVar = " << distanceVar << " Segment Diff: " << segmentDiff; 

		Logger::console.info(true) << "Height calculated: " << newHeight;
#endif
	}

	if (newHeight != 0.f) {
		baseValue = newHeight;
	}

#ifdef DEBUG_AFFECTOR_ROAD
	Logger::console.info(true) << "Height Returned: " << baseValue;
#endif
}
