#ifndef WARRENDISKCONTAINERCOMPONENT_H_
#define WARRENDISKCONTAINERCOMPONENT_H_

/*
 * WarrenDiskContainerComponent.h
 *
 * Created: 2024-04-20
 * By: Hakry
 *
 *
*/

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"


class WarrenDiskContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* WARRENDISKCONTAINERCOMPONENT_H_ */