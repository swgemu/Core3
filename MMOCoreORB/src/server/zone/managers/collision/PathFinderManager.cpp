/*
 * PathFinderManager.cpp
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#include "PathFinderManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"
#include "CollisionManager.h"
#include "engine/util/u3d/Funnel.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "engine/util/u3d/Segment.h"

Vector<WorldCoordinates>* PathFinderManager::findPath(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	if (isnan(pointA.getX()) || isnan(pointA.getY()) || isnan(pointA.getZ()))
		return NULL;

	if (isnan(pointB.getX()) || isnan(pointB.getY()) || isnan(pointB.getZ()))
		return NULL;

	SceneObject* cellA = pointA.getCell();
	SceneObject* cellB = pointB.getCell();

	if (cellA == NULL && cellB == NULL) { // world -> world
		return findPathFromWorldToWorld(pointA, pointB);
	} else if (cellA != NULL && cellB == NULL) { // cell -> world
		return findPathFromCellToWorld(pointA, pointB);
	} else if (cellA == NULL && cellB != NULL) { // world -> cell
		return findPathFromWorldToCell(pointA, pointB);
	} else if (cellA != NULL && cellB != NULL) { // cell -> cell
		return findPathFromCellToCell(pointA, pointB);
	}

	return NULL;
}

void PathFinderManager::filterPastPoints(Vector<WorldCoordinates>* path, SceneObject* object) {
    Vector3 thisWorldPosition = object->getWorldPosition();
    Vector3 thiswP = thisWorldPosition;
    thiswP.setZ(0);

    if (path->size() > 2 && path->get(0) == path->get(1))
        path->remove(1);

    for (int i = 2; i < path->size(); ++i) {
        WorldCoordinates coord1 = path->get(i);
        WorldCoordinates coord2 = path->get(i - 1);

        Vector3 end = coord1.getWorldPosition();
        Vector3 start = coord2.getWorldPosition();

        if (coord1.getCell() != coord2.getCell()) {
            Vector3 coord1WorldPosition = end;
            Vector3 coord2WorldPosition = start;

            if (coord1WorldPosition == coord2WorldPosition && thisWorldPosition == coord1WorldPosition) {
                path->remove(i - 1);
                break;
            }

            continue;
        }

        end.setZ(0);
        start.setZ(0);
        Segment sgm(start, end);

        Vector3 closestP = sgm.getClosestPointTo(thiswP);

        if (closestP.distanceTo(thiswP) <= FLT_EPSILON) {
            for (int j = i - 1; j > 0; --j) {
                path->remove(j);
            }

            break;
        }
    }
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromWorldToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	//we dont have path nodes in the world yet returning straight line

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(2, 1);
	path->add(pointA);
	path->add(pointB);

	return path;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromWorldToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	CellObject* targetCell = cast<CellObject*>( pointB.getCell());
	ManagedReference<BuildingObject*> building = dynamic_cast<BuildingObject*>(targetCell->getParent().get().get());

	if (building == NULL) {
		error("building == NULL in PathFinderManager::findPathFromWorldToCell");
		return NULL;
	}

	SharedObjectTemplate* templateObject = building->getObjectTemplate();

	if (templateObject == NULL)
		return NULL;

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	//find nearest entrance
	FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0); // get outside layout
	PathGraph* exteriorPathGraph = exteriorFloorMesh->getPathGraph();

	FloorMesh* targetFloorMesh = portalLayout->getFloorMesh(targetCell->getCellNumber());
	PathGraph* targetPathGraph = targetFloorMesh->getPathGraph();

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA);

	Vector3 transformedPosition = transformToModelSpace(pointA.getPoint(), building);

	PathNode* nearestEntranceNode = exteriorPathGraph->findNearestNode(transformedPosition);

	if (nearestEntranceNode == NULL) {
		error("NULL entrance node for building " + templateObject->getFullTemplateString());
		delete path;
		return NULL;
	}
	//PathNode* nearestTargetNode = targetPathGraph->findNearestNode(pointB.getPoint());
	TriangleNode* nearestTargetNodeTriangle = CollisionManager::getTriangle(pointB.getPoint(), targetFloorMesh);

	if (nearestTargetNodeTriangle == NULL) {
		delete path;
		return NULL;
	}

	PathNode* nearestTargetNode = CollisionManager::findNearestPathNode(nearestTargetNodeTriangle, targetFloorMesh, pointB.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (nearestTargetNode == NULL) {
		delete path;
		return NULL;
	}

	/*if (nearestEntranceNode == nearestTargetNode)
		info("nearestEntranceNode == nearestTargetNode", true);*/

	//find graph from outside to appropriate cell
	Vector<PathNode*>* pathToCell = portalLayout->getPath(nearestEntranceNode, nearestTargetNode);

	if (pathToCell == NULL) {
		error("pathToCell = portalLayout->getPath(nearestEntranceNode, nearestTargetNode); == NULL");
		delete path;
		return NULL;
	}

	for (int i = 0; i < pathToCell->size(); ++i) {
		PathNode* pathNode = pathToCell->get(i);
		PathGraph* pathGraph = pathNode->getPathGraph();

		FloorMesh* floorMesh = pathGraph->getFloorMesh();

		int cellID = floorMesh->getCellID();

		//info("cellID:" + String::valueOf(cellID), true);

		if (cellID == 0) { // we are still outside
			WorldCoordinates coord(pathNode->getPosition(), targetCell);

			path->add(WorldCoordinates(coord.getWorldPosition(), NULL));
		} else { // we are inside the building
			SceneObject* pathCell = building->getCell(cellID);

			path->add(WorldCoordinates(pathNode->getPosition(), pathCell));

			if (i == pathToCell->size() - 1)
				if (pathCell != targetCell) {
					error("final cell not target cell");
				}
		}
	}

	delete pathToCell;
	pathToCell = NULL;

	// path from cell path node to destination point
	Vector<Triangle*>* trianglePath = NULL;

	int res = getFloorPath(path->get(path->size() - 1).getPoint(), pointB.getPoint(), targetFloorMesh, trianglePath);

	if (res != -1 && trianglePath != NULL)
		addTriangleNodeEdges(path->get(path->size() - 1).getPoint(), pointB.getPoint(), trianglePath, path, targetCell);

	if (trianglePath != NULL)
		delete trianglePath;

	path->add(pointB);

	return path;
}

