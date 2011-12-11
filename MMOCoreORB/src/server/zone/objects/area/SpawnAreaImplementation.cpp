/*
 * SpawnAreaImplementation.cpp
 *
 *  Created on: 11/12/2011
 *      Author: victor
 */

#include "SpawnArea.h"

Vector3 SpawnAreaImplementation::getRandomPosition(SceneObject* player) {
	double angle = System::random(359) * Math::DEG2RAD;

	Vector3 rOuter(radius * (float)Math::cos(angle), radius * (float)Math::sin(angle), 0);

	float lowIntersect = 1, highIntersect = 0;

	for (int i = 0; i < noSpawnAreas.size(); ++i) {
		SpawnArea* noSpawnArea = noSpawnAreas.get(i);
		Vector3 offset(noSpawnArea->getPositionX() - player->getPositionX(), noSpawnArea->getPositionY() - player->getPositionY(), 0);
		if (offset.squaredLength() >= noSpawnArea->getRadius2() + (radius2))
			continue;

		float t1 = 0, t2 = 0;
		float a = rOuter.dotProduct(rOuter);
		float b = 2 * (offset.dotProduct(rOuter));
		float c = offset.dotProduct(offset) - noSpawnArea->getRadius2();

		float discriminant = (b * b) - (4 * a * c);
		if (discriminant < 0)
			continue;

		if (discriminant == 0)
			t1 = (-b)/(2 * a);
		else {
			discriminant = Math::sqrt(discriminant);
			t1 = (-b + discriminant)/(2 * a);
			t2 = (-b - discriminant)/(2 * a);
		}

		if (t1 > 0 && t1 < lowIntersect)
			lowIntersect = t1;
		else if (t1 <= 1 && t1 > highIntersect)
			highIntersect = t1;

		if (t2 > 0 && t2 < lowIntersect)
			lowIntersect = t2;
		else if (t2 <= 1 && t2 > highIntersect)
			highIntersect = t2;
	}

	float difference = (highIntersect - lowIntersect) * 1000;
	if (difference < 0)
		difference = 0;

	float randomLength = (float)System::random(1000 - (int)difference);
	if (randomLength >= lowIntersect)
		randomLength = randomLength + difference;

	randomLength /= 1000;

	//info("randomLength = " + String::valueOf(randomLength), true);

	rOuter = randomLength * rOuter;

	return rOuter;
}
