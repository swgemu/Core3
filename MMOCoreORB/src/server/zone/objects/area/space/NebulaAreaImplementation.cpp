/*
 * NebulaAreaImplementation.cpp
 *
 * Created on: 01/05/2024
 * Author: Hakry
 */

#include "server/zone/objects/area/space/NebulaArea.h"
#include "server/zone/objects/ship/ShipObject.h"


void NebulaAreaImplementation::notifyEnter(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

	SpaceActiveAreaImplementation::notifyEnter(sceneO);

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;


}

void NebulaAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

	SpaceActiveAreaImplementation::notifyExit(sceneO);

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;


}