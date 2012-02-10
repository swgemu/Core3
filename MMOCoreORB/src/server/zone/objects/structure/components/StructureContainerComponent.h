/*
 * StructureContainerComponent.h
 *
 *  Created on: 09/02/2012
 *      Author: victor
 */

#ifndef STRUCTURECONTAINERCOMPONENT_H_
#define STRUCTURECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class StructureContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);
};

#endif /* STRUCTURECONTAINERCOMPONENT_H_ */
