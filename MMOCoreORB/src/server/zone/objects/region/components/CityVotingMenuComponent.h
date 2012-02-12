/*
 * CityVotingMenuComponent.h
 *
 *  Created on: Feb 12, 2012
 *      Author: xyborn
 */

#ifndef CITYVOTINGMENUCOMPONENT_H_
#define CITYVOTINGMENUCOMPONENT_H_

#include "server/zone/objects/scene/components/ObjectMenuComponent.h"

class CityVotingMenuComponent : public ObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};

#endif /* CITYVOTINGMENUCOMPONENT_H_ */
