/*
 * StructureTerminalMenuComponent.h
 *
 *  Created on: Feb 26, 2012
 *      Author: swgemu
 */

#ifndef STRUCTURETERMINALMENUCOMPONENT_H_
#define STRUCTURETERMINALMENUCOMPONENT_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class StructureTerminalMenuComponent : public ObjectMenuComponent {
public:
	void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* creature);
	int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID);
};

#endif /* STRUCTURETERMINALMENUCOMPONENT_H_ */
