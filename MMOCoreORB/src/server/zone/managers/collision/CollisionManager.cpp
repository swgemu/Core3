/*
 * CollisionManager.cpp
 *
 *  Created on: 01/03/2011
 *      Author: victor
 */

#include "CollisionManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"
#include "server/zone/managers/terrain/TerrainManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/area/ActiveArea.h"

float CollisionManager::getRayOriginPoint(CreatureObject* creature) {
	float heightOrigin = creature->getHeight() - 0.3f;

	if (creature->isProne() || creature->isKnockedDown() || creature->isIncapacitated()) {
		heightOrigin = 0.3;
	} else if (creature->isKneeling()) {
		heightOrigin /= 2.f;
	}

	return heightOrigin;
}

bool CollisionManager::checkLineOfSightInBuilding(SceneObject* object1, SceneObject* object2, SceneObject* building) {
	SharedObjectTemplate* objectTemplate = building->getObjectTemplate();
	PortalLayout* portalLayout = objectTemplate->getPortalLayout();

	if (portalLayout == NULL)
		return true;

	//we are in model space... in cells
	Vector3 rayOrigin = object1->getPosition();
	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ() + 1.f);

	Vector3 rayEnd = object2->getPosition();
	rayEnd.set(rayEnd.getX(), rayEnd.getY(), rayEnd.getZ() + 1.f);

	Vector3 direction(Vector3(rayEnd - rayOrigin));
	direction.normalize();

	float distance = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;

	Ray ray(rayOrigin, direction);
	Triangle* triangle = NULL;

	// we check interior cells
	for (int i = 1; i < portalLayout->getAppearanceTemplatesSize(); ++i) {
		MeshAppearanceTemplate* app = portalLayout->getMeshAppearanceTemplate(i);

		AABBTree* aabbTree = app->getAABBTree();

		if (aabbTree == NULL)
			continue;

		if (aabbTree->intersects(ray, distance, intersectionDistance, triangle, true))
			return false;
	}

	return true;
}

AABBTree* CollisionManager::getAABBTree(SceneObject* scno, int collisionBlockFlags) {
	SharedObjectTemplate* templateObject = scno->getObjectTemplate();

	if (templateObject == NULL)
		return NULL;

	if (!(templateObject->getCollisionActionBlockFlags() & collisionBlockFlags))
		return NULL;

	PortalLayout* portalLayout = templateObject->getPortalLayout();
	MeshAppearanceTemplate* mesh = NULL;

	if (portalLayout != NULL) {
		mesh = portalLayout->getMeshAppearanceTemplate(0);
	} else {
		AppearanceTemplate* appTemplate = templateObject->getAppearanceTemplate();

		if (appTemplate == NULL)
			return NULL;

		mesh = dynamic_cast<MeshAppearanceTemplate*>(appTemplate->getFirstMesh());
	}

	if (mesh == NULL)
		return NULL;

	return mesh->getAABBTree();
}

bool CollisionManager::checkSphereCollision(const Vector3& origin, float radius, Zone* zone) {
	Vector3 sphereOrigin(origin.getX(), origin.getZ(), origin.getY());

	SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
	zone->getInRangeObjects(origin.getX(), origin.getY(), 512, &objects, true);

	for (int i = 0; i < objects.size(); ++i) {
		AABBTree* aabbTree = NULL;

		SceneObject* scno = cast<SceneObject*>(objects.get(i).get());

		try {
			aabbTree = getAABBTree(scno, -1);

			if (aabbTree == NULL)
				continue;

		} catch (Exception& e) {
			aabbTree = NULL;
		} catch (...) {
			throw;
		}

		if (aabbTree != NULL) {
			//moving ray to model space

			try {
				Sphere sphere(convertToModelSpace(sphereOrigin, scno), radius);
				//structure->info("checking ray with building dir" + String::valueOf(structure->getDirectionAngle()), true);

				if (aabbTree->testCollide(sphere)) {
					return true;
				}
			} catch (Exception& e) {
				scno->error(e.getMessage());
			} catch (...) {
				throw;
			}
		}
	}

	return false;
}

