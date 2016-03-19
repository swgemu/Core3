/*
 * ElevatorMenuComponent.h
 *
 *  Created on: 06/24/2012
 *      Author: swgemu
 */

#ifndef ELEVATORMENUCOMPONENT_H_
#define ELEVATORMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class ElevatorMenuComponent : public TangibleObjectMenuComponent {
protected:
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* ELEVATORMENUCOMPONENT_H_ */
