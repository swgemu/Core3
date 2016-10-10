/*
 * PathFinderManager.h
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#ifndef PATHFINDERMANAGER_H_
#define PATHFINDERMANAGER_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/objects/pathfinding/NavMeshRegion.h"
#include "pathfinding/recast/DetourCommon.h"
#include "pathfinding/recast/DetourNavMeshQuery.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace cell {
   	   class CellObject;
   }

   namespace creature {
    namespace ai {
    	class AiAgent;
    }
   }
  }
 }
}

using namespace server::zone::objects::creature;
using namespace server::zone::objects::cell;

class FloorMesh;
class dtQueryFilter;
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

protected:
	Vector<WorldCoordinates>* findPathFromWorldToWorld(const WorldCoordinates& pointA, Vector<WorldCoordinates>& endPoints, Zone* zone, bool allowPartial);
	Vector<WorldCoordinates>* findPathFromWorldToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);
	Vector<WorldCoordinates>* findPathFromWorldToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);

	Vector<WorldCoordinates>* findPathFromCellToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone);
	Vector<WorldCoordinates>* findPathFromCellToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	Vector<WorldCoordinates>* findPathFromCellToDifferentCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	void addTriangleNodeEdges(const Vector3& source, const Vector3& goal, Vector<Triangle*>* trianglePath, Vector<WorldCoordinates>* path, CellObject* cell);

private:
	dtQueryFilter m_filter;
	ThreadLocal<dtNavMeshQuery*> m_navQuery;
};



#endif /* PATHFINDERMANAGER_H_ */
