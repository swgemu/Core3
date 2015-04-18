/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions.caught in AreaTrackTask::run()");
		}
	}

	String getDirection(CreatureObject* tracker, CreatureObject* trackee) {
		String direction;
		float trackerX = tracker->getPositionX();
		float trackerY = tracker->getPositionY();
		float trackeeX = trackee->getPositionX();
		float trackeeY = trackee->getPositionY();

		// transform points so the origin is the tracker's position
		float transformedX = trackeeX - trackerX;
		float transformedY = trackeeY - trackerY;

		// normalize the transformed points which will give us points on the unit circle
		// in the direction of the trackee
		float length = sqrt(transformedX * transformedX + transformedY * transformedY);
		if(length > 0) {
			float pointOnUnitCircleX = transformedX / length;
			float pointOnUnitCircleY = transformedY / length;

			// inverse cos of the pointOnUnitCircleX will give the angle
			float directionAngleInDegrees = ((float)acos(pointOnUnitCircleX) * 180) / M_PI;

			// if the point is in the 3rd or 4th quadrant, 360 - directionAngleInDegrees will give the correct angle value
			// with the origin at (1,0) on the unit circle
			if(pointOnUnitCircleY < 0)
				directionAngleInDegrees = 360 - directionAngleInDegrees;

			if((directionAngleInDegrees >= 0 && directionAngleInDegrees <= 22.5) || (directionAngleInDegrees >= 337.5 && directionAngleInDegrees <= 360))
				direction = "east";
			else if(directionAngleInDegrees >= 22.5 && directionAngleInDegrees <= 67.5)
				direction = "northeast";
			else if(directionAngleInDegrees >= 67.5 && directionAngleInDegrees <= 112.5)
				direction = "north";
			else if(directionAngleInDegrees >= 112.5 && directionAngleInDegrees <= 157.5)
				direction = "northwest";
			else if(directionAngleInDegrees >= 157.5 && directionAngleInDegrees <= 202.5)
				direction = "west";
			else if(directionAngleInDegrees >= 202.5 && directionAngleInDegrees <= 247.5)
				direction = "southwest";
			else if(directionAngleInDegrees >= 247.5 && directionAngleInDegrees <= 292.5)
				direction = "south";
			else if(directionAngleInDegrees >= 292.5 && directionAngleInDegrees <= 337.5)
				direction = "southeast";
			else
				direction = "Error: Report this to Kyle Please";
		} else {
			direction = "north";  // this is for trackees that have the same position as the tracker's position
		}

		return direction;
	}

	String getDistance(CreatureObject* tracker, CreatureObject* trackee) {
		int distance = (int)tracker->getDistanceTo(trackee);

		StringBuffer strBuffer;
		strBuffer << " " << distance << "m";
		String result = strBuffer.toString();
		return result;
	}
};

#endif /* AREATRACKTASK_H_ */
