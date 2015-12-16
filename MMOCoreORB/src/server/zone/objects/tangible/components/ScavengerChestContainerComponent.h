#ifndef SCAVENGERCHESTCONTAINERCOMPONENT_H_
#define SCAVENGERCHESTCONTAINERCOMPONENT_H_
#include "server/zone/objects/scene/components/ContainerComponent.h"

class ScavengerChestContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
	int notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination);
};

#endif /* SCAVENGERCHESTCONTAINERCOMPONENT_H_ */
