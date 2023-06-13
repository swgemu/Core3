/*
 * PobShipContainerComponent.h
 */

#ifndef POBSHIPCONTAINERCOMPONENT_H_
#define POBSHIPCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class PobShipContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* POBSHIPCONTAINERCOMPONENT_H_ */
