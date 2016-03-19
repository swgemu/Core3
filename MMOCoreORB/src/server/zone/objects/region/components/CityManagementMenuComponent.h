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
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* CITYMANAGEMENTMENUCOMPONENT_H_ */
