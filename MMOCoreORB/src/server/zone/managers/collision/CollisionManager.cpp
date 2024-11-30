/*
 * CollisionManager.cpp
 *
 *  Created on: 01/03/2011
 *      Author: victor
 */

#include "CollisionManager.h"
#include "server/zone/Zone.h"
#include "server/zone/SpaceZone.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "templates/SharedObjectTemplate.h"
#include "templates/appearance/PortalLayout.h"
#include "templates/appearance/FloorMesh.h"
#include "templates/appearance/PathGraph.h"
#include "terrain/manager/TerrainManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/managers/collision/PathFinderManager.h"

// #define DEBUG_MOVEMENT_COLLISION

float CollisionManager::getRayOriginPoint(CreatureObject* creature) {
	float heightOrigin = creature->getHeight() - 0.3f;

	if (creature->isProne() || creature->isKnockedDown() || creature->isIncapacitated()) {
		heightOrigin = 0.3f;
	} else if (creature->isKneeling()) {
		heightOrigin /= 2.f;
	}

	return heightOrigin;
}

bool CollisionManager::checkLineOfSightInBuilding(SceneObject* object1, SceneObject* object2, SceneObject* building) {
	SharedObjectTemplate* objectTemplate = building->getObjectTemplate();
	const PortalLayout* portalLayout = objectTemplate->getPortalLayout();

	if (portalLayout == nullptr)
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
	Triangle* triangle = nullptr;

	// we check interior cells
	for (int i = 1; i < portalLayout->getAppearanceTemplatesSize(); ++i) {
		const AppearanceTemplate *tmpl = portalLayout->getAppearanceTemplate(i);
		if(tmpl == nullptr)
			continue;

		if(tmpl->intersects(ray, distance, intersectionDistance, triangle, true))
			return false;
	}

	return true;
}

const AppearanceTemplate* CollisionManager::getCollisionAppearance(SceneObject* scno, int collisionBlockFlags) {
	SharedObjectTemplate* templateObject = scno->getObjectTemplate();

	if (templateObject == nullptr)
		return nullptr;

	if (!(templateObject->getCollisionActionBlockFlags() & collisionBlockFlags)) {
		return nullptr;
	}

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	return (portalLayout != nullptr) ? portalLayout->getAppearanceTemplate(0) : templateObject->getAppearanceTemplate();
}

bool CollisionManager::checkSphereCollision(const Vector3& origin, float radius, Zone* zone) {
	Vector3 sphereOrigin(origin.getX(), origin.getZ(), origin.getY());

	SortedVector<ManagedReference<TreeEntry*> > objects(512, 512);
	zone->getInRangeObjects(origin.getX(), origin.getZ(), origin.getY(), 512, &objects, true);

	for (int i = 0; i < objects.size(); ++i) {

		SceneObject* scno = static_cast<SceneObject*>(objects.get(i).get());

		try {
			SharedObjectTemplate* templateObject = scno->getObjectTemplate();

			if (templateObject == nullptr)
				continue;

			if (!(templateObject->getCollisionActionBlockFlags() & 255))
				continue;

			Sphere sphere(convertToModelSpace(sphereOrigin, scno), radius);

			const PortalLayout* portalLayout = templateObject->getPortalLayout();
			if (portalLayout != nullptr) {
				if(portalLayout->getAppearanceTemplate(0)->testCollide(sphere))
					return true;
			} else {
				auto appearanceTemplate = templateObject->getAppearanceTemplate();

				if(appearanceTemplate && appearanceTemplate->testCollide(sphere))
					return true;
			}

		} catch (Exception& e) {

		} catch (...) {
			throw;
		}
	}

	return false;
}