bool CollisionManager::checkLineOfSightWorldToCell(const Vector3& rayOrigin, const Vector3& rayEnd, float distance, CellObject* cellObject) {
	ManagedReference<SceneObject*> building = cellObject->getParent();

	if (building == NULL)
		return true;

	SharedObjectTemplate* objectTemplate = building->getObjectTemplate();
	PortalLayout* portalLayout = objectTemplate->getPortalLayout();

	if (portalLayout == NULL)
		return true;

	Ray ray = convertToModelSpace(rayOrigin, rayEnd, building);

	if (cellObject->getCellNumber() >= portalLayout->getAppearanceTemplatesSize())
		return true;

	MeshAppearanceTemplate* app = portalLayout->getMeshAppearanceTemplate(cellObject->getCellNumber());

	AABBTree* aabbTree = app->getAABBTree();

	if (aabbTree == NULL)
		return true;

	float intersectionDistance;
	Triangle* triangle = NULL;

	if (aabbTree->intersects(ray, distance, intersectionDistance, triangle, true))
		return false;

	return true;
}

bool CollisionManager::checkMovementCollision(CreatureObject* creature, float x, float z, float y, Zone* zone) {
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(x, y, 128, &closeObjects, true);

	//Vector3 rayStart(x, z + 0.25, y);
	//Vector3 rayStart(creature->getWorldPositionX(), creature->getWorldPositionZ(), creature->getPos)
	Vector3 rayStart = creature->getWorldPosition();
	rayStart.set(rayStart.getX(), rayStart.getY(), rayStart.getZ() + 0.25f);
	//Vector3 rayEnd(x + System::random(512), z + 0.3f, y + System::random(512));

	/*Vector3 rayEnd;
	rayEnd.set(targetPosition.getX(), targetPosition.getY(), targetPosition.getZ());*/

	Vector3 rayEnd(x, z + 0.25, y);

	float maxDistance = rayEnd.distanceTo(rayStart);

	if (maxDistance == 0)
		return false;

	printf("%f\n", maxDistance);

	SortedVector<IntersectionResult> results;
	results.setAllowDuplicateInsertPlan();

	printf("starting test\n");

	Triangle* triangle;

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* object = dynamic_cast<SceneObject*>(closeObjects.get(i).get());

		if (object == NULL)
			continue;

		AABBTree* tree = getAABBTree(object, 255);

		if (tree == NULL)
			continue;

		Ray ray = convertToModelSpace(rayStart, rayEnd, object);

		//results.removeAll(10, 10);

		//ordered by intersection distance
		//tree->intersects(ray, maxDistance, results);

		float intersectionDistance;

		if (tree->intersects(ray, maxDistance, intersectionDistance, triangle, true)) {
			String str = object->getObjectTemplate()->getFullTemplateString();

			object->info("intersecting with me " + str, true);
			return true;
		}
	}

	return false;
}

Vector<float>* CollisionManager::getCellFloorCollision(float x, float y, CellObject* cellObject) {
	Vector<float>* collisions = NULL;

	ManagedReference<SceneObject*> rootObject = cellObject->getRootParent();

	if (rootObject == NULL)
		return NULL;

	SharedObjectTemplate* templateObject = rootObject->getObjectTemplate();

	if (templateObject == NULL)
		return NULL;

	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	FloorMesh* mesh = portalLayout->getFloorMesh(cellObject->getCellNumber());

	if (mesh == NULL)
		return NULL;

	AABBTree* tree = mesh->getAABBTree();

	if (tree == NULL)
		return NULL;

	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	Vector3 norm = rayEnd - rayStart;
	norm.normalize();

	Ray ray(rayStart, norm);

	SortedVector<IntersectionResult> results(3, 2);

	tree->intersects(ray, 16384 * 2, results);

	if (results.size() == 0)
		return NULL;

	collisions = new Vector<float>(results.size(), 1);

	for (int i = 0; i < results.size(); ++i) {
		float floorHeight = 16384 - results.get(i).getIntersectionDistance();

		collisions->add(floorHeight);
	}

	return collisions;
}

