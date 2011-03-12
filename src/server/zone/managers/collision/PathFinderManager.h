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

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
    class AiAgent;
   }
  }
 }
}

using namespace server::zone::objects::creature;

class FloorMesh;

class PathFinderManager : public Singleton<PathFinderManager>, public Logger {

public:
	PathFinderManager() : Logger("PathFinderManager") {

	}

	Vector<WorldCoordinates>* findPath(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	static Vector3 transformToModelSpace(const Vector3& point, SceneObject* building);


protected:
	Vector<WorldCoordinates>* findPathFromWorldToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB);
	Vector<WorldCoordinates>* findPathFromWorldToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	Vector<WorldCoordinates>* findPathFromCellToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB);
	Vector<WorldCoordinates>* findPathFromCellToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	Vector<WorldCoordinates>* findPathFromCellToDifferentCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB);

	/**
	 * @returns -1 when points are in the same triangle
	 * @returns 0 when a successful path is found, the path is in nodes
	 * @returns 1 when no successful path is found
	 */
	int getFloorPath(const Vector3& pointA, const Vector3& pointB, FloorMesh* floor, Vector<Triangle*>*& nodes);

	void addTriangleNodeEdges(const Vector3& source, const Vector3& goal, Vector<Triangle*>* trianglePath, Vector<WorldCoordinates>* path, SceneObject* cell);
};



#endif /* PATHFINDERMANAGER_H_ */
