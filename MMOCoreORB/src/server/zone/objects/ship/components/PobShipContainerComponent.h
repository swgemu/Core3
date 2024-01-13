/*
 * PobShipContainerComponent.h
 */

#ifndef POBSHIPCONTAINERCOMPONENT_H_
#define POBSHIPCONTAINERCOMPONENT_H_

#include "server/zone/objects/ship/components/ShipContainerComponent.h"

class PobShipContainerComponent : public ShipContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission) const;
};

#endif /* POBSHIPCONTAINERCOMPONENT_H_ */
