/*
 * ElevatorDownMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORDOWNMENUCOMPONENT_H_
#define ELEVATORDOWNMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class ElevatorDownMenuComponent : public TangibleObjectMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};

#endif /* ELEVATORDOWNMENUCOMPONENT_H_ */
