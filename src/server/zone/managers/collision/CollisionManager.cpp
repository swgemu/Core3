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

float CollisionManager::getCollisionPoint(CreatureObject* creature) {
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

	if (object1->isCreatureObject())
		heightOrigin = getCollisionPoint((CreatureObject*)object1);

	if (object2->isCreatureObject())
		heightEnd = getCollisionPoint((CreatureObject*)object2);

	rayOrigin.set(rayOrigin.getX(), rayOrigin.getY(), rayOrigin.getZ() + heightOrigin);

	Vector3 rayEnd = object2->getWorldPosition();
	rayEnd.set(rayEnd.getX(), rayEnd.getY(), rayEnd.getZ() + heightEnd);

	float dist = rayEnd.distanceTo(rayOrigin);
	float intersectionDistance;
	Triangle* triangle = NULL;

	zone->rlock();

	for (int i = 0; i < object1->inRangeObjectCount(); ++i) {
		AABBTree* aabbTree = NULL;

		SceneObject* scno = (SceneObject*) object1->getInRangeObject(i);

		try {
			SharedObjectTemplate* templateObject = scno->getObjectTemplate();

			if (templateObject == NULL)
				continue;

			if (templateObject->getCollisionActionBlockFlags() != 255)
				continue;

			PortalLayout* portalLayout = templateObject->getPortalLayout();
			MeshAppearanceTemplate* mesh = NULL;

			if (portalLayout != NULL) {
				mesh = portalLayout->getMeshAppearanceTemplate(0);
			} else {
				AppearanceTemplate* appTemplate = templateObject->getAppearanceTemplate();

				if (appTemplate == NULL)
					continue;

				mesh = dynamic_cast<MeshAppearanceTemplate*>(appTemplate->getFirstMesh());
			}

			if (mesh == NULL)
				continue;

			aabbTree = mesh->getAABBTree();

			if (aabbTree == NULL)
				continue;

		} catch (...) {
			aabbTree = NULL;

			throw;
		}

		if (aabbTree != NULL) {
			//moving ray to model space
			zone->runlock();

			try {
				Matrix4 translationMatrix;
				translationMatrix.setTranslation(-scno->getPositionX(), -scno->getPositionZ(), -scno->getPositionY());

				float rad = -scno->getDirection()->getRadians();
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

				Vector3 transformedOrigin = rayOrigin * modelMatrix;
				Vector3 transformedEnd = rayEnd * modelMatrix;

				Vector3 norm = transformedEnd - transformedOrigin;
				norm.normalize();

				Ray ray(transformedOrigin, norm);

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
