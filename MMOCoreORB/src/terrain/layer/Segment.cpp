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

		/* This is not needed it was kept as a possible method to smooth certain areas out
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

void Segment::findNearestHeight(float& baseValue, Vector3 worldPosition, Vector3 roadCenter, float direction) {
#ifdef DEBUG_AFFECTOR_ROAD
	Logger::console.info(true) << "---------- FIND NEAREST HEIGHT ----------";
#endif

	int positionsSize = positions.size();

	if (positionsSize < 3 || flatRoad) {
		baseValue = positions.get(0)->getZ();
		return;
	}

	float positionX = worldPosition.getX();
	float positionY = worldPosition.getY();

	Point3D* firstPoint = positions.get(0);
	Point3D* lastPoint = positions.get(positionsSize - 1);

	if (firstPoint == nullptr || lastPoint == nullptr)
		return;

	float worldDistToFirstSq = firstPoint->squaredDistanceTo(positionX, positionY);
	float worldDistToLastSq = lastPoint->squaredDistanceTo(positionX, positionY);

	float deltaX = roadCenter.getX() - worldPosition.getX();
	float deltaY = roadCenter.getY() - worldPosition.getY();

	float rotatedY = deltaX * Math::sin(-direction) - deltaY * Math::cos(-direction);
	float rotatedYSq = rotatedY * rotatedY;

	float newHeight = 0.f;
	int heightSegment = -1;
	int halfSize = (positionsSize - 1) / 2;

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "World Distance Y: " << rotatedY << " y squared: " << rotatedYSq << " Segments half size: " << halfSize << " Angle in Rad: " << direction;
#endif

	// If the point to check for is closer to the front end of the road we start our iteration there, if not we will run it reverse
	if (worldDistToFirstSq <= worldDistToLastSq) {
		for (int i = 1; i < positionsSize; ++i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float thisDistSq = point->squaredDistanceTo(roadCenter.getX(), roadCenter.getY());

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Checking position " << i << " - X: " << point->getX() << " Y: " << point->getY() << " thisDistSq: " << thisDistSq;
#endif
			if (thisDistSq > rotatedYSq && i <= halfSize) {
				continue;
			}

			heightSegment = i;
			newHeight = point->getZ();

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Current best height: " << newHeight;
#endif
			break;
		}
	// Iterate the vector of segments in reverse since we are closer to the other end of the road
	} else {
		for (int i = positionsSize - 1; i > 0; --i) {
			Point3D* point = positions.get(i);

			if (point == nullptr)
				continue;

			float thisDistSq = point->squaredDistanceTo(roadCenter.getX(), roadCenter.getY());

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Segment Checking position " << i << " - X: " << point->getX() << " Y: " << point->getY() << " thisDistSq: " << thisDistSq;
#endif
			if (thisDistSq > rotatedYSq && i > halfSize) {
				continue;
			}

			heightSegment = i + 1;
			newHeight = point->getZ();

#ifdef DEBUG_AFFECTOR_ROAD
			Logger::console.info(true) << "Current best height: " << newHeight;
#endif
			break;
		}
	}

	if (heightSegment > 0 && heightSegment <= (positionsSize - 1)) {
#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "Adjust Z Height for heightSegment: " << heightSegment;
#endif

		// Get the points before and after the closest segment so we can find if the point is above or below our segment
		Point3D* segmentBefore = positions.get(heightSegment - 1);
		Point3D* segmentAfter = positions.get(heightSegment);

		Vector3 beforeSeg(segmentBefore->getX(), segmentBefore->getY(), segmentBefore->getZ());
		Vector3 afterSeg(segmentAfter->getX(), segmentAfter->getY(), segmentAfter->getZ());

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "===== SEGMENTS =====";
		Logger::console.info(true) << "segmentBefore - X: " << beforeSeg.getX() << " Z: " << beforeSeg.getZ() << " Y: " << beforeSeg.getY();

		Logger::console.info(true) << "segmentAfter - X: " << afterSeg.getX() << " Z: " << afterSeg.getZ() << " Y: " << afterSeg.getY();
		Logger::console.info(true) << "===== END SEGMENTS =====";
#endif

		float totalDistance = beforeSeg.distanceTo2d(afterSeg);
		float afterSegDistFromCenter = afterSeg.distanceTo2d(roadCenter);
		float positionDistance = totalDistance - fabs(afterSegDistFromCenter - fabs(rotatedY));

		// We need to check and see if the road center falls between our points to account for that in our calculation
		if (rotatedY > 0 && halfSize + 1 == heightSegment) {
			positionDistance = totalDistance - (afterSegDistFromCenter + fabs(rotatedY));
		}

		float distanceVar = Math::clamp(0.001f, positionDistance / totalDistance, 1.f);
		float segmentDiff = afterSeg.getZ() - beforeSeg.getZ();

		newHeight = beforeSeg.getZ() + (distanceVar * segmentDiff);

#ifdef DEBUG_AFFECTOR_ROAD
		Logger::console.info(true) << "===== POSITIONS =====";
		Logger::console.info(true) << "World Positon - X = " << positionX << " Y = " << positionY;
		Logger::console.info(true) << "afterSeg distance from center: " << afterSegDistFromCenter << " positionDistance = " << positionDistance << " totalDistance = " << totalDistance << " distanceVar: " << distanceVar;
		Logger::console.info(true) << "Height calculated: " << newHeight;
		Logger::console.info(true) << "===== END POSITIONS =====";
#endif
	}

	if (newHeight != 0.f) {
		baseValue = newHeight;
	}

#ifdef DEBUG_AFFECTOR_ROAD
	Logger::console.info(true) << "Height Returned: " << baseValue;
	Logger::console.info(true) << "---------- END FIND NEAREST HEIGHT ----------";
#endif
}
