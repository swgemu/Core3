#ifndef SCAVENGERCHESTCONTAINERCOMPONENT_H_
#define SCAVENGERCHESTCONTAINERCOMPONENT_H_
#include "server/zone/objects/scene/components/ContainerComponent.h"

class ScavengerChestContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* container, CreatureObject* creature, uint16 permission) const;
	int notifyObjectRemoved(SceneObject* container, SceneObject*, SceneObject* destination) const;
};

#endif /* SCAVENGERCHESTCONTAINERCOMPONENT_H_ */