float CollisionManager::getWorldFloorCollision(float x, float y, Zone* zone, bool testWater) {
	SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
	zone->getInRangeObjects(x, y, 128, &closeObjects, true);

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == NULL)
		return 0.f;

	float height = 0;

	TerrainManager* terrainManager = planetManager->getTerrainManager();

	//need to include exclude affectors in the terrain calcs
	height = terrainManager->getHeight(x, y);

	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	Triangle* triangle = NULL;

	if (testWater) {
		float waterHeight;

		if (terrainManager->getWaterHeight(x, y, waterHeight))
			if (waterHeight > height)
				height = waterHeight;
	}

	float intersectionDistance;

	for (int i = 0; i < closeObjects.size(); ++i) {
		BuildingObject* building = dynamic_cast<BuildingObject*>(closeObjects.get(i).get());

		if (building == NULL)
			continue;

		//building->getObjectTemplate()->get

		SharedObjectTemplate* templateObject = building->getObjectTemplate();

		if (templateObject == NULL)
			continue;

		PortalLayout* portalLayout = templateObject->getPortalLayout();

		if (portalLayout == NULL)
			continue;

		if (portalLayout->getFloorMeshNumber() == 0)
			continue;

		//find nearest entrance
		FloorMesh* exteriorFloorMesh = portalLayout->getFloorMesh(0); // get outside layout
		AABBTree* aabbTree = exteriorFloorMesh->getAABBTree();

		if (aabbTree == NULL)
			continue;

		Ray ray = convertToModelSpace(rayStart, rayEnd, building);

		if (aabbTree->intersects(ray, 16384 * 2, intersectionDistance, triangle, true)) {
			float floorHeight = 16384 - intersectionDistance;

			if (floorHeight > height)
				height = floorHeight;
		}
	}

	return height;
}

bool CollisionManager::checkLineOfSight(SceneObject* object1, SceneObject* object2) {
	Zone* zone = object1->getZone();

	if (zone == NULL)
		return false;

	if (object2->getZone() != zone)
		return false;

	ManagedReference<SceneObject*> rootParent1 = object1->getRootParent();
	ManagedReference<SceneObject*> rootParent2 = object2->getRootParent();

	if (rootParent1 != NULL || rootParent2 != NULL) {
		if (rootParent1 == rootParent2) {
			return CollisionManager::checkLineOfSightInBuilding(object1, object2, rootParent1);
		} else if (rootParent1 != NULL && rootParent2 != NULL)
			return false; //different buildings
	}

	//switching z<->y, adding player height (head)
	Vector3 rayOrigin = object1->getWorldPosition();

	float heightOrigin = 1.f;
	float heightEnd = 1.f;

	Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> closeObjects = object1->getCloseObjects();

	int maxInRangeObjectCount = 0;

	if (closeObjects == NULL) {
		closeObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
		zone->getInRangeObjects(object1->getPositionX(), object1->getPositionY(), 512, closeObjects.get(), true);
	}

	if (object1->isCreatureObject())
		heightOrigin = getRayOriginPoint(cast<CreatureObject*>(object1));

	if (object2->isCreatureObject())
		heightEnd = getRayOriginPoint(cast<CreatureObject*>(object2));

	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ() + heightOrigin);

	Vector3 rayEnd = object2->getWorldPosition();
	rayEnd.set(rayEnd.getX(), rayEnd.getY(), rayEnd.getZ() + heightEnd);

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;
	Triangle* triangle = NULL;

	zone->rlock();

	try {
		for (int i = 0; i < closeObjects->size(); ++i) {
			AABBTree* aabbTree = NULL;

			SceneObject* scno = cast<SceneObject*>(closeObjects->get(i).get());

			try {
				aabbTree = getAABBTree(scno, 255);

				if (aabbTree == NULL)
					continue;

			} catch (Exception& e) {
				aabbTree = NULL;
			} catch (...) {
				zone->runlock();

				throw;
			}

			if (aabbTree != NULL) {
				//moving ray to model space
				zone->runlock();

				try {
					Ray ray = convertToModelSpace(rayOrigin, rayEnd, scno);

					//structure->info("checking ray with building dir" + String::valueOf(structure->getDirectionAngle()), true);

					if (aabbTree->intersects(ray, dist, intersectionDistance, triangle, true)) {
						return false;
					}
				} catch (...) {
					throw;
				}

				zone->rlock();

			}
		}
	} catch (Exception& e) {
		Logger::console.error("unreported exception caught in bool CollisionManager::checkLineOfSight(SceneObject* object1, SceneObject* object2) ");
		Logger::console.error(e.getMessage());
	}

	zone->runlock();

	ManagedReference<SceneObject*> parent1 = object1->getParent();
	ManagedReference<SceneObject*> parent2 = object2->getParent();

	if (parent1 != NULL || parent2 != NULL) {
		CellObject* cell = NULL;

		if (parent1 != NULL && parent1->isCellObject()) {
			cell = cast<CellObject*>(parent1.get());
		} else if (parent2 != NULL && parent2->isCellObject()) {
			cell = cast<CellObject*>(parent2.get());
		}

		if (cell != NULL) {
			return checkLineOfSightWorldToCell(rayOrigin, rayEnd, dist, cell);
		}
	}

	return true;

}


