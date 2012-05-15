/*
 * FireHeavyWeaponMenuComponent.h
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#ifndef FIREHEAVYWEAPONMENUCOMPONENT_H_
#define FIREHEAVYWEAPONMENUCOMPONENT_H_

#include "TangibleObjectMenuComponent.h"
#include "engine/engine.h"

class FireHeavyWeaponMenuComponent : public TangibleObjectMenuComponent {
public:
	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID);
};

#endif /* FIREHEAVYWEAPONMENUCOMPONENT_H_ */