bool CollisionManager::checkLineOfSightWorldToCell(const Vector3& rayOrigin, const Vector3& rayEnd, float distance, CellObject* cellObject) {
	ManagedReference<SceneObject*> building = cellObject->getParent().get();

	if (building == nullptr) {
		return true;
	}

	SharedObjectTemplate* objectTemplate = building->getObjectTemplate();
	const PortalLayout* portalLayout = objectTemplate->getPortalLayout();
	int cellNum = cellObject->getCellNumber();

	if (portalLayout == nullptr) {
		return true;
	}

	const CellProperty* cellProperty = portalLayout->getCellProperty(cellNum);

	if (cellProperty == nullptr) {
		return true;
	}

	if (!cellProperty->hasWorldPortal()) {
		return false;
	}

	Ray ray = convertToModelSpace(rayOrigin, rayEnd, building);

	if (cellNum >= portalLayout->getAppearanceTemplatesSize()) {
		return true;
	}

	const AppearanceTemplate* app = portalLayout->getAppearanceTemplate(cellNum);
	float intersectionDistance;
	Triangle* triangle = nullptr;

	if (app->intersects(ray, distance, intersectionDistance, triangle, true)) {
		return false;
	}

	const SortedVector<int>& connectedCells = cellProperty->getConnectedCells();

	for (int i = 0; i < connectedCells.size(); i++) {
		const AppearanceTemplate* appTemp = portalLayout->getAppearanceTemplate(connectedCells.get(i));

		float intersectDist;
		Triangle* triangle2 = nullptr;

		if (appTemp->intersects(ray, distance, intersectDist, triangle2, true)) {
			return false;
		}
	}

	return true;
}

bool CollisionManager::checkMovementCollision(CreatureObject* player, CloseObjectsVector* closeObjectsVector, Zone* zone, const Vector3& lastValidWorld, const Vector3& transformPosition) {
#ifdef DEBUG_MOVEMENT_COLLISION
	player->info(true) << "CollisionManager::checkMovementCollision -- CALLED";
#endif // DEBUG_MOVEMENT_COLLISION

	if (zone == nullptr || closeObjectsVector == nullptr) {
		return false;
	}

	float rayHeight = getRayOriginPoint(player);

	Vector3 rayStart = lastValidWorld;
	rayStart.setZ(rayStart.getZ() + rayHeight);

	Vector3 rayEnd;

	float dx = rayStart.getX() - transformPosition.getX();
	float dy = rayStart.getY() - transformPosition.getY();

	rayEnd.setX(rayStart.getX() - (dx * 0.25f));
	rayEnd.setY(rayStart.getY() - (dy * 0.25f));
	rayEnd.setZ(transformPosition.getZ() + rayHeight);

#ifdef DEBUG_MOVEMENT_COLLISION
	auto path = new CreateClientPathMessage();

	path->addCoordinate(rayStart.getX(), rayStart.getZ(), rayStart.getY());
	path->addCoordinate(rayEnd.getX(), rayEnd.getZ(), rayEnd.getY());

	player->sendMessage(path);
#endif // DEBUG_MOVEMENT_COLLISION

	float maxDistance = rayStart.distanceTo(rayEnd);

#ifdef DEBUG_MOVEMENT_COLLISION
	player->info(true) << "Movement Collision -- Max Dist: " << maxDistance << " Ray Start: " << rayStart.toString() << " Ray End: " << rayEnd.toString() << " Transform Position: " << transformPosition.toString();
#endif // DEBUG_MOVEMENT_COLLISION

	try {
		// First attempt using navmeshes
		SortedVector<ManagedReference<NavArea*>> areas;

		zone->getInRangeNavMeshes(rayStart.getX(), rayStart.getY(), &areas, true);

#ifdef DEBUG_MOVEMENT_COLLISION
		player->info(true) << "CollisionManager::checkMovementCollision -- Total In Range NavMeshes: " << areas.size();
#endif // DEBUG_MOVEMENT_COLLISION

		if (areas.size() > 0) {
			auto pathFinderMan = PathFinderManager::instance();

			SortedVector<NavCollision*> collisions;
			pathFinderMan->getNavMeshCollisions(&collisions, &areas, rayStart, rayEnd);

			if (collisions.size() == 0) {
				Vector<WorldCoordinates>* path = new Vector<WorldCoordinates>();

				for (int i = 0; i < areas.size(); i++) {
					auto navArea = areas.get(i);

					if (navArea == nullptr) {
						continue;
					}

					if (!pathFinderMan->getRecastPath(rayStart, rayEnd, navArea, path, maxDistance, false)) {
						delete path;
						path = nullptr;

#ifdef DEBUG_MOVEMENT_COLLISION
						StringBuffer msg;
						msg << "CollisionManager::checkMovementCollision -- FAILED -- Due to mesh path failure." << endl;

						player->info(true) << msg.toString();
						player->sendSystemMessage(msg.toString());
#endif // DEBUG_MOVEMENT_COLLISION

						return false;
					}

					delete path;
					path = nullptr;
				}
			}
		}

		// Second attempt using collidable world objects
		SortedVector<TreeEntry*> closeObjects;
		closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::COLLIDABLETYPE);

		for (int i = 0; i < closeObjects.size(); ++i) {
			SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

			if (object == nullptr) {
				continue;
			}

			const auto appearance = object->getAppearanceTemplate();

			if (appearance == nullptr) {
				continue;
			}

			const auto bounding = appearance->getBoundingVolume();

			if (bounding == nullptr) {
				continue;
			}

			const Sphere& objectSphere = bounding->getBoundingSphere();
			const Vector3& objectPosition = object->getPosition() + objectSphere.getCenter();

			float targetRadius = objectSphere.getRadius() + maxDistance;

			if (getPointIntersection(objectPosition, rayStart, rayEnd, targetRadius, maxDistance) == FLT_MAX) {
				continue;
			}

			if (getAppearanceIntersection(object, rayStart, rayEnd, targetRadius, maxDistance) != FLT_MAX) {
#ifdef DEBUG_MOVEMENT_COLLISION
				String str = object->getObjectTemplate()->getFullTemplateString();

				StringBuffer msg;
				msg << "CollisionManager::checkMovementCollision -- FAILED -- Player is intersecting with: " << str << endl;

				player->info(true) << msg.toString();
				player->sendSystemMessage(msg.toString());
#endif // DEBUG_MOVEMENT_COLLISION

				return false;
			}
		}
	} catch (const Exception& e) {
		Logger::console.error("unreported exception caught in bool CollisionManager::checkMovementCollision");
		Logger::console.error(e.getMessage());
	}

	return true;
}

