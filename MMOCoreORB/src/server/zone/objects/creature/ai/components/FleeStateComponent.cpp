/*
 * FleeStateComponent.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: da
 */

#include "FleeStateComponent.h"
#include "../AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/templates/appearance/PathGraph.h"
#include "server/zone/templates/appearance/PathNode.h"
#include "server/zone/Zone.h"

uint16 FleeStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	SceneObject* target = actor->getFollowObject();
	if (target == NULL)
		target = host->getThreatMap()->getHighestThreatCreature();

	if (target == NULL)
		return AiActor::FORGOT;

	host->showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);

	actor->setDefender(target);

	actor->activateMovementEvent();
	actor->activateRecovery();

	return AiActor::UNFINISHED;
}

uint16 FleeStateComponent::doRecovery(AiActor* actor) {
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

uint16 FleeStateComponent::doMovement(AiActor* actor) {
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

	WorldCoordinates nextPosition;
	if (findNextPosition(actor, getMaxDistance(host), getSpeed(host), actor->getPatrolPoints(), &nextPosition))
		actor->setNextStepPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY(), nextPosition.getCell());
	else
		actor->setNextStepPosition(host->getPositionX(), host->getPositionZ(), host->getPositionY(), host->getParent().get());

	return AiStateComponent::doMovement(actor);
}

float FleeStateComponent::getSpeed(CreatureObject* host) {
	return host->getRunSpeed();
}

PatrolPoint FleeStateComponent::getFleeLocation(CreatureObject* host, SceneObject* followObject) {
	Vector3 agressorVector = 2 * host->getWorldPosition() - followObject->getWorldPosition();
	PatrolPoint nextPoint = PatrolPoint(0, 0, 0, NULL);

	ManagedReference<SceneObject*> parent = host->getParent();
	if (parent != NULL && parent->isCellObject()) {
		CellObject* ourCell = cast<CellObject*>(parent.get());
		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(ourCell->getParent().get().get());
		int ourCellID = ourCell->getCellNumber();
		SharedObjectTemplate* templateObject = ourCell->getParent().get()->getObjectTemplate();

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
	} else {
		Zone* zone = host->getZone();
		if (zone == NULL)
			return nextPoint;

		agressorVector.normalize();
		agressorVector = agressorVector * 256;

		if (agressorVector.getX() > zone->getMaxX() || agressorVector.getX() < zone->getMinX())
			agressorVector.setX(0);

		if (agressorVector.getY() > zone->getMaxY() || agressorVector.getY() < zone->getMinY())
			agressorVector.setY(0);

		nextPoint = PatrolPoint(agressorVector.getX(), 0, agressorVector.getY(), NULL);
		nextPoint.setPositionZ(host->getZone()->getHeight(nextPoint.getPositionX(), nextPoint.getPositionY()));
	}

	return nextPoint;
}


