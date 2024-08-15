/*
 * SpaceActiveAreaImplementation.cpp
 *
 * Created on: 01/05/2024
 * Author: Hakry
 */

#include "server/zone/objects/area/space/SpaceActiveArea.h"
#include "server/zone/objects/ship/ShipObject.h"

// #define DEBUG_SPACE_AREAS

void SpaceActiveAreaImplementation::notifyEnter(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;

#ifdef DEBUG_SPACE_AREAS
	StringBuffer msg;
	msg << "notifyEnter - SpaceActiveArea: " << getAreaName() << " Location: " << getAreaCenter().toString();
	shipObject->sendShipMembersMessage(msg.toString());
#endif

	ActiveAreaImplementation::notifyEnter(sceneO);
}

void SpaceActiveAreaImplementation::notifyExit(SceneObject* sceneO) {
	if (sceneO == nullptr || !sceneO->isShipObject())
		return;

	auto shipObject = sceneO->asShipObject();

	if (shipObject == nullptr)
		return;

#ifdef DEBUG_SPACE_AREAS
	StringBuffer msg;
	msg << "notifyExit - SpaceActiveArea: " << getAreaName() << " Location: " << getAreaCenter().toString();
	shipObject->sendShipMembersMessage(msg.toString());
#endif

	ActiveAreaImplementation::notifyExit(sceneO);
}