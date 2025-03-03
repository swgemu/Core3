#ifndef DROIDCOMMANDCONTAINERCOMPONENT_H_
#define DROIDCOMMANDCONTAINERCOMPONENT_H_

/*
 * DroidCommandContainerComponent.h
 *
 * Created: 2025-03-04
 * By: Hakry
 *
 *
*/

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"

class DroidCommandContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* DROIDCOMMANDCONTAINERCOMPONENT_H_ */