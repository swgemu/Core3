/*
 * PathFinderManager.cpp
 *
 *  Created on: 02/03/2011
 *      Author: victor
 */

#include "PathFinderManager.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/PathGraph.h"
#include "server/zone/Zone.h"

#include "CollisionManager.h"
#include "engine/util/u3d/Funnel.h"
#include "engine/util/u3d/Segment.h"
#include "pathfinding/recast/DetourCommon.h"

//#define DEBUG_PATHING

const static constexpr int MAX_QUERY_NODES = 2048 * 2;

void destroyNavMeshQuery(void* value) {
	dtFreeNavMeshQuery(reinterpret_cast<dtNavMeshQuery*>(value));
}

PathFinderManager::PathFinderManager() : Logger("PathFinderManager"), m_navQuery(destroyNavMeshQuery) {
	setFileLogger("log/pathfinder.log", true, true);
	setLogToConsole(false);
	setGlobalLogging(false);
	setLogSynchronized(true);
	setLogJSON(ConfigManager::instance()->getPathfinderLogJSON());
	setRotateLogSizeMB(ConfigManager::instance()->getRotateLogSizeMB());

	m_filter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL ^ (SAMPLE_POLYFLAGS_DISABLED));
	m_filter.setExcludeFlags(0);
	m_filter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f);
	m_filter.setAreaCost(SAMPLE_POLYAREA_WATER, 15.0f);
	m_filter.setAreaCost(SAMPLE_POLYAREA_ROAD, 1.0f);
	m_filter.setAreaCost(SAMPLE_POLYAREA_DOOR, 1.0f);
	m_filter.setAreaCost(SAMPLE_POLYAREA_GRASS, 2.0f);
	m_filter.setAreaCost(SAMPLE_POLYAREA_JUMP, 1.5f);

	m_spawnFilter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL ^ (SAMPLE_POLYFLAGS_DISABLED | SAMPLE_POLYFLAGS_SWIM));
	m_spawnFilter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f);
	m_spawnFilter.setExcludeFlags(0);

	setLogging(true);
}

Vector<WorldCoordinates>* PathFinderManager::findPath(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone) {
#ifdef PLATFORM_WIN
#undef isnan
#endif

	if (std::isnan(pointA.getX()) || std::isnan(pointA.getY()) || std::isnan(pointA.getZ()))
		return nullptr;

	if (std::isnan(pointB.getX()) || std::isnan(pointB.getY()) || std::isnan(pointB.getZ()))
		return nullptr;

	CellObject* cellA = pointA.getCell();
	CellObject* cellB = pointB.getCell();

	if (cellA == nullptr && cellB == nullptr) { // world -> world
		return findPathFromWorldToWorld(pointA, pointB, zone);
	} else if (cellA != nullptr && cellB == nullptr) { // cell -> world
		return findPathFromCellToWorld(pointA, pointB, zone);
	} else if (cellA == nullptr && cellB != nullptr) { // world -> cell
		return findPathFromWorldToCell(pointA, pointB, zone);
	} else { // cell -> cell, the only left option
		return findPathFromCellToCell(pointA, pointB);
	}
}

void PathFinderManager::filterPastPoints(Vector<WorldCoordinates>* path, SceneObject* object) {
	Vector3 thisWorldPosition = object->getWorldPosition();
	Vector3 thiswP = thisWorldPosition;
	thiswP.setZ(0);

#ifdef DEBUG_PATHING
	for (int i = 0; i < path->size(); ++i) {
		WorldCoordinates coord = path->get(i);

		printf("Filter Past Points initial #%i - ", i);
		printf(" X = %f,", coord.getX());
		printf("Y = %f  ", coord.getY());
		if (coord.getCell() == nullptr) {
			printf(" -- Cell is nullptr -- \n");
		} else {
			printf("Cell ID: %llu \n", coord.getCell()->getObjectID());
		}
	}
#endif

	int i = 2;

	while (i < path->size()) {
		WorldCoordinates coord1 = path->get(i - 1);
		WorldCoordinates coord2 = path->get(i);

		if (path->size() > 2) {
			if (coord1 == coord2) {
				WorldCoordinates point = path->get(i - 1);

#ifdef DEBUG_PATHING
				printf("Removing - X = %f, ", point.getX());
				printf(" Y = %f  -- ", point.getY());
				printf("At Point 1 \n");
#endif
				path->remove(i - 1);
				continue;
			}

			Vector3 initial(coord1.getX(), coord1.getZ(), coord1.getY());
			Vector3 end(coord2.getX(), coord2.getZ(), coord2.getY());

			if (initial == end) {
				WorldCoordinates point2 = path->get(i - 1);

#ifdef DEBUG_PATHING
				printf("Removing - X = %f, ", point2.getX());
				printf(" Y = %f  -- ", point2.getY());
				printf("At Point 2 \n");
#endif

				path->remove(i - 1);
				continue;
			}

			end.setZ(0);

			Vector3 start = coord1.getWorldPosition();
			start.setZ(0);

			Segment sgm(start, end);
			Vector3 closestP = sgm.getClosestPointTo(thiswP);

			if (closestP.distanceTo(thiswP) <= FLT_EPSILON) {
				for (int j = i - 1; j > 0; --j) {
					WorldCoordinates point3 = path->get(j);

#ifdef DEBUG_PATHING
					printf("Removing - X = %f, ", point3.getX());
					printf(" Y = %f -- ", point3.getY());
					printf("At Point 3 \n");
#endif

					path->remove(j);
				}

				continue;
			}
		}

		i++;
	}

#ifdef DEBUG_PATHING
	printf("Filter past points End Size = %i\n", path->size());
#endif
}

