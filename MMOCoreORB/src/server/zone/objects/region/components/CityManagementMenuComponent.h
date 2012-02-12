/*
 * CityManagementMenuComponent.h
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#ifndef CITYMANAGEMENTMENUCOMPONENT_H_
#define CITYMANAGEMENTMENUCOMPONENT_H_

#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class CityManagementMenuComponent : public ObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};

#endif /* CITYMANAGEMENTMENUCOMPONENT_H_ */
