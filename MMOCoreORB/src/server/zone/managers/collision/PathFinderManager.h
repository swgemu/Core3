/*
 * PathFinderManager.h
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#ifndef PATHFINDERMANAGER_H_
#define PATHFINDERMANAGER_H_

#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/objects/pathfinding/NavMeshRegion.h"
#include "pathfinding/recast/DetourNavMeshQuery.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace cell {
   	   class CellObject;
   }
  }
 }
}

using namespace server::zone::objects::cell;

class FloorMesh;
class dtQueryFilter;

class NavCollision : public Object {
protected:
	float dist;
	Vector3 position;
	Reference<NavMeshRegion*> region;
public:

	int compareTo(const NavCollision* rhs) const {
		if (fabs(dist - rhs->dist) < 0.001f)
			return 0;
		else if (dist < rhs->dist)
			return 1;
		else
			return -1;
	}

	NavCollision(const Vector3& p, float len, Reference<NavMeshRegion*> r) : dist(len), position(p), region(r) { }
	float getDistance() const { return dist; }
	const Vector3& getPosition() const { return position; }
	const Reference<NavMeshRegion*>& getRegion() { return region; }
};

class PathFinderManager : public Singleton<PathFinderManager>, public Logger, public Object {
public:
	PathFinderManager();

	Vector<WorldCoordinates>* findPath(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone* zone);

	void filterPastPoints(Vector<WorldCoordinates>* path, SceneObject* object);

	static Vector3 transformToModelSpace(const Vector3& point, SceneObject* building);
	static FloorMesh* getFloorMesh(CellObject* cell);

	/**
	 * @returns -1 when points are in the same triangle
	 * @returns 0 when a successful path is found, the path is in nodes
	 * @returns 1 when no successful path is found
	 */
	int getFloorPath(const Vector3& pointA, const Vector3& pointB, FloorMesh* floor, Vector<Triangle*>*& nodes);
	Vector<WorldCoordinates>* findPathFromWorldToWorld(const WorldCoordinates& pointA, Vector<WorldCoordinates>& endPoints, Zone* zone, bool allowPartial);
	bool getSpawnPointInArea(const Sphere& area, Zone* zone, Vector3& point, bool checkRaycast = true);
protected:
	Vector<WorldCoordinates>* findPathFromWorldToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);
	Vector<WorldCoordinates>* findPathFromWorldToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);

	Vector<WorldCoordinates>* findPathFromCellToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);
	Vector<WorldCoordinates>* findPathFromCellToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	Vector<WorldCoordinates>* findPathFromCellToDifferentCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);
	bool getRecastPath(const Vector3& start, const Vector3& end, NavMeshRegion* region, Vector<WorldCoordinates>* path, float& len, bool allowPartial);
	void addTriangleNodeEdges(const Vector3& source, const Vector3& goal, Vector<Triangle*>* trianglePath, Vector<WorldCoordinates>* path, CellObject* cell);

	// The caller of this function is responsible for deleting the NavCollision objects.
	// Collisions should be sorted from closest to farthest.
	void getNavMeshCollisions(SortedVector<NavCollision*> *collisions, const SortedVector<ManagedReference<NavMeshRegion*>> *regions, const Vector3& start, const Vector3& end);
private:
	dtQueryFilter m_filter;
	dtQueryFilter m_spawnFilter;
	ThreadLocal<dtNavMeshQuery*> m_navQuery;
};

#endif /* PATHFINDERMANAGER_H_ */
