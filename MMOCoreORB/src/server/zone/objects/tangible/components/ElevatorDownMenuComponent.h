/*
 * ElevatorDownMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORDOWNMENUCOMPONENT_H_
#define ELEVATORDOWNMENUCOMPONENT_H_

#include "ElevatorMenuComponent.h"

class ElevatorDownMenuComponent : public ElevatorMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* ELEVATORDOWNMENUCOMPONENT_H_ */