FloorMesh* PathFinderManager::getFloorMesh(CellObject* cell) {
    ManagedReference<BuildingObject*> building1 = (cell->getParent().castTo<BuildingObject*>());

    SharedObjectTemplate* templateObject = building1->getObjectTemplate();

    if (templateObject == NULL) {
    	return NULL;
    }

    PortalLayout* portalLayout = templateObject->getPortalLayout();

    if (portalLayout == NULL) {
    	return NULL;
    }

    FloorMesh* floorMesh1 = portalLayout->getFloorMesh(cell->getCellNumber());

    return floorMesh1;
}

int PathFinderManager::getFloorPath(const Vector3& pointA, const Vector3& pointB, FloorMesh* floor, Vector<Triangle*>*& nodes) {
	/*Vector3 objectPos = pointA;
	Vector3 targetPos = pointB;

	StringBuffer objPos;
	objPos << "returning path point x:" << objectPos.getX() << " z:" << objectPos.getZ() << " y:" << objectPos.getY();
	info(objPos.toString(), true);

	//switching y<->z for client coords
	objectPos.set(objectPos.getX(), objectPos.getY(), objectPos.getZ());
	targetPos.set(targetPos.getX(), targetPos.getY(), targetPos.getZ());*/

	//TriangleNode* objectFloor = floor->findNearestTriangle(objectPos);

	TriangleNode* objectFloor = CollisionManager::getTriangle(pointA, floor);

	/*Vector3 objectFloorVector = objectFloor->getBarycenter();
	StringBuffer objectFoorBar;
	objectFoorBar << "nearest object floor point x:" << objectFloorVector.getX() << " z:" << objectFloorVector.getY() << " y:" << objectFloorVector.getZ();
	info(objectFoorBar.toString(), true);*/

	//TriangleNode* targetFloor = floor->findNearestTriangle(targetPos);
	TriangleNode* targetFloor = CollisionManager::getTriangle(pointB, floor);

	/*Vector3 targetFloorVector = targetFloor->getBarycenter();
	StringBuffer targetFoorBar;
	targetFoorBar << "nearest target floor point x:" << targetFloorVector.getX() << " z:" << targetFloorVector.getY() << " y:" << targetFloorVector.getZ();
	info(targetFoorBar.toString(), true);*/

	nodes = NULL;

	if (objectFloor == targetFloor) { // we are on the same triangle, returning pointB
		return -1;
	} else if (objectFloor == NULL || targetFloor == NULL)
		return 1;

	nodes = TriangulationAStarAlgorithm::search(pointA, pointB, objectFloor, targetFloor);

	if (nodes == NULL)
		return 1;

	return 0;
}