bool pointInSphere(const Vector3 &point, const Sphere& sphere) {
	return (point-sphere.getCenter()).length() < sphere.getRadius();
}

static AtomicLong totalTime;

void PathFinderManager::getNavMeshCollisions(SortedVector<NavCollision*> *collisions,
											 const SortedVector<ManagedReference<NavArea*>> *areas,
											 const Vector3& start, const Vector3& end) {
	Vector3 dir = (end-start);
	float maxT = dir.normalize();

	for (const ManagedReference<NavArea*>& area : *areas) {
		if (area->getZone() == nullptr) {
			String name = area->getMeshName();
			error() << "Null zone on navmesh area " << name << " in getNavMeshCollisions";
			continue;
		}

		const AABB* bounds = area->getMeshBounds();

		const Vector3& bPos = bounds->center();
		Vector3 sPos(bPos.getX(), bPos.getZ(), 0);
		sPos.setZ(CollisionManager::getWorldFloorCollision(sPos.getX(), sPos.getY(), area->getZone(), false));
		const float radius = bounds->extents()[bounds->longestAxis()] * .975f;
		float radiusSq = radius*radius;

		//http://www.scratchapixel.com/code.php?id=10&origin=/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes
		Vector3 L = sPos - start;
		float tca = L.dotProduct(dir);
		if (tca < 0) continue;
		float d2 = L.dotProduct(L) - tca * tca;
		if (d2 > radiusSq) continue;
		float thc = sqrt(radiusSq - d2);
		float t1 = tca - thc;
		float t2 = tca + thc;

		if (fabs(t1 - t2) > 0.1f && t1 > 0 && t1 < maxT)
			collisions->put(new NavCollision(start + (dir * t1), t1, area));

		if (t2 > 0 && t2 < maxT)
			collisions->put(new NavCollision(start + (dir * t2), t2, area));
	}
}

dtNavMeshQuery* PathFinderManager::getNavQuery() {
	dtNavMeshQuery* query = m_navQuery.get();

	if (query == nullptr) {
		query = dtAllocNavMeshQuery();
		m_navQuery.set(query);
	}

	return query;
}

