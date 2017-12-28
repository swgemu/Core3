/*
 * CollisionManager.h
 *
 *  Created on: 01/03/2011
 *      Author: victor
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_

#include <stddef.h>

#include "engine/engine.h"
#include "engine/util/Singleton.h"
#include "engine/util/u3d/Ray.h"
#include "engine/util/u3d/Vector3.h"
#include "server/zone/CloseObjectsVector.h"
#include "system/lang/ref/Reference.h"
#include "system/util/SortedVector.h"
#include "system/util/Vector.h"
#include "templates/appearance/AppearanceTemplate.h"

class AppearanceTemplate;
class FloorMesh;
class PathNode;
namespace engine {
namespace core {
template <class O> class ManagedReference;
}  // namespace core
namespace util {
namespace u3d {
class IntersectionResult;
class Matrix4;
class TriangleNode;
}  // namespace u3d
}  // namespace util
}  // namespace engine
namespace server {
namespace zone {
class CloseObjectsVector;
class QuadTreeEntry;
}  // namespace zone
}  // namespace server

namespace server {
namespace zone {
namespace objects {
namespace cell {
	class CellObject;
}
namespace scene {
	class SceneObject;
}

namespace creature {
	class CreatureObject;
}

namespace ship {
	class ShipObject;
}
}

	class Zone;
}
}

using namespace server::zone::objects::cell;
using namespace server::zone::objects::scene;
using namespace server::zone::objects::creature;
using namespace server::zone::objects::ship;
using namespace server::zone;

class CollisionManager : public Singleton<CollisionManager> {
public:
	static const AppearanceTemplate* getCollisionAppearance(SceneObject* scno, int collisionBlockFlags);
	static Ray convertToModelSpace(const Vector3& rayOrigin, const Vector3& rayEnd, SceneObject* model);
	static Vector3 convertToModelSpace(const Vector3& point, SceneObject* model);
	static TriangleNode* getTriangle(const Vector3& point, FloorMesh* floor);
	static Reference<Matrix4*> getTransformMatrix(SceneObject* model);
	/**
	 * @returns nearest available path node int the floor path graph with the lowest distance from triangle to final target
	 */
	static PathNode* findNearestPathNode(TriangleNode* triangle, FloorMesh* floor, const Vector3& finalTarget);

	static bool checkLineOfSightInBuilding(SceneObject* object1, SceneObject* object2, SceneObject* building);
	static bool checkLineOfSight(SceneObject* object1, SceneObject* object2);
	static bool checkLineOfSightWorldToCell(const Vector3& rayOrigin, const Vector3& rayEnd, float distance, CellObject* cell);
	static bool checkMovementCollision(CreatureObject* creature, float x, float z, float y, Zone* zone);
	static float getRayOriginPoint(CreatureObject* creature);

	static float getWorldFloorCollision(float x, float y, Zone* zone, bool testWater);
	static float getWorldFloorCollision(float x, float y, float z, Zone* zone, bool testWater);
	static void getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, CloseObjectsVector* closeObjectsVector = NULL);

	static void getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, const SortedVector<ManagedReference<QuadTreeEntry*> >& inRangeObjects);
	static void getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, const Vector<QuadTreeEntry* >& inRangeObjects);

	static Vector<float>* getCellFloorCollision(float x, float y, CellObject* cellObject);

	//static bool

	static bool checkShipCollision(ShipObject* ship, const Vector3& targetPosition, Vector3& collisionPoint);

	static bool checkSphereCollision(const Vector3& sphereOrigin, float radius, Zone* zone);

	static bool checkLineOfSightInParentCell(SceneObject* object, Vector3& endPoint);

};

#endif /* COLLISIONMANAGER_H_ */