TriangleNode* CollisionManager::getTriangle(const Vector3& point, FloorMesh* floor) {
	/*PathGraph* graph = node->getPathGraph();
	FloorMesh* floor = graph->getFloorMesh();*/

	AABBTree* aabbTree = floor->getAABBTree();

	//Vector3 nodePosition = node->getPosition();

	Vector3 rayOrigin(point.getX(), point.getZ() + 0.5, point.getY());
	//Vector3 rayOrigin(point.getX(), point.getY(), point.getZ() + 0.2);
	Vector3 direction(0, -1, 0);

	Ray ray(rayOrigin, direction);

	float intersectionDistance = 0;
	Triangle* triangle = NULL;

	aabbTree->intersects(ray, 4, intersectionDistance, triangle, true);

	TriangleNode* triangleNode = dynamic_cast<TriangleNode*>(triangle);

	if (triangleNode == NULL) {
		//System::out << "CollisionManager::getTriangle triangleNode NULL" << endl;

		return floor->findNearestTriangle(rayOrigin);
	}

	return triangleNode;
}

Vector3 CollisionManager::convertToModelSpace(const Vector3& point, SceneObject* model) {
	Reference<Matrix4*> modelMatrix = getTransformMatrix(model);

	Vector3 transformedPoint = point * *modelMatrix;

	return transformedPoint;
}

Reference<Matrix4*> CollisionManager::getTransformMatrix(SceneObject* model) {
	//this can be optimized by storing the matrix on the model and update it when needed
	//Reference

	Reference<Matrix4*> modelMatrix = model->getTransformForCollisionMatrix();

	if (modelMatrix == NULL) {
		//modelMatrix = new Matrix4();

		Matrix4 translationMatrix;
		translationMatrix.setTranslation(-model->getPositionX(), -model->getPositionZ(), -model->getPositionY());

		float rad = -model->getDirection()->getRadians();
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

		//Matrix4 modelMatrix;
		modelMatrix = new Matrix4(translationMatrix * rotateMatrix);

		model->setTransformForCollisionMatrixIfNull(modelMatrix);
	}

	return modelMatrix;
}

Ray CollisionManager::convertToModelSpace(const Vector3& rayOrigin, const Vector3& rayEnd, SceneObject* model) {
	Reference<Matrix4*> modelMatrix = getTransformMatrix(model);

	Vector3 transformedOrigin = rayOrigin * *modelMatrix;
	Vector3 transformedEnd = rayEnd * *modelMatrix;

	Vector3 norm = transformedEnd - transformedOrigin;
	norm.normalize();

	Ray ray(transformedOrigin, norm);

	return ray;
}

bool CollisionManager::checkShipCollision(ShipObject* ship, const Vector3& targetPosition, Vector3& collisionPoint) {
	Zone* zone = ship->getZone();

	if (zone == NULL)
		return false;

	TerrainManager* terrainManager = zone->getPlanetManager()->getTerrainManager();

	float height = terrainManager->getHeight(targetPosition.getX(), targetPosition.getY());

	float waterHeight = -16368.f;

	if (terrainManager->getWaterHeight(targetPosition.getY(), targetPosition.getY(), waterHeight))
		height = MAX(waterHeight, height);

	if (height > targetPosition.getZ()) {
		collisionPoint = targetPosition;
		collisionPoint.setZ(height);
		//ship->info("colliding with terrain", true);
		return true;
	}

	Vector3 rayOrigin = ship->getWorldPosition();

	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ());

	Vector3 rayEnd;
	rayEnd.set(targetPosition.getX(), targetPosition.getY(), targetPosition.getZ());

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;
	Triangle* triangle = NULL;

	SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
	zone->getInRangeObjects(targetPosition.getX(), targetPosition.getY(), 512, &objects, true);

	for (int i = 0; i < objects.size(); ++i) {
		AABBTree* aabbTree = NULL;

		SceneObject* scno = cast<SceneObject*>(objects.get(i).get());

		try {
			aabbTree = getAABBTree(scno, -1);

			if (aabbTree == NULL)
				continue;

		} catch (Exception& e) {
			aabbTree = NULL;
		} catch (...) {
			throw;
		}

		if (aabbTree != NULL) {
			//moving ray to model space

			try {
				Ray ray = convertToModelSpace(rayOrigin, rayEnd, scno);

				//structure->info("checking ray with building dir" + String::valueOf(structure->getDirectionAngle()), true);

				if (aabbTree->intersects(ray, dist, intersectionDistance, triangle, true)) {

					//rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ());
					Vector3 direction = rayEnd - rayOrigin;
					direction.normalize();
					//intersectionDistance -= 0.5f;

					collisionPoint.set(rayOrigin.getX() + (direction.getX() * intersectionDistance), rayOrigin.getY() + (direction.getY() * intersectionDistance), rayOrigin.getZ() + (direction.getZ() * intersectionDistance));
					//ship->info("colliding with building", true);

					return true;
				}
			} catch (Exception& e) {
				ship->error(e.getMessage());
			} catch (...) {
				throw;
			}


		}
	}

	return false;
}

