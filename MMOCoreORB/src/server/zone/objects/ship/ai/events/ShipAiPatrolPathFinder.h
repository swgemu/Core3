#ifndef SHIPAIPATROLPATHFINDER_H_
#define SHIPAIPATROLPATHFINDER_H_

#include "engine/engine.h"
#include "server/zone/objects/ship/ai/SpacePatrolPoint.h"

class ShipAiPatrolPathFinder {
public:
	enum PathShape: uint32 {
		CIRCLE = 0,
		SPHERE = 1
	};

	static Vector3 getRandomPosition(const Vector3& position, float radiusMin = 0.f, float radiusMax = 1.f) {
		float x = Math::linearInterpolate(radiusMin, radiusMax, System::frandom(2.f) - 1.f);
		float y = Math::linearInterpolate(radiusMin, radiusMax, System::frandom(2.f) - 1.f);
		float z = Math::linearInterpolate(radiusMin, radiusMax, System::frandom(2.f) - 1.f);

		return position + Vector3(x,y,z);
	}

	static Vector<SpacePatrolPoint> generatePatrolCircle(const Sphere& sphere, const Matrix4& rotation, int totalPoints) {
		Vector<SpacePatrolPoint> patrolPoints;

		const Vector3& sphereCenter = sphere.getCenter();
		float sphereRadius = sphere.getRadius();

		for (int i = 0; i < totalPoints; ++i) {
			float theta = (2.f * M_PI * i) / (float)totalPoints;
			float cosTheta = cos(theta);
			float sinTheta = sin(theta);

			Vector3 patrolPoint = Vector3(sphereRadius * cosTheta,
										  sphereRadius * sinTheta,
										  0.f);

			patrolPoint = Vector3(patrolPoint.getX(), patrolPoint.getZ(), patrolPoint.getY()) * rotation;
			patrolPoint = Vector3(patrolPoint.getX(), patrolPoint.getZ(), patrolPoint.getY()) + sphereCenter;
			patrolPoints.add(SpacePatrolPoint(patrolPoint));
		}

		return patrolPoints;
	}

	static Vector<SpacePatrolPoint> generatePatrolSphere(const Sphere& sphere, const Matrix4& rotation, int totalPoints) {
		Vector<SpacePatrolPoint> patrolPoints;

		const Vector3& sphereCenter = sphere.getCenter();
		float sphereRadius = sphere.getRadius();

		int circles = sqrt(totalPoints);
		int points = totalPoints / circles;

		for (int i = 0; i < circles; ++i) {
			float phi = (M_PI * (i + 0.5)) / circles;
			float cosPhi = cos(phi);
			float sinPhi = sin(phi);

			for (int ii = 0; ii < points; ++ii) {
				float theta = (M_PI * ii * 2.f) / points;
				float cosTheta = cos(theta);
				float sinTheta = sin(theta);

				Vector3 patrolPoint = Vector3(sphereRadius * sinPhi * cosTheta,
											  sphereRadius * sinPhi * sinTheta,
											  sphereRadius * cosPhi);

				patrolPoint = Vector3(patrolPoint.getX(), patrolPoint.getZ(), patrolPoint.getY()) * rotation;
				patrolPoint = Vector3(patrolPoint.getX(), patrolPoint.getZ(), patrolPoint.getY()) + sphereCenter;
				patrolPoints.add(SpacePatrolPoint(patrolPoint));
			}
		}

		return patrolPoints;
	}
};

#endif // SHIPAIPATROLPATHFINDER_H_
