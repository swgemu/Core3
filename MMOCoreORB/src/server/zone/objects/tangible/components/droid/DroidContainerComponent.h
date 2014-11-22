/*
 * DroidContainerComponent.h
 */

#ifndef DROIDCONTAINERCOMPONENT_H_
#define DROIDCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class DroidContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
	int canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription);
};

#endif /* DROIDCONTAINERCOMPONENT_H_ */
