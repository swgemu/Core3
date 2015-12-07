#ifndef SCAVENGERCHESTCONTAINERCOMPONENT_H_
#define SCAVENGERCHESTCONTAINERCOMPONENT_H_
#include "server/zone/objects/scene/components/ContainerComponent.h"

class ScavengerChestContainerComponent: public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
};

#endif /* SCAVENGERCHESTCONTAINERCOMPONENT_H_ */
