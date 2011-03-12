/*
 * CollisionManager.h
 *
 *  Created on: 01/03/2011
 *      Author: victor
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/WorldCoordinates.h"

class PathNode;
class FloorMesh;

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;
}

namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;

class CollisionManager : public Singleton<CollisionManager> {


public:
	static TriangleNode* getTriangle(const Vector3& point, FloorMesh* floor);


	/**
	 * @returns nearest available path node int the floor path graph with the lowest distance from triangle to final target
	 */
	static PathNode* findNearestPathNode(TriangleNode* triangle, FloorMesh* floor, const Vector3& finalTarget);

	static bool checkLineOfSightInBuilding(SceneObject* object1, SceneObject* object2, SceneObject* building);
	static bool checkLineOfSight(SceneObject* object1, SceneObject* object2);
	static float getCollisionPoint(CreatureObject* creature);

};

#endif /* COLLISIONMANAGER_H_ */
