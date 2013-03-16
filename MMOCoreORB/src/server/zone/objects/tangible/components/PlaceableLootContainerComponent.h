/*
 * PlacableLootContainerComponent.h
 *
 *  Created on: Mar 13, 2013
 *      Author: root
 */

#ifndef PLACEABLELOOTCONTAINERCOMPONENT_H_
#define PLACEABLELOOTCONTAINERCOMPONENT_H_
#include "server/zone/objects/scene/components/ContainerComponent.h"

class PlaceableLootContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);
};

#endif /* PLACEABLELOOTCONTAINERCOMPONENT_H_ */