bool PathFinderManager::getRecastPath(const Vector3& start, const Vector3& end, NavArea* area, Vector<WorldCoordinates>* path, float& len, bool allowPartial) {
	const Vector3 startPosition(start.getX(), start.getZ(), -start.getY());
	const Vector3 targetPosition(end.getX(), end.getZ(), -end.getY());
	const float* startPosAsFloat = startPosition.toFloatArray();
	const float* tarPosAsFloat = targetPosition.toFloatArray();
	const static float extents[3] = {8, 8, 3};
	dtPolyRef startPoly;
	dtPolyRef endPoly;

	Vector3 areaPos = area->getPosition();
	Zone* zone = area->getZone();

	if (zone == nullptr)
		return false;

	areaPos.setZ(area->getAreaTerrainHeight());

	dtNavMeshQuery* query = getNavQuery();

	ReadLocker rLocker(area);

	RecastNavMesh* navMesh = area->getNavMesh();

	if (navMesh == nullptr || !navMesh->isLoaded())
		return false;

	// We need to flip the Y/Z axis and negate Z to put it in recasts model space
	const Sphere sphere(Vector3(areaPos.getX(), areaPos.getZ(), -areaPos.getY()), area->getRadius());

	query->init(navMesh->getNavMesh(), MAX_QUERY_NODES);

	if (pointInSphere(targetPosition, sphere) || pointInSphere(startPosition, sphere)) {
		Vector3 polyStart;
		Vector3 polyEnd;
		int numPolys;
		const static constexpr int MAX_POLYS = 2048;

		dtPolyRef polyPath[MAX_POLYS];
		int status = 0;

		if (!((status = query->findNearestPoly(startPosAsFloat, extents, &m_filter, &startPoly, polyStart.toFloatArray())) & DT_SUCCESS))
			return false;

		if (!((status = query->findNearestPoly(tarPosAsFloat, extents, &m_filter, &endPoly, polyEnd.toFloatArray())) & DT_SUCCESS))
			return false;

		if (!((status = query->findPath(startPoly, endPoly, polyStart.toFloatArray(), polyEnd.toFloatArray(), &m_filter, polyPath, &numPolys, MAX_POLYS)) & DT_SUCCESS))
			return false;

#ifdef DEBUG_PATHING
		info("findPath result: 0x" + String::hexvalueOf(status), true);
#endif

		if ((status & DT_PARTIAL_RESULT) && !allowPartial)
			return false;

		if (path == nullptr)
			return true;

		if (numPolys) {
			// In case of partial path, make sure the end point is clamped to the last polygon.
			float epos[3];
			dtVcopy(epos, polyEnd.toFloatArray());
			if (polyPath[numPolys - 1] != endPoly) {
#ifdef DEBUG_PATHING
				info("Poly mismatch: Expected: " + String::hexvalueOf((int64)endPoly) + " actual: " + String::hexvalueOf((int64)polyPath[numPolys-1]), true);
#endif
				if (allowPartial)
					query->closestPointOnPoly(polyPath[numPolys - 1], tarPosAsFloat, polyEnd.toFloatArray(), 0);
				else
					return false;
			}

			static constexpr int MAX_PATH_POINTS = 256;

			float pathPoints[MAX_PATH_POINTS][3];
			int numPoints = 0;
			int pathOptions = DT_STRAIGHTPATH_ALL_CROSSINGS;

			status = query->findStraightPath(polyStart.toFloatArray(), polyEnd.toFloatArray(),
									polyPath, numPolys,
									(float*) pathPoints, nullptr, nullptr,
									&numPoints, MAX_PATH_POINTS, pathOptions);
#ifdef DEBUG_PATHING
			info("findStraightPath result: 0x" + String::hexvalueOf(status), true);
			info("number of points = " + String::valueOf(numPoints), true);
#endif
			if (numPoints > 0) {
				for (int i = 0; i < numPoints; i++) {
					//info("PathFind Point : " + point.toString(), true);
					len += pathPoints[i][0] * pathPoints[i][0] + pathPoints[i][2] * pathPoints[i][2];
					path->add(WorldCoordinates(Vector3(pathPoints[i][0], -pathPoints[i][2], pathPoints[i][1]), nullptr));
				}
			}
		}
	}

	return true;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromWorldToWorld(const WorldCoordinates& pointA, const Vector<WorldCoordinates>& endPoints, Zone* zone, bool allowPartial) {
	Vector<WorldCoordinates>* finalpath = new Vector<WorldCoordinates>();
	float finalLengthSq = FLT_MAX;

#ifdef PROFILE_PATHING
	Timer t;
	t.start();
#endif

	for (const WorldCoordinates& pointB : endPoints) {
		const Vector3& startTemp = pointA.getPoint();
		const Vector3& targetTemp = pointB.getPoint();

		SortedVector<ManagedReference<NavArea*> > areas;

		Vector3 mid = startTemp + ((targetTemp-startTemp) * 0.5f);

		zone->getInRangeNavMeshes(mid.getX(), mid.getY(), &areas, true);

		SortedVector<NavCollision*> collisions;

		getNavMeshCollisions(&collisions, &areas, pointA.getWorldPosition(), pointB.getWorldPosition());

		// Collisions are sorted by distance from the start of the line. This is done so that we can chain our path from
		// one navmesh to another if a path spans multiple meshes.
		Vector<WorldCoordinates> *path = new Vector<WorldCoordinates>();
		float len = 0.0f;

		try {
			int collisionSize = collisions.size();

			if (collisionSize == 1) { // we're entering/exiting a navmesh
				NavCollision* collision = collisions.get(0);
				NavArea *area = collision->getNavArea();
				Vector3 position = collision->getPosition();
				position.setZ(CollisionManager::getWorldFloorCollision(position.getX(), position.getY(), zone, true));

				if (area->containsPoint(startTemp.getX(), startTemp.getY())) {
					if (!getRecastPath(startTemp, position, area, path, len, allowPartial)) { // exiting navmesh
						delete collision;
						if (path != nullptr) delete path;
						continue;
					}

					path->add(pointB);

				} else {
					path->add(pointA);

					if (!getRecastPath(position, targetTemp, area, path, len, allowPartial)) { // entering navmesh
						delete collision;
						if (path != nullptr) delete path;
						continue;
					}
				}

				if (len > 0 && len < finalLengthSq) {
					if (finalpath)
						delete finalpath;

					finalLengthSq = len;
					finalpath = path;
					path = nullptr;
				}
			} else if (collisionSize == 0) { // we're already inside a navmesh (or there are no navmeshes around)
				for (int i = 0; i < areas.size(); i++) {
					if (!getRecastPath(startTemp, targetTemp, areas.get(i), path, len, allowPartial)) {
						continue;
					}

					if (len > 0 && len < finalLengthSq) {
						if (finalpath)
							delete finalpath;

						finalLengthSq = len;
						finalpath = path;
						path = new Vector<WorldCoordinates>();
					}
				}
			} else if (collisionSize == 2) { // we're crossing over a mesh or dealing with multiple meshes
				NavCollision* collision1 = collisions.get(0);
				NavArea *area1 = collision1->getNavArea();
				NavCollision* collision2 = collisions.get(1);
				NavArea *area2 = collision2->getNavArea();

				if (area1 == area2) { // crossing same mesh
					path->add(pointA);

					Vector3 position1 = collision1->getPosition();
					position1.setZ(CollisionManager::getWorldFloorCollision(position1.getX(), position1.getY(), zone, false));
					Vector3 position2 = collision2->getPosition();
					position2.setZ(CollisionManager::getWorldFloorCollision(position2.getX(), position2.getY(), zone, false));

					if (!getRecastPath(position1, position2, area1, path, len, allowPartial)) {
						delete collision1;
						delete collision2;
						if (path != nullptr) delete path;
						continue;
					}

					path->add(pointB);

					if (len > 0 && len < finalLengthSq) {
						if (finalpath)
							delete finalpath;

						finalLengthSq = len;
						finalpath = path;
						path = nullptr;
					}
				} else { // TODO: handle multiple meshes

				}
			} else { // TODO: handle multiple meshes

			}
		} catch (...) {
			error("Unhandled pathing exception");

			for (int i=collisions.size()-1; i>=0; i--) {
				NavCollision *collision = collisions.remove(i);
				delete collision;
			}

			delete path;
			path = nullptr;
		}

		for (int i=collisions.size()-1; i>=0; i--) {
			NavCollision *collision = collisions.remove(i);
			delete collision;
		}

		if (path != nullptr)
			delete path;
	}

	if (finalpath && finalpath->size() < 2) { // path could not be evaluated, just return the start/end position
		finalpath->removeAll();
		finalpath->add(pointA);
		finalpath->add(endPoints.get(0));
	}

#ifdef PROFILE_PATHING
	t.stop();
	totalTime.add(t.getElapsedTime());
	info("Spent " + String::valueOf(totalTime.get()) + " in recast", true);
#endif
	return finalpath;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromWorldToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone* zone) {
	Vector<WorldCoordinates> temp;
	temp.add(pointB);
	return findPathFromWorldToWorld(pointA, temp, zone, true);
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromWorldToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone) {
	CellObject* targetCell = pointB.getCell();

	if (targetCell == nullptr)
		return nullptr;

	ManagedReference<BuildingObject*> building = dynamic_cast<BuildingObject*>(targetCell->getParent().get().get());

	if (building == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "building == nullptr in PathFinderManager::findPathFromWorldToCell from " << pointA << " to " << pointB << " in zone " << zoneName;

		return nullptr;
	}

	SharedObjectTemplate* templateObject = building->getObjectTemplate();

	if (templateObject == nullptr)
		return nullptr;

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr)
		return nullptr;

	//find nearest entrance
	const FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0); // get outside layout
	const FloorMesh* interiorFloorMesh = portalLayout->getFloorMesh(targetCell->getCellNumber());

	if (exteriorFloorMesh == nullptr || interiorFloorMesh == nullptr)
		return nullptr;

	const PathGraph* exteriorPathGraph = exteriorFloorMesh->getPathGraph();

	if (exteriorPathGraph == nullptr)
		return nullptr;

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA);

	Vector3 transformedPosition = transformToModelSpace(pointA.getPoint(), building);
	const PathNode* exteriorNode = exteriorPathGraph->findNearestGlobalNode(transformedPosition);

	if (exteriorNode == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "nullptr exterior node for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

	const TriangleNode* nearestInteriorNodeTriangle = CollisionManager::getTriangle(pointB.getPoint(), interiorFloorMesh);

	if (nearestInteriorNodeTriangle == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "nearest node triangle is nullptr for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

	const PathNode* nearestInteriorNode = CollisionManager::findNearestPathNode(nearestInteriorNodeTriangle, interiorFloorMesh, pointB.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (nearestInteriorNode == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "nearest node is nullptr for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

	//find graph from outside to appropriate cell
	Vector<const PathNode*>* pathToCell = portalLayout->getPath(exteriorNode, nearestInteriorNode);

	if (pathToCell == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "getPath from " << exteriorNode << " to " << nearestInteriorNode
			   << " is nullptr for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

#ifdef DEBUG_PATHING
	printf("Pathing - worldToCell Called -- ");
	printf(" Initial Path Size = %i \n", path->size());
#endif

	for (int i = 0; i < pathToCell->size(); ++i) {
		const PathNode* pathNode = pathToCell->get(i);
		const PathGraph* pathGraph = pathNode->getPathGraph();

		const FloorMesh* floorMesh = pathGraph->getFloorMesh();
		int cellID = floorMesh->getCellID();

		//info("cellID:" + String::valueOf(cellID), true);

		if (cellID == 0) { // we are still outside
			WorldCoordinates coord(pathNode->getPosition(), targetCell);

			WorldCoordinates point(coord.getWorldPosition(), nullptr);

#ifdef DEBUG_PATHING
			printf("Adding Path Node with Cell ID = 0 , X = %f ,", point.getX());
			printf("Y = %f \n", point.getY());
#endif

			path->add(point);
		} else { // we are inside the building
			CellObject* pathCell = building->getCell(cellID);

#ifdef DEBUG_PATHING
			printf("Adding Path Node with Cell ID = %i, ", cellID);
			printf(" X = %f ,", pathNode->getPosition().getX());
			printf("Y = %f \n", pathNode->getPosition().getY());
#endif

			WorldCoordinates point(pathNode->getPosition(), pathCell);

			path->add(point);
		}
	}

	delete pathToCell;
	pathToCell = nullptr;

	// path from cell path node to destination point
	Vector<const Triangle*>* trianglePath = nullptr;

	int res = getFloorPath(path->get(path->size() - 1).getPoint(), pointB.getPoint(), interiorFloorMesh, trianglePath);

	if (res != -1 && trianglePath != nullptr)
		addTriangleNodeEdges(path->get(path->size() - 1).getPoint(), pointB.getPoint(), trianglePath, path, targetCell);

	if (trianglePath != nullptr)
		delete trianglePath;

	path->add(pointB);

#ifdef DEBUG_PATHING
	printf(" FINAL PATH POINTS VECTOR - worldToCell: \n");

	for (int i = 0; i < path->size(); ++i) {
		WorldCoordinates coord = path->get(i);

		printf("Final Path Point #%i - ", i);
		printf(" X = %f,", coord.getX());
		printf("Y = %f", coord.getY());
		if (coord.getCell() == nullptr) {
			printf(" -- Cell is nullptr --");
		}

		printf("\n");
	}
#endif

	return path;
}

const FloorMesh* PathFinderManager::getFloorMesh(CellObject* cell) {
	auto building1 = (cell->getParent().get().castTo<BuildingObject*>());

	SharedObjectTemplate* templateObject = building1->getObjectTemplate();

	if (templateObject == nullptr) {
		return nullptr;
	}

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr) {
		return nullptr;
	}

	const FloorMesh* floorMesh1 = portalLayout->getFloorMesh(cell->getCellNumber());

	return floorMesh1;
}

int PathFinderManager::getFloorPath(const Vector3& pointA, const Vector3& pointB, const FloorMesh* floor, Vector<const Triangle*>*& nodes) {
	/*Vector3 objectPos = pointA;
	Vector3 targetPos = pointB;

	StringBuffer objPos;
	objPos << "returning path point x:" << objectPos.getX() << " z:" << objectPos.getZ() << " y:" << objectPos.getY();
	info(objPos.toString(), true);

	//switching y<->z for client coords
	objectPos.set(objectPos.getX(), objectPos.getY(), objectPos.getZ());
	targetPos.set(targetPos.getX(), targetPos.getY(), targetPos.getZ());*/

	//TriangleNode* objectFloor = floor->findNearestTriangle(objectPos);

	const TriangleNode* objectFloor = CollisionManager::getTriangle(pointA, floor);

	/*Vector3 objectFloorVector = objectFloor->getBarycenter();
	StringBuffer objectFoorBar;
	objectFoorBar << "nearest object floor point x:" << objectFloorVector.getX() << " z:" << objectFloorVector.getY() << " y:" << objectFloorVector.getZ();
	info(objectFoorBar.toString(), true);*/

	//TriangleNode* targetFloor = floor->findNearestTriangle(targetPos);
	const TriangleNode* targetFloor = CollisionManager::getTriangle(pointB, floor);

	/*Vector3 targetFloorVector = targetFloor->getBarycenter();
	StringBuffer targetFoorBar;
	targetFoorBar << "nearest target floor point x:" << targetFloorVector.getX() << " z:" << targetFloorVector.getY() << " y:" << targetFloorVector.getZ();
	info(targetFoorBar.toString(), true);*/

	nodes = nullptr;

	if (objectFloor == targetFloor) { // we are on the same triangle, returning pointB
		return -1;
	} else if (objectFloor == nullptr || targetFloor == nullptr)
		return 1;

	nodes = TriangulationAStarAlgorithm::search(pointA, pointB, objectFloor, targetFloor);

	if (nodes == nullptr)
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

Vector<WorldCoordinates>* PathFinderManager::findPathFromCellToWorld(const WorldCoordinates& pointA, const WorldCoordinates& pointB, Zone *zone) {
	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);

	if (path == nullptr)
		return nullptr;

	path->add(pointA);

	CellObject* ourCell = pointA.getCell();
	ManagedReference<BuildingObject*> building = cast<BuildingObject*>( ourCell->getParent().get().get());
	int ourCellID = ourCell->getCellNumber();
	SharedObjectTemplate* templateObject = ourCell->getParent().get()->getObjectTemplate();

	if (templateObject == nullptr) {
		delete path;
		return nullptr;
	}

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr) {
		delete path;
		return nullptr;
	}

	const FloorMesh* sourceFloorMesh = portalLayout->getFloorMesh(ourCellID);

	if (sourceFloorMesh == nullptr) {
		delete path;
		return nullptr;
	}

	const PathGraph* sourcePathGraph = sourceFloorMesh->getPathGraph();

	if (sourcePathGraph == nullptr) {
		delete path;
		return nullptr;
	}

	const FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0);

	if (exteriorFloorMesh == nullptr) {
		delete path;
		return nullptr;
	}

	const PathGraph* exteriorPathGraph = exteriorFloorMesh->getPathGraph();

	if (exteriorPathGraph == nullptr) {
		delete path;
		return nullptr;
	}

	// we need to move world position into model space
	Vector3 transformedPosition = transformToModelSpace(pointB.getPoint(), building);

	//find exit node in our cell
	//PathNode* exitNode = sourcePathGraph->findNearestNode(pointA.getPoint());
	const TriangleNode* nearestTargetNodeTriangle = CollisionManager::getTriangle(pointA.getPoint(), sourceFloorMesh);

	if (nearestTargetNodeTriangle == nullptr) {
		delete path;
		return nullptr;
	}

	const PathNode* exitNode = CollisionManager::findNearestPathNode(nearestTargetNodeTriangle, sourceFloorMesh, transformedPosition);//targetPathGraph->findNearestNode(pointB.getPoint());

	if (exitNode == nullptr) {
		delete path;
		return nullptr;
	}

	//find exterior node
	const PathNode* exteriorNode = exteriorPathGraph->findNearestGlobalNode(transformedPosition);

	if (exteriorNode == nullptr) {
		delete path;
		return nullptr;
	}

	//find path to the exit
	Vector<const PathNode*>* exitPath = portalLayout->getPath(exitNode, exteriorNode);

	if (exitPath == nullptr) {
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "getPath from " << exitNode << " to " << exteriorNode
			   << " exitpath is nullptr for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

	//find triangle path to exitNode
	Vector<const Triangle*>* trianglePath = nullptr;

	int res = getFloorPath(pointA.getPoint(), exitNode->getPosition(), sourceFloorMesh, trianglePath);

	if (res != -1 && trianglePath != nullptr)
		addTriangleNodeEdges(pointA.getPoint(), exitNode->getPosition(), trianglePath, path, ourCell);

	if (trianglePath != nullptr)
		delete trianglePath;

	path->add(WorldCoordinates(exitNode->getPosition(), ourCell));

	//populate cell traversing
	for (int i = 0; i < exitPath->size(); ++i) {
		const PathNode* pathNode = exitPath->get(i);
		const PathGraph* pathGraph = pathNode->getPathGraph();

		const FloorMesh* floorMesh = pathGraph->getFloorMesh();

		int cellID = floorMesh->getCellID();

		if (cellID == 0) { // we are outside
			WorldCoordinates coord(pathNode->getPosition(), ourCell);

			path->add(WorldCoordinates(coord.getWorldPosition(), nullptr));
		} else { // we are inside the building
			CellObject* pathCell = building->getCell(cellID);

			path->add(WorldCoordinates(pathNode->getPosition(), pathCell));
		}
	}

	delete exitPath;
	exitPath = nullptr;

	if (path->size()) {
		Vector<WorldCoordinates>* newPath = findPathFromWorldToWorld(path->get(path->size()-1), pointB, zone);
		if (newPath) {
			path->addAll(*newPath);
			delete newPath;
		}
	} else
		path->add(pointB);

	return path;
}

void PathFinderManager::addTriangleNodeEdges(const Vector3& source, const Vector3& goal, Vector<const Triangle*>* trianglePath,
		Vector<WorldCoordinates>* path, CellObject* cell) {
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
#ifdef DEBUG_PATHING
	info ("findPathFromCellToDifferentCell", true);
#endif
	CellObject* ourCell = pointA.getCell();
	CellObject* targetCell = pointB.getCell();

	if (ourCell == nullptr || targetCell == nullptr)
		return nullptr;

	int ourCellID = ourCell->getCellNumber();
	int targetCellID = targetCell->getCellNumber();

	ManagedReference<BuildingObject*> building1 = cast<BuildingObject*>(ourCell->getParent().get().get());
	ManagedReference<BuildingObject*> building2 = cast<BuildingObject*>(targetCell->getParent().get().get());

	if (building1 != building2) // TODO: implement path finding between 2 buildings
		return nullptr;

	SharedObjectTemplate* templateObject = building1->getObjectTemplate();

	if (templateObject == nullptr)
		return nullptr;

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr)
		return nullptr;

	const FloorMesh* floorMesh1 = portalLayout->getFloorMesh(ourCellID);
	const FloorMesh* floorMesh2 = portalLayout->getFloorMesh(targetCellID);

	if (floorMesh2->getCellID() != targetCellID)
		error("floorMes2 cellID != targetCellID");

	//info("targetCellID:" + String::valueOf(targetCellID), true);

	const PathGraph* pathGraph1 = floorMesh1->getPathGraph();
	const PathGraph* pathGraph2 = floorMesh2->getPathGraph();

	if (pathGraph1 == nullptr || pathGraph2 == nullptr)
		return nullptr;

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA); // adding source

	//PathNode* source = pathGraph1->findNearestNode(pointA.getPoint());
	const TriangleNode* nearestSourceNodeTriangle = CollisionManager::getTriangle(pointA.getPoint(), floorMesh1);

	if (nearestSourceNodeTriangle == nullptr) {
		delete path;
		return nullptr;
	}

	const PathNode* source = CollisionManager::findNearestPathNode(nearestSourceNodeTriangle, floorMesh1, pointA.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (source == nullptr) {
		delete path;
		return nullptr;
	}

	//PathNode* target = pathGraph2->findNearestNode(pointB.getPoint());
	const TriangleNode* nearestTargetNodeTriangle = CollisionManager::getTriangle(pointB.getPoint(), floorMesh2);

	if (nearestTargetNodeTriangle == nullptr) {
		delete path;
		return nullptr;
	}

	const PathNode* target = CollisionManager::findNearestPathNode(nearestTargetNodeTriangle, floorMesh2, pointB.getPoint());//targetPathGraph->findNearestNode(pointB.getPoint());

	if (target == nullptr) {
		delete path;
		return nullptr;
	}

	Vector<const PathNode*>* nodes = portalLayout->getPath(source, target);

	if (nodes == nullptr) {
		log() << "Could not find path from " << source
				<< " to " << target << " in building: "
				<< templateObject->getFullTemplateString();

		delete path;
		return nullptr;
	}

	// FIXME (dannuic): Sometimes nodes only have one entry.... why?
	if (nodes->size() == 1) {
		auto zone = building1->getZone();
		String zoneName = zone == nullptr ? "unknown" : zone->getZoneName();

		error() << "getPath from " << source << " to " << target
			   << " nodes->size() == 1 for building " << templateObject->getFullTemplateString()
				<< " from " << pointA << " to " << pointB << " in zone " << zoneName;

		delete path;
		return nullptr;
	}

	// path from our position to path node
	Vector<const Triangle*>* trianglePath = nullptr;

	int res = getFloorPath(pointA.getPoint(), nodes->get(1)->getPosition(), floorMesh1, trianglePath);

	if (res != -1 && trianglePath != nullptr)
		addTriangleNodeEdges(pointA.getPoint(), nodes->get(1)->getPosition(), trianglePath, path, ourCell);

	if (trianglePath != nullptr) {
		delete trianglePath;
		trianglePath = nullptr;
	}

	WorldCoordinates sourceCellNode(source->getPosition(), ourCell);

	path->add(sourceCellNode);

	//traversing cells
	for (int i = 1; i < nodes->size(); ++i) {
		const PathNode* pathNode = nodes->get(i);
		const PathGraph* pathGraph = pathNode->getPathGraph();

		const FloorMesh* floorMesh = pathGraph->getFloorMesh();

		int cellID = floorMesh->getCellID();

		if (cellID == 0) {
			// We should never have a cellID of 0 when moving cell to cell
			nodes->remove(i);
#ifdef DEBUG_PATHING
			printf("Removing node with cellID = 0 \n");
#endif
		} else {
			CellObject* pathCell = building1->getCell(cellID);

			if (pathCell == nullptr)
				continue;

			WorldCoordinates coord(pathNode->getPosition(), pathCell);

#ifdef DEBUG_PATHING
			printf("Adding Path Node with Cell ID = %i, ", cellID);
			printf(" X = %f ,", coord.getX());
			printf("Y = %f \n", coord.getY());
#endif

			path->add(coord);

			if (i == nodes->size() - 1) {
				if (pathNode != target) {
					error() << "pathNode != target pathNode: " << pathNode->getID() << " target:" << target->getID();
				}

				if (pathCell != targetCell) {
					error("final cell not target cell");
				}
			}
		}
	}

	delete nodes;
	nodes = nullptr;

	// path from cell entrance to destination point
	trianglePath = nullptr;

	res = getFloorPath(path->get(path->size() - 1).getPoint(), pointB.getPoint(), floorMesh2, trianglePath);

	if (res != -1 && trianglePath != nullptr)
		addTriangleNodeEdges(path->get(path->size() - 1).getPoint(), pointB.getPoint(), trianglePath, path, targetCell);

	if (trianglePath != nullptr)
		delete trianglePath;

	path->add(pointB);

#ifdef DEBUG_PATHING
	printf(" FINAL PATH POINTS cell to other cell: \n");

	for (int i = 0; i < path->size(); ++i) {
		WorldCoordinates coord = path->get(i);

		printf("Final Path Point #%i - ", i);
		printf(" X = %f,", coord.getX());
		printf("Y = %f", coord.getY());
		if (coord.getCell() == nullptr) {
			printf(" -- Cell is nullptr -- ");
		} else {
			printf("Cell ID: %llu \n", coord.getCell()->getObjectID());
		}
	}
#endif

	return path;
}

Vector<WorldCoordinates>* PathFinderManager::findPathFromCellToCell(const WorldCoordinates& pointA, const WorldCoordinates& pointB) {
	CellObject* ourCell = pointA.getCell();
	CellObject* targetCell = pointB.getCell();

	if (ourCell == nullptr || targetCell == nullptr)
		return nullptr;

	if (ourCell != targetCell)
		return findPathFromCellToDifferentCell(pointA, pointB);

	int ourCellID = ourCell->getCellNumber();

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>( ourCell->getParent().get().get());

	SharedObjectTemplate* templateObject = building->getObjectTemplate();

	if (templateObject == nullptr)
		return nullptr;

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr)
		return nullptr;

	const FloorMesh* floorMesh1 = portalLayout->getFloorMesh(ourCellID);
	const PathGraph* pathGraph1 = floorMesh1->getPathGraph();

	Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>(5, 1);
	path->add(pointA); // adding source

	//info("same cell... trying to calculate triangle path", true);

	Vector<const Triangle*>* trianglePath = nullptr;

	//info("searching floorMesh for cellID " + String::valueOf(ourCellID), true);

	int res = getFloorPath(pointA.getPoint(), pointB.getPoint(), floorMesh1, trianglePath);

	if (res == -1) { //points in the same triangle
		path->add(pointB);

		return path;
	}

	if (trianglePath == nullptr) { // returning nullptr, no path found
		//error("path nullptr");
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

float frand() {
	return System::getMTRand()->randExc();
}

bool PathFinderManager::getSpawnPointInArea(const Sphere& area, Zone *zone, Vector3& point, bool checkPath) {
	SortedVector<ManagedReference<NavArea*>> areas;
	float radius = area.getRadius();
	const Vector3& center = area.getCenter();
	Vector3 flipped(center.getX(), center.getZ(), -center.getY());
	const float extents[3] = {3, 5, 3};

	dtNavMeshQuery* query = getNavQuery();

	if (zone == nullptr)
		return false;

	zone->getInRangeNavMeshes(center.getX(), center.getY(), &areas, true);

	if (areas.size() == 0) {
		Vector3 temp((frand() * 2.0f) - 1.0f, (frand() * 2.0f) - 1.0f, 0);
		Vector3 result = temp * (frand() * radius);
		point = center + result;
		point.setZ(CollisionManager::getWorldFloorCollision(point.getX(), point.getY(), zone, false));
		return true;
	}

	for (const auto& navArea : areas) {
		Vector3 polyStart;
		dtPolyRef startPoly;
		dtPolyRef ref;
		int status = 0;
		float pt[3];

		RecastNavMesh *mesh = navArea->getNavMesh();
		if (mesh == nullptr)
			continue;

		ReadLocker rLocker(navArea);

		dtNavMesh *dtNavMesh = mesh->getNavMesh();
		if (dtNavMesh == nullptr)
			continue;

		query->init(dtNavMesh, MAX_QUERY_NODES);

		if (!((status = query->findNearestPoly(flipped.toFloatArray(), extents, &m_spawnFilter, &startPoly, polyStart.toFloatArray())) & DT_SUCCESS))
			continue;

		for (int i=0; i<50; i++) {
			try {
				if (!((status = query->findRandomPointAroundCircle(startPoly, polyStart.toFloatArray(), radius, &m_spawnFilter, frand, &ref, pt)) & DT_SUCCESS)) {
					continue;
				} else {
					point = Vector3(pt[0], -pt[2], CollisionManager::getWorldFloorCollision(pt[0], -pt[2], zone, false));

					Vector3 temp = point - center;
					float len = temp.length();
					if (len > radius) {
						float multiplier = (frand() * radius) / len;
						temp.setX(temp.getX() * multiplier);
						temp.setY(temp.getY() * multiplier);
						point = center + temp;
						radius = len;

						point.setZ(CollisionManager::getWorldFloorCollision(point.getX(), point.getY(), zone, false));
					}
				}

				if (checkPath && !getRecastPath(center, point, navArea, nullptr, radius, false)) {
					continue;
				}

				return true;
			} catch (Exception& exc) {
				error(exc.getMessage());
			}
		}
	}

	return false;
}