Vector3 PathFinderManager::transformToModelSpace(const Vector3& point, SceneObject* building) {
	// we need to move world position into model space
	Vector3 switched(point.getX(), point.getZ(), point.getY());
	Matrix4 translationMatrix;
	translationMatrix.setTranslation(-building->getPositionX(), -building->getPositionZ(), -building->getPositionY());

	float rad = -building->getDirection()->getRadians();
	float cosRad = cos(rad);
	float sinRad = sin(rad);

	Matrix3 rot;
	rot[0][0] = cosRad;
	rot[0][2] = -sinRad;
	rot[1][1] = 1;
	rot[2][0] = sinRad;
	rot[2][2] = cosRad;

	Matrix4 rotateMatrix;
	rotateMatrix.setRotationMatrix(rot);

	Matrix4 modelMatrix;
	modelMatrix = translationMatrix * rotateMatrix;

	Vector3 transformedPosition = switched * modelMatrix;

	transformedPosition.set(transformedPosition.getX(), transformedPosition.getY(), transformedPosition.getZ());

	return transformedPosition;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromCellToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA);

	CellObject* ourCell = cast<CellObject*>( pointA.getCell());
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>( ourCell->getParent().get().get());
	int ourCellID = ourCell->getCellNumber();
	SharedObjectTemplate* templateObject = ourCell->getParent().get()->getObjectTemplate();

	if (templateObject == NULL) {
		delete path;
		return NULL;
	}

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL) {
		delete path;
		return NULL;
	}

	FloorMesh* sourceFloorMesh = portalLayout->getFloorMesh(ourCellID);
	PathGraph* sourcePathGraph = sourceFloorMesh->getPathGraph();

	FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0);
	PathGraph* exteriorPathGraph = exteriorFloorMesh->getPathGraph();

	// we need to move world position into model space
	Vector3 transformedPosition = transformToModelSpace(pointB.getPoint(), building);

	//find exit node in our cell
	//PathNode* exitNode = sourcePathGraph->findNearestNode(pointA.getPoint());
	TriangleNode* nearestTargetNodeTriangle = CollisionManager::getTriangle(pointA.getPoint(), sourceFloorMesh);

	if (nearestTargetNodeTriangle == NULL) {
		delete path;
		return NULL;
	}

	PathNode* exitNode = CollisionManager::findNearestPathNode(nearestTargetNodeTriangle, sourceFloorMesh, transformedPosition);//targetPathGraph->findNearestNode(pointB.getPoint());

	if (exitNode == NULL) {
		delete path;
		return NULL;
	}

	//find exterior node
	PathNode* exteriorNode = exteriorPathGraph->findNearestGlobalNode(transformedPosition);

	if (exteriorNode == NULL) {
		delete path;
		return NULL;
	}

	//find path to the exit
	Vector<PathNode*>* exitPath = portalLayout->getPath(exitNode, exteriorNode);

	if (exitPath == NULL) {
		error("exitPath == NULL");
		delete path;
		return NULL;
	}

	//find triangle path to exitNode
	Vector<Triangle*>* trianglePath = NULL;

	int res = getFloorPath(pointA.getPoint(), exitNode->getPosition(), sourceFloorMesh, trianglePath);

	if (res != -1 && trianglePath != NULL)
		addTriangleNodeEdges(pointA.getPoint(), exitNode->getPosition(), trianglePath, path, ourCell);

	if (trianglePath != NULL)
		delete trianglePath;

	path->add(WorldCoordinates(exitNode->getPosition(), ourCell));

	//populate cell traversing
	for (int i = 0; i < exitPath->size(); ++i) {
		PathNode* pathNode = exitPath->get(i);
		PathGraph* pathGraph = pathNode->getPathGraph();

		FloorMesh* floorMesh = pathGraph->getFloorMesh();

		int cellID = floorMesh->getCellID();

		if (cellID == 0) { // we are outside
			WorldCoordinates coord(pathNode->getPosition(), ourCell);

			path->add(WorldCoordinates(coord.getWorldPosition(), NULL));
		} else { // we are inside the building
			SceneObject* pathCell = building->getCell(cellID);

			path->add(WorldCoordinates(pathNode->getPosition(), pathCell));
		}
	}

	delete exitPath;
	exitPath = NULL;

	path->add(pointB);

	return path;
}