Vector<float>* CollisionManager::getCellFloorCollision(float x, float y, CellObject* cellObject) {
	Vector<float>* collisions = nullptr;

	ManagedReference<SceneObject*> rootObject = cellObject->getRootParent();

	if (rootObject == nullptr)
		return nullptr;

	SharedObjectTemplate* templateObject = rootObject->getObjectTemplate();

	if (templateObject == nullptr)
		return nullptr;

	const PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == nullptr)
		return nullptr;

	const FloorMesh* mesh = portalLayout->getFloorMesh(cellObject->getCellNumber());

	if (mesh == nullptr)
		return nullptr;

	const AABBTree* tree = mesh->getAABBTree();

	if (tree == nullptr)
		return nullptr;

	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	Vector3 norm = rayEnd - rayStart;
	norm.normalize();

	Ray ray(rayStart, norm);

	SortedVector<IntersectionResult> results(3, 2);

	tree->intersects(ray, 16384 * 2, results);

	if (results.size() == 0)
		return nullptr;

	collisions = new Vector<float>(results.size(), 1);

	for (int i = 0; i < results.size(); ++i) {
		float floorHeight = 16384 - results.get(i).getIntersectionDistance();

		collisions->add(floorHeight);
	}

	return collisions;
}

float CollisionManager::getWorldFloorCollision(float x, float y, float z, Zone* zone, bool testWater) {
	if (zone == nullptr)
		return 0.f;

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == nullptr)
		return 0.f;

	SortedVector<TreeEntry*> closeObjects;
	zone->getInRangeObjects(x, z, y, 128, &closeObjects, true, false);

	float height = 0;

	TerrainManager* terrainManager = planetManager->getTerrainManager();

	//need to include exclude affectors in the terrain calcs
	height = terrainManager->getHeight(x, y);

	if (z < height)
		return height;

	if (testWater) {
		float waterHeight;

		if (terrainManager->getWaterHeight(x, y, waterHeight))
			if (waterHeight > height)
				height = waterHeight;
	}

	Ray ray(Vector3(x, z+2.0f, y), Vector3(0, -1, 0));

	for (const auto& entry : closeObjects) {
		SceneObject* sceno = static_cast<SceneObject*>(entry);

		const AppearanceTemplate* app = getCollisionAppearance(sceno, 255);

		if (app != nullptr) {
			Ray rayModelSpace = convertToModelSpace(ray.getOrigin(), ray.getOrigin()+ray.getDirection(), sceno);

			IntersectionResults results;

			app->intersects(rayModelSpace, 16384 * 2, results);

			if (results.size()) { // results are ordered based on intersection distance from min to max
				float floorHeight = ray.getOrigin().getY() - results.getUnsafe(0).getIntersectionDistance();

				if (floorHeight > height)
					height = floorHeight;
			}
		} else {
			continue;
		}
	}

	return height;
}