PathNode* CollisionManager::findNearestPathNode(TriangleNode* triangle, FloorMesh* floor, const Vector3& finalTarget) {
	// this is overkill TODO: find something faster
	PathGraph* graph = floor->getPathGraph();
	Vector<PathNode*>* pathNodes = graph->getPathNodes();
	PathNode* returnNode = NULL;
	float distance = 16000;
	Vector3 trianglePos(triangle->getBarycenter());
	//trianglePos.set(trianglePos.getX(), trianglePos.getY(), trianglePos.getZ());*/

	for (int i = 0; i < pathNodes->size(); ++i) {
		PathNode* node = pathNodes->get(i);

		TriangleNode* triangleOfPathNode = getTriangle(node->getPosition(), floor);

		Vector<Triangle*>* path = TriangulationAStarAlgorithm::search(trianglePos, triangleOfPathNode->getBarycenter(), triangle, triangleOfPathNode);

		if (path == NULL)
			continue;
		else {
			delete path;

			float sqrDistance = node->getPosition().squaredDistanceTo(finalTarget);

			if (sqrDistance < distance) {
				distance = sqrDistance;
				returnNode = node;
			}
		}
	}

	return returnNode;
}

bool CollisionManager::checkLineOfSightInParentCell(SceneObject* object, Vector3& endPoint) {
	ManagedReference<SceneObject*> parent = object->getParent();

	if (parent == NULL || !parent->isCellObject())
		return true;

	CellObject* cell = cast<CellObject*>( parent.get());

	SharedObjectTemplate* objectTemplate = parent->getRootParent().get()->getObjectTemplate();
	PortalLayout* portalLayout = objectTemplate->getPortalLayout();
	MeshAppearanceTemplate* appearanceMesh = NULL;

	if (portalLayout == NULL)
		return true;

	try {
		appearanceMesh = portalLayout->getMeshAppearanceTemplate(cell->getCellNumber());
	} catch (Exception& e) {
		return true;
	}

	if (appearanceMesh == NULL) {
		//info("null appearance mesh ");
		return true;
	}

	AABBTree* aabbTree = appearanceMesh->getAABBTree();

	if (aabbTree == NULL)
		return true;

	//switching Y<->Z, adding 0.1 to account floor
	Vector3 startPoint = object->getPosition();
	startPoint.set(startPoint.getX(), startPoint.getY(), startPoint.getZ() + 0.1f);

	endPoint.set(endPoint.getX(), endPoint.getY(), endPoint.getZ() + 0.1f);

	Vector3 dir = endPoint - startPoint;
	dir.normalize();

	float distance = endPoint.distanceTo(startPoint);
	float intersectionDistance;

	Ray ray(startPoint, dir);

	Triangle* triangle = NULL;

	//nothing in the middle
	if (aabbTree->intersects(ray, distance, intersectionDistance, triangle, true))
		return false;

	Ray ray2(endPoint, Vector3(0, -1, 0));

	//check if we are in the cell with dir (0, -1, 0)
	if (!aabbTree->intersects(ray2, 64000.f, intersectionDistance, triangle, true))
		return false;

	return true;
}
