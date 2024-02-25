/*
 * PobShipObjectMenuComponent.cpp
 *
 * Created on: 1/16/2024
 * Author: Hakry
 */

#include "PobShipObjectMenuComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

void PobShipObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	if (!sceneObject->isTangibleObject())
		return;

	auto objectRoot = sceneObject->getRootParent();

	if (objectRoot == nullptr)
		return;

	if (objectRoot->containsChildObject(sceneObject))
		return;

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int PobShipObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
}