float CollisionManager::getWorldFloorCollision(float x, float y, Zone* zone, bool testWater) {
	SortedVector<TreeEntry*> closeObjects;
	zone->getInRangeObjects(x, 0, y, 128, &closeObjects, true, false);

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == nullptr)
		return 0.f;

	float height = 0;

	TerrainManager* terrainManager = planetManager->getTerrainManager();

	//need to include exclude affectors in the terrain calcs
	height = terrainManager->getHeight(x, y);

	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	if (testWater) {
		float waterHeight;

		if (terrainManager->getWaterHeight(x, y, waterHeight))
			if (waterHeight > height)
				height = waterHeight;
	}

	for (const auto& entry : closeObjects) {
		SceneObject* sceno = static_cast<SceneObject*>(entry);

		const AppearanceTemplate* app = getCollisionAppearance(sceno, 255);

		if (app != nullptr) {
			Ray ray = convertToModelSpace(rayStart, rayEnd, sceno);

			IntersectionResults results;

			app->intersects(ray, 16384 * 2, results);

			if (results.size()) { // results are ordered based on intersection distance from min to max
				float floorHeight = 16384.f - results.getUnsafe(0).getIntersectionDistance();

				if (floorHeight > height)
					height = floorHeight;
			}
		} else {
			continue;
		}
	}

	return height;
}

void CollisionManager::getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, CloseObjectsVector* closeObjectsVector) {
	if (closeObjectsVector != nullptr) {
		Vector<TreeEntry*> closeObjects(closeObjectsVector->size(), 10);
		closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::COLLIDABLETYPE);

		getWorldFloorCollisions(x, y, zone, result, closeObjects);
	} else {
#ifdef COV_DEBUG
		zone->info("Null closeobjects vector in CollisionManager::getWorldFloorCollisions", true);
#endif
		SortedVector<ManagedReference<TreeEntry*> > closeObjects;

		zone->getInRangeObjects(x, 0, y, 128, &closeObjects, true);

		getWorldFloorCollisions(x, y, zone, result, closeObjects);
	}
}

void CollisionManager::getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, const SortedVector<ManagedReference<TreeEntry*> >& inRangeObjects) {
	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		SceneObject* sceno = static_cast<SceneObject*>(inRangeObjects.get(i).get());

		const AppearanceTemplate* app = getCollisionAppearance(sceno, 255);
		if (app != nullptr) {
			Ray ray = convertToModelSpace(rayStart, rayEnd, sceno);

			app->intersects(ray, 16384 * 2, *result);
		}
	}
}

void CollisionManager::getWorldFloorCollisions(float x, float y, Zone* zone, SortedVector<IntersectionResult>* result, const Vector<TreeEntry*>& inRangeObjects) {
	Vector3 rayStart(x, 16384.f, y);
	Vector3 rayEnd(x, -16384.f, y);

	for (int i = 0; i < inRangeObjects.size(); ++i) {
		SceneObject* sceno = static_cast<SceneObject*>(inRangeObjects.get(i));
		const AppearanceTemplate* app = getCollisionAppearance(sceno, 255);
		if (app != nullptr) {
			Ray ray = convertToModelSpace(rayStart, rayEnd, sceno);

			app->intersects(ray, 16384 * 2, *result);
		}
	}
}

