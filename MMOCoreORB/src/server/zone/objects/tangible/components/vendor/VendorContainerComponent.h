/*
 * VendorContainerComponent.h
 *
 *  Created on: 08/02/2012
 *      Author: victor
 */

#ifndef VENDORCONTAINERCOMPONENT_H_
#define VENDORCONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"

class VendorContainerComponent : public ContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* VENDORCONTAINERCOMPONENT_H_ */
