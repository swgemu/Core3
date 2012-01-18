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

bool CollisionManager::checkSphereCollision(const Vector3& sphereOrigin, float radius, Zone* zone) {
	SortedVector<ManagedReference<QuadTreeEntry*> > objects(512, 512);
	zone->getInRangeObjects(sphereOrigin.getX(), sphereOrigin.getY(), 512, &objects);

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

bool CollisionManager::checkLineOfSight(SceneObject* object1, SceneObject* object2) {
	Zone* zone = object1->getZone();

	if (zone == NULL)
		return false;

	if (object2->getZone() != zone)
		return false;

	SceneObject* rootParent1 = object1->getRootParent();
	SceneObject* rootParent2 = object2->getRootParent();

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
		zone->getInRangeObjects(object1->getPositionX(), object1->getPositionY(), 512, closeObjects.get());
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
	Matrix4 modelMatrix = getTransformMatrix(model);

	Vector3 transformedPoint = point * modelMatrix;

	return transformedPoint;
}

Matrix4 CollisionManager::getTransformMatrix(SceneObject* model) {
	//this can be optimized by storing the matrix on the model and update it when needed
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

	Matrix4 modelMatrix;
	modelMatrix = translationMatrix * rotateMatrix;

	return modelMatrix;
}

Ray CollisionManager::convertToModelSpace(const Vector3& rayOrigin, const Vector3& rayEnd, SceneObject* model) {
	Matrix4 modelMatrix = getTransformMatrix(model);

	Vector3 transformedOrigin = rayOrigin * modelMatrix;
	Vector3 transformedEnd = rayEnd * modelMatrix;

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
	zone->getInRangeObjects(targetPosition.getX(), targetPosition.getY(), 512, &objects);

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

	SharedObjectTemplate* objectTemplate = parent->getRootParent()->getObjectTemplate();
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
