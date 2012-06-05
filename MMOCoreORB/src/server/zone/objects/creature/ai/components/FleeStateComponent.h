/*
 * FleeStateComponent.h
 *
 *  Created on: May 17, 2012
 *      Author: da
 */

#ifndef FLEESTATECOMPONENT_H_
#define FLEESTATECOMPONENT_H_

#include "AiStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"
#include "server/zone/templates/appearance/PathNode.h"

class FleeStateComponent : public AiStateComponent {
public:
	uint16 doRecovery(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		host->activateHAMRegeneration();
		host->activateStateRecovery();
		actor->activatePostureRecovery();

		ManagedReference<SceneObject*> followObject = actor->getFollowObject();
		if (followObject == NULL || !host->isInRange(followObject, 128.f))
			return AiActor::FORGOT;

		actor->activateRecovery();

		return AiActor::UNFINISHED;
	}

	uint16 doMovement(AiActor* actor) {
		ManagedReference<CreatureObject*> host = actor->getHost();
		if (host == NULL)
			return AiActor::NONE;

		if (host->isDead())
			return AiActor::DEAD;

		ManagedReference<SceneObject*> followObject = actor->getFollowObject();
		if (followObject == NULL || !host->isInRange(followObject, 128.f))
			return AiActor::FORGOT;

		// clear patrol points every time we do this to make sure they are always running away
		PatrolPointsVector* patrolPoints = actor->getPatrolPoints();
		patrolPoints->removeAll();
		PatrolPoint point = getFleeLocation(host, actor->getFollowObject());
		setNextPosition(actor, point.getPositionX(), point.getPositionZ(), point.getPositionY(), point.getCell());

		return AiStateComponent::doMovement(actor);
	}

	float getSpeed(CreatureObject* host) {
		return host->getRunSpeed();
	}

	PatrolPoint getFleeLocation(CreatureObject* host, SceneObject* followObject) {
		Vector3 agressorVector = 2 * host->getWorldPosition() - followObject->getWorldPosition();
		PatrolPoint nextPoint = PatrolPoint(agressorVector);
		nextPoint.setPositionZ(host->getZone()->getHeight(nextPoint.getPositionX(), nextPoint.getPositionY()));

		ManagedReference<SceneObject*> parent = host->getParent();
		if (parent != NULL && parent->isCellObject()) {
			CellObject* ourCell = cast<CellObject*>(parent.get());
			BuildingObject* building = cast<BuildingObject*>(ourCell->getParent());
			int ourCellID = ourCell->getCellNumber();
			SharedObjectTemplate* templateObject = ourCell->getParent()->getObjectTemplate();

			if (templateObject == NULL)
				return nextPoint;

			PortalLayout* portalLayout = templateObject->getPortalLayout();

			if (portalLayout == NULL)
				return nextPoint;

			FloorMesh* sourceFloorMesh = portalLayout->getFloorMesh(ourCellID);
			PathGraph* sourcePathGraph = sourceFloorMesh->getPathGraph();

			PathNode* exitPathNode = sourcePathGraph->findNearestGlobalNode(agressorVector);
			int newCellID = portalLayout->getFloorMeshID(exitPathNode->getGlobalGraphNodeID(), ourCellID);

			Vector<PathNode*>* pathNodes = sourcePathGraph->getPathNodes();

			// there's an adjacent cell to run to
			if (newCellID >= 0)
				pathNodes = portalLayout->getFloorMesh(newCellID)->getPathGraph()->getPathNodes();

			if (pathNodes->size() > 0) {
				Vector3 newPos = pathNodes->get(System::random(pathNodes->size() - 1))->getPosition();
				nextPoint.setPosition(newPos.getX(), newPos.getZ(), newPos.getY());
				nextPoint.setCell(building->getCell(newCellID));
			}
		}

		return nextPoint;
	}
};


#endif /* FLEESTATECOMPONENT_H_ */