void PathFinderManager::addTriangleNodeEdges(const Vector3& source, const Vector3& goal, Vector<Triangle*>* trianglePath, Vector<WorldCoordinates>* path, SceneObject* cell) {
	Vector3 startPoint = Vector3(source.getX(), source.getZ(), source.getY());
	Vector3 goalPoint = Vector3(goal.getX(), goal.getZ(), goal.getY());

	Vector<Vector3>* funnelPath = Funnel::funnel(startPoint, goalPoint, trianglePath);

	/*info("found funnel size: " + String::valueOf(funnelPath->size()));
	info("triangle number: " + String::valueOf(trianglePath->size()));

	StringBuffer objectFoorBarSource;
	objectFoorBarSource << "funnel source point x:" << source.getX() << " z:" << source.getZ() << " y:" << source.getY();
	info(objectFoorBarSource.toString(), true);*/

	for (int i = 1; i < funnelPath->size() - 1; ++i) { //without the start and the goal
		/*Vector3 worldPosition = path->get(i);

		StringBuffer objectFoorBar;
		objectFoorBar << "funnel node point x:" << worldPosition.getX() << " z:" << worldPosition.getZ() << " y:" << worldPosition.getY();
		info(objectFoorBar.toString(), true);*/

		Vector3 pathPoint = funnelPath->get(i);

		//switch y<->x
		pathPoint.set(pathPoint.getX(), pathPoint.getY(), pathPoint.getZ());

		/*StringBuffer objectFoorBar;
		objectFoorBar << "funnel node point x:" << pathPoint.getX() << " z:" << pathPoint.getZ() << " y:" << pathPoint.getY();
		info(objectFoorBar.toString(), true);*/

		path->add(WorldCoordinates(pathPoint, cell));
	}

	/*StringBuffer objectFoorBarGoal;
	objectFoorBarGoal << "funnel goal point x:" << goal.getX() << " z:" << goal.getZ() << " y:" << goal.getY();
	info(objectFoorBarGoal.toString(), true);*/

	delete funnelPath;



	/*for (int i = 0; i < trianglePath->size(); ++i) {
		TriangleNode* node = trianglePath->get(i);

		//if (!node->isEdge()) // adding only edge nodes
			//continue;

		Vector3 pathBary = node->getBarycenter();

		//switch y<->x
		pathBary.set(pathBary.getX(), pathBary.getY(), pathBary.getZ());

		path->add(WorldCoordinates(pathBary, cell));
	}*/
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromCellToDifferentCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	//info ("findPathFromCellToDifferentCell", true);

	CellObject* ourCell = cast<CellObject*>( pointA.getCell());
	CellObject* targetCell = cast<CellObject*>( pointB.getCell());

	int ourCellID = ourCell->getCellNumber();
	int targetCellID = targetCell->getCellNumber();

	ManagedReference<BuildingObject*> building1 = cast<BuildingObject*>( ourCell->getParent().get().get());
	ManagedReference<BuildingObject*> building2 = cast<BuildingObject*>( targetCell->getParent().get().get());

	if (building1 != building2) // TODO: implement path finding between 2 buildings
		return NULL;

	SharedObjectTemplate* templateObject = building1->getObjectTemplate();

	if (templateObject == NULL)
		return NULL;

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	FloorMesh* floorMesh1 = portalLayout->getFloorMesh(ourCellID);
	FloorMesh* floorMesh2 = portalLayout->getFloorMesh(targetCellID);

	if (floorMesh2->getCellID() != targetCellID)
		error("floorMes2 cellID != targetCellID");

	//info("targetCellID:" + String::valueOf(targetCellID), true);

	PathGraph* pathGraph1 = floorMesh1->getPathGraph();
	PathGraph* pathGraph2 = floorMesh2->getPathGraph();

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA); // adding source

	//PathNode* source = pathGraph1->findNearestNode(pointA.getPoint());
	TriangleNode* nearestSourceNodeTriangle = CollisionManager::getTriangle(pointA.getPoint(), floorMesh1);

	if (nearestSourceNodeTriangle == NULL) {
		delete path;
		return NULL;
	}

	PathNode* source = CollisionManager::findNearestPathNode(nearestSourceNodeTriangle, floorMesh1, pointB.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (source == NULL) {
		delete path;
		return NULL;
	}

	//PathNode* target = pathGraph2->findNearestNode(pointB.getPoint());
	TriangleNode* nearestTargetNodeTriangle = CollisionManager::getTriangle(pointB.getPoint(), floorMesh2);

	if (nearestTargetNodeTriangle == NULL) {
		delete path;
		return NULL;
	}

	PathNode* target = CollisionManager::findNearestPathNode(nearestTargetNodeTriangle, floorMesh2, pointB.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (target == NULL) {
		delete path;
		return NULL;
	}

	Vector<PathNode*>* nodes = portalLayout->getPath(source, target);

	if (nodes == NULL) {
		error("NODES NULL");

		delete path;
		return NULL;
	}

	// path from our position to path node
	Vector<Triangle*>* trianglePath = NULL;

	int res = getFloorPath(pointA.getPoint(), nodes->get(1)->getPosition(), floorMesh1, trianglePath);

	if (res != -1 && trianglePath != NULL)
		addTriangleNodeEdges(pointA.getPoint(), nodes->get(1)->getPosition(), trianglePath, path, ourCell);

	if (trianglePath != NULL) {
		delete trianglePath;
		trianglePath = NULL;
	}

	path->add(WorldCoordinates(source->getPosition(), ourCell));

	//traversing cells
	for (int i = 1; i < nodes->size(); ++i) {
		PathNode* pathNode = nodes->get(i);
		PathGraph* pathGraph = pathNode->getPathGraph();

		FloorMesh* floorMesh = pathGraph->getFloorMesh();

		int cellID = floorMesh->getCellID();

		if (cellID == 0) {
			//info("cellID == 0", true);
			WorldCoordinates coord(pathNode->getPosition(), ourCell);

			path->add(WorldCoordinates(coord.getWorldPosition(), NULL));
		} else {
			SceneObject* pathCell = building1->getCell(cellID);

			WorldCoordinates coord(pathNode->getPosition(), pathCell);

			path->add(coord);

			//info("cellID:" + String::valueOf(cellID), true);

			if (i == nodes->size() - 1) {
				if (pathNode != target) {
					StringBuffer msg;
					msg << "pathNode != target pathNode: " << pathNode->getID() << " target:" << target->getID();
					error(msg.toString());
				}

				if (pathCell != targetCell) {
					error("final cell not target cell");
				}
			}
		}
	}

	delete nodes;
	nodes = NULL;

	// path from cell entrance to destination point
	trianglePath = NULL;

	res = getFloorPath(path->get(path->size() - 1).getPoint(), pointB.getPoint(), floorMesh2, trianglePath);

	if (res != -1 && trianglePath != NULL)
		addTriangleNodeEdges(path->get(path->size() - 1).getPoint(), pointB.getPoint(), trianglePath, path, targetCell);

	if (trianglePath != NULL)
		delete trianglePath;

	path->add(pointB);

	return path;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromCellToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	CellObject* ourCell = cast<CellObject*>( pointA.getCell());
	CellObject* targetCell = cast<CellObject*>( pointB.getCell());

	if (ourCell != targetCell)
		return findPathFromCellToDifferentCell(pointA, pointB);

	int ourCellID = ourCell->getCellNumber();

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>( ourCell->getParent().get().get());

	SharedObjectTemplate* templateObject = building->getObjectTemplate();

	if (templateObject == NULL)
		return NULL;

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	FloorMesh* floorMesh1 = portalLayout->getFloorMesh(ourCellID);
	PathGraph* pathGraph1 = floorMesh1->getPathGraph();

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA); // adding source

	//info("same cell... trying to calculate triangle path", true);

	Vector<Triangle*>* trianglePath = NULL;

	//info("searching floorMesh for cellID " + String::valueOf(ourCellID), true);

	int res = getFloorPath(pointA.getPoint(), pointB.getPoint(), floorMesh1, trianglePath);

	if (res == -1) { //points in the same triangle
		path->add(pointB);

		return path;
	}

	if (trianglePath == NULL) { // returning NULL, no path found
		//error("path NULL");
		delete path;

		return findPathFromCellToDifferentCell(pointA, pointB);
	} else {
		//info("path found", true);

		addTriangleNodeEdges(pointA.getPoint(), pointB.getPoint(), trianglePath, path, ourCell);

		delete trianglePath;

		path->add(pointB); //adding destination

		return path;
	}

	return path;
}
