/*
 * ThrowGrenadeMenuComponent.h
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#ifndef THROWGRENADEMENUCOMPONENT_H_
#define THROWGRENADEMENUCOMPONENT_H_

#include "WeaponObjectMenuComponent.h"

class ThrowGrenadeMenuComponent : public WeaponObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player);

	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};


#endif /* THROWGRENADEMENUCOMPONENT_H_ */
