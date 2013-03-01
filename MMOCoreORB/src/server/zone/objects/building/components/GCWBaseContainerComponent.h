/*
 * GCWBaseContainerComponent.h
 *
 *  Created on: Dec 6, 2012
 *      Author: root
 */

#ifndef GCWBASECONTAINERCOMPONENT_H_
#define GCWBASECONTAINERCOMPONENT_H_

#include "server/zone/objects/scene/components/ContainerComponent.h"
#include "GCWBaseContainerComponent.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/components/DestructibleBuildingDataComponent.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/structure/components/StructureContainerComponent.h"
class GCWBaseContainerComponent : public StructureContainerComponent {
public:
	bool checkContainerPermission(SceneObject* sceneObject, CreatureObject* creature, uint16 permission);

	bool checkContainerPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage);

	bool checkPVPPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage);

	bool checkPVEPermission(BuildingObject* building, CreatureObject* creature, uint16 permission, bool sendMessage);

};

#endif /* GCWBASECONTAINERCOMPONENT_H_ */
