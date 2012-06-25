/*
 * ElevatorUpMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORUPMENUCOMPONENT_H_
#define ELEVATORUPMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class ElevatorUpMenuComponent : public TangibleObjectMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};

#endif /* ELEVATORUPMENUCOMPONENT_H_ */
