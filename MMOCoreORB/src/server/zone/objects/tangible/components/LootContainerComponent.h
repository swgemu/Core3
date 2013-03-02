/*
 * LootContainerComponent.h
 *
 *  Created on: Jan 24, 2012
 *      Author: xyborn
 */

#ifndef LOOTCONTAINERCOMPONENT_H_
#define LOOTCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class LootContainerComponent: public ContainerComponent {
public:
	int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination);
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);
};

#endif /* LOOTCONTAINERCOMPONENT_H_ */