bool CollisionManager::checkLineOfSight(SceneObject* object1, SceneObject* object2) {
	Zone* zone = object1->getZone();

	if (zone == nullptr)
		return false;

	if (object2->getZone() != zone) {
		return false;
	}

	/*if (object1->isAiAgent() || object2->isAiAgent()) {
		Vector<WorldCoordinates>* path = PathFinderManager::instance()->findPath(object1, object2, zone);

		if (path == nullptr)
			return false;
		else
			delete path;
	}*/

	ManagedReference<SceneObject*> rootParent1 = object1->getRootParent();
	ManagedReference<SceneObject*> rootParent2 = object2->getRootParent();

	if (rootParent1 != nullptr || rootParent2 != nullptr) {
		if (rootParent1 == rootParent2) {
			return CollisionManager::checkLineOfSightInBuilding(object1, object2, rootParent1);
		} else if (rootParent1 != nullptr && rootParent2 != nullptr)
			return false; //different buildings
	}

	//switching z<->y, adding player height (head)
	Vector3 rayOrigin = object1->getWorldPosition();

	float heightOrigin = 1.f;
	float heightEnd = 1.f;

	UniqueReference<SortedVector<TreeEntry*>* > closeObjectsNonReference;/* new SortedVector<TreeEntry* >();*/
	UniqueReference<SortedVector<ManagedReference<TreeEntry*> >*> closeObjects;/*new SortedVector<ManagedReference<TreeEntry*> >();*/

	int maxInRangeObjectCount = 0;

	if (object1->getCloseObjects() == nullptr) {
#ifdef COV_DEBUG
		object1->info("Null closeobjects vector in CollisionManager::checkLineOfSight for " + object1->getDisplayedName(), true);
#endif

		closeObjects = new SortedVector<ManagedReference<TreeEntry*> >();
		zone->getInRangeObjects(object1->getPositionX(), object1->getPositionZ(), object1->getPositionY(), 512, closeObjects, true);
	} else {
		closeObjectsNonReference = new SortedVector<TreeEntry* >();

		CloseObjectsVector* vec = (CloseObjectsVector*) object1->getCloseObjects();
		vec->safeCopyReceiversTo(*closeObjectsNonReference.get(), CloseObjectsVector::COLLIDABLETYPE);
	}

	if (object1->isCreatureObject())
		heightOrigin = getRayOriginPoint(object1->asCreatureObject());

	if (object2->isCreatureObject())
		heightEnd = getRayOriginPoint(object2->asCreatureObject());

	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ() + heightOrigin);

	Vector3 rayEnd = object2->getWorldPosition();
	rayEnd.set(rayEnd.getX(), rayEnd.getY(), rayEnd.getZ() + heightEnd);

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;
	Triangle* triangle = nullptr;

	try {
		for (int i = 0; i < (closeObjects != nullptr ? closeObjects->size() : closeObjectsNonReference->size()); ++i) {
			const AppearanceTemplate* app = nullptr;

			SceneObject* scno;

			if (closeObjects != nullptr) {
				scno = static_cast<SceneObject*>(closeObjects->get(i).get());
			} else {
				scno = static_cast<SceneObject*>(closeObjectsNonReference->get(i));
			}

			if (scno == object2)
				continue;

			try {
				app = getCollisionAppearance(scno, 255);

				if (app == nullptr)
					continue;

			} catch (const Exception& e) {
				app = nullptr;
			}

			if (app != nullptr) {
				//moving ray to model space
				Ray ray = convertToModelSpace(rayOrigin, rayEnd, scno);

				//structure->info("checking ray with building dir" + String::valueOf(structure->getDirectionAngle()), true);

				if (app->intersects(ray, dist, intersectionDistance, triangle, true)) {
					return false;
				}
			}
		}
	} catch (const Exception& e) {
		Logger::console.error("unreported exception caught in bool CollisionManager::checkLineOfSight(SceneObject* object1, SceneObject* object2) ");
		Logger::console.error(e.getMessage());
	}

//	zone->runlock();

	ManagedReference<SceneObject*> parent1 = object1->getParent().get();
	ManagedReference<SceneObject*> parent2 = object2->getParent().get();

	if (parent1 != nullptr || parent2 != nullptr) {
		CellObject* cell = nullptr;

		if (parent1 != nullptr && parent1->isCellObject()) {
			cell = cast<CellObject*>(parent1.get());
		} else if (parent2 != nullptr && parent2->isCellObject()) {
			cell = cast<CellObject*>(parent2.get());
		}

		if (cell != nullptr) {
			return checkLineOfSightWorldToCell(rayOrigin, rayEnd, dist, cell);
		}
	}

	return true;
}

