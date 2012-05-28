/*
 * ThrowGrenadeMenuComponent.h
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#ifndef THROWGRENADEMENUCOMPONENT_H_
#define THROWGRENADEMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"

class ThrowGrenadeMenuComponent : public TangibleObjectMenuComponent {
public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};


#endif /* THROWGRENADEMENUCOMPONENT_H_ */
