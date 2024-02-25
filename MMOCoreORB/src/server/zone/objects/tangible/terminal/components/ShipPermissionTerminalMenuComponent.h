/*
 * ShipPermissionTerminalMenuComponent.h
 *
 *	Created on: June 7, 2023
 *	Author: hakry
 */

#ifndef SHIPPERMISSIONTERMINALMENUCOMPONENT_H_
#define SHIPPERMISSIONTERMINALMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class ShipPermissionTerminalMenuComponent : public ObjectMenuComponent {
public:
	void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature) const;
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const;
};

#endif /* SHIPPERMISSIONTERMINALMENUCOMPONENT_H_ */