const TriangleNode* CollisionManager::getTriangle(const Vector3& point, const FloorMesh* floor) {
	/*PathGraph* graph = node->getPathGraph();
	FloorMesh* floor = graph->getFloorMesh();*/

	const AABBTree* aabbTree = floor->getAABBTree();

	//Vector3 nodePosition = node->getPosition();

	Vector3 rayOrigin(point.getX(), point.getZ() + 0.5, point.getY());
	//Vector3 rayOrigin(point.getX(), point.getY(), point.getZ() + 0.2);
	Vector3 direction(0, -1, 0);

	Ray ray(rayOrigin, direction);

	float intersectionDistance = 0;
	Triangle* triangle = nullptr;

	aabbTree->intersects(ray, 4, intersectionDistance, triangle, true);

	if (triangle == nullptr) {
		//System::out << "CollisionManager::getTriangle triangleNode nullptr" << endl;

		return floor->findNearestTriangle(rayOrigin);
	}

	TriangleNode* triangleNode = static_cast<TriangleNode*>(triangle);

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

	if (modelMatrix == nullptr) {

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

	if (zone == nullptr)
		return false;

	Vector3 rayOrigin = ship->getWorldPosition();

	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ());

	Vector3 rayEnd;
	rayEnd.set(targetPosition.getX(), targetPosition.getY(), targetPosition.getZ());

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;
	Triangle* triangle = nullptr;

	SortedVector<ManagedReference<TreeEntry*> > objects(512, 512);
	zone->getInRangeObjects(targetPosition.getX(), targetPosition.getZ(), targetPosition.getY(), 512, &objects, true);

	for (int i = 0; i < objects.size(); ++i) {
		const AppearanceTemplate *app = nullptr;

		SceneObject* scno = static_cast<SceneObject*>(objects.get(i).get());

		try {
			app = getCollisionAppearance(scno, -1);

			if (app == nullptr)
				continue;

		} catch (Exception& e) {
			app = nullptr;
		} catch (...) {
			throw;
		}

		if (app != nullptr) {
			//moving ray to model space

			try {
				Ray ray = convertToModelSpace(rayOrigin, rayEnd, scno);

				if (app->intersects(ray, dist, intersectionDistance, triangle, true)) {

					Vector3 direction = rayEnd - rayOrigin;
					direction.normalize();

					collisionPoint.set(rayOrigin.getX() + (direction.getX() * intersectionDistance), rayOrigin.getY() + (direction.getY() * intersectionDistance), rayOrigin.getZ() + (direction.getZ() * intersectionDistance));
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

bool CollisionManager::checkShipWeaponCollision(ShipObject* obj, const Vector3 startPosition, const Vector3& targetPosition, Vector3& collisionPoint, Vector<ManagedReference<SceneObject*> >& collidedObjects) {

	Zone* zone = obj->getZone();

	if (zone == nullptr)
		return false;

	Vector3 rayOrigin = startPosition;
	Vector3 rayEnd = targetPosition;

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;

	Triangle* triangle = nullptr;

	Vector3 center = startPosition - ((targetPosition - startPosition) * 0.5f);
	SortedVector<ManagedReference<TreeEntry*> > objects;

	obj->getCloseObjects()->safeCopyTo(objects);

	for (int i = 0; i < objects.size(); ++i) {
		const AppearanceTemplate *app = nullptr;

		SceneObject* scno = cast<SceneObject*>(objects.get(i).get());

		if (scno == obj)
			continue;

		ShipObject* ship = dynamic_cast<ShipObject*>(scno);

		if (ship == nullptr) {
			continue;
		}

		try {
			app = ship->getObjectTemplate()->getAppearanceTemplate();

		} catch (Exception& e) {
			app = nullptr;
		} catch (...) {
			throw;
		}

		if (app != nullptr) {
			//moving ray to model space

			try {
				Ray ray = convertToModelSpace(rayOrigin, rayEnd, ship);
				if (app->intersects(ray, dist, intersectionDistance, triangle, true)) {
					Vector3 point = ray.getOrigin() + (ray.getDirection() * intersectionDistance);
					collisionPoint.set(point.getX(), point.getY(), point.getZ());
					//Logger::console.info("Tri Center: " + triangle->getBarycenter().toString(), true);
					collidedObjects.add(scno);

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

const PathNode* CollisionManager::findNearestPathNode(const TriangleNode* triangle, const FloorMesh* floor, const Vector3& finalTarget) {
	// this is overkill TODO: find something faster
	const PathGraph* graph = floor->getPathGraph();

	if (graph == nullptr)
		return nullptr;

	const Vector<PathNode*>* pathNodes = graph->getPathNodes();

	PathNode* returnNode = nullptr;
	float distance = 16000;
	Vector3 trianglePos(triangle->getBarycenter());
	//trianglePos.set(trianglePos.getX(), trianglePos.getY(), trianglePos.getZ());*/

	for (int i = 0; i < pathNodes->size(); ++i) {
		PathNode* node = pathNodes->get(i);

		const TriangleNode* triangleOfPathNode = getTriangle(node->getPosition(), floor);

		Vector<const Triangle*>* path = TriangulationAStarAlgorithm::search(trianglePos, triangleOfPathNode->getBarycenter(), triangle, triangleOfPathNode);

		if (path == nullptr)
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
	ManagedReference<SceneObject*> parent = object->getParent().get();

	if (parent == nullptr || !parent->isCellObject())
		return true;

	CellObject* cell = cast<CellObject*>( parent.get());

	SharedObjectTemplate* objectTemplate = parent->getRootParent()->getObjectTemplate();
	const PortalLayout* portalLayout = objectTemplate->getPortalLayout();
	const AppearanceTemplate* appearanceMesh = nullptr;

	if (portalLayout == nullptr)
		return true;

	try {
		appearanceMesh = portalLayout->getAppearanceTemplate(cell->getCellNumber());
	} catch (Exception& e) {
		return true;
	}

	if (appearanceMesh == nullptr) {
		//info("null appearance mesh ");
		return true;
	}

	//switching Y<->Z, adding 0.1 to account floor
	Vector3 startPoint = object->getPosition();
	startPoint.set(startPoint.getX(), startPoint.getY(), startPoint.getZ() + 0.1f);

	endPoint.set(endPoint.getX(), endPoint.getY(), endPoint.getZ() + 0.1f);

	Vector3 dir = endPoint - startPoint;
	dir.normalize();

	float distance = endPoint.distanceTo(startPoint);
	float intersectionDistance;

	Ray ray(startPoint, dir);

	Triangle* triangle = nullptr;

	//nothing in the middle
	if (appearanceMesh->intersects(ray, distance, intersectionDistance, triangle, true))
		return false;

	Ray ray2(endPoint, Vector3(0, -1, 0));

	//check if we are in the cell with dir (0, -1, 0)
	if (!appearanceMesh->intersects(ray2, 64000.f, intersectionDistance, triangle, true))
		return false;

	return true;
}

float CollisionManager::getPointIntersection(const Vector3& rayStart, const Vector3& rayEnd, const Vector3& point, float radius, float distance) {
	Vector3 direction = rayEnd - rayStart;
	Vector3 difference = point - rayStart;

	float dotProduct = difference.dotProduct(direction);
	float sqrDistance = distance * distance;
	float sqrRadius = radius * radius;

	if (dotProduct < -sqrRadius || dotProduct > (sqrRadius + sqrDistance)) {
		return FLT_MAX;
	}

	float intersection = dotProduct >= sqrDistance ? 1.f : dotProduct > 0.f ? dotProduct / sqrDistance : 0.f;
	Vector3 position = intersection >= 1.f ? direction : intersection > 0.f ? direction * intersection : Vector3::ZERO;

	float sqrDifference = difference.squaredDistanceTo(position);

	if (sqrDifference > sqrRadius) {
		return FLT_MAX;
	}

	return intersection;
}

float CollisionManager::getAppearanceIntersection(SceneObject* target, const Vector3& rayStart, const Vector3& rayEnd, float radius, float distance) {
	auto appearance = target->getAppearanceTemplate();

	if (appearance == nullptr) {
		return FLT_MAX;
	}

	Ray ray = getAxisAlignedRay(target, rayStart, rayEnd, distance);

	SortedVector<IntersectionResult> results;
	appearance->intersects(ray, distance + radius, results);

	float intersection = FLT_MAX;

	if (results.size() > 0) {
		intersection = Math::max(results.getUnsafe(0).getIntersectionDistance() - radius, 0.f) / Math::max(distance, 1.f);
	}

	return intersection;
}

Ray CollisionManager::getAxisAlignedRay(SceneObject* target, const Vector3& rayStart, const Vector3& rayEnd, float distance) {
	const Vector3& position = target->getPosition();

	Matrix4 rotation;
	rotation.setRotationMatrix(target->getDirection()->toMatrix3());

	float inverseDistance = 1.f / distance;

	Vector3 localStart = getAxisAlignedVector(rayStart - position, rotation);
	Vector3 localEnd = getAxisAlignedVector(rayEnd - position, rotation);
	Vector3 localDirection = (localEnd - localStart) * inverseDistance;

	return Ray(localStart, localDirection);
}

Vector3 CollisionManager::getAxisAlignedVector(const Vector3& position, const Matrix4& rotation) {
	return Vector3(position.getX(), position.getZ(), position.getY()) * rotation;
}
