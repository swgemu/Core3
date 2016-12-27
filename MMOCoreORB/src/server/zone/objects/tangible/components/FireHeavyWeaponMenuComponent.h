/*
 * FireHeavyWeaponMenuComponent.h
 *
 *  Created on: May 10, 2012
 *      Author: chris.rush
 */

#ifndef FIREHEAVYWEAPONMENUCOMPONENT_H_
#define FIREHEAVYWEAPONMENUCOMPONENT_H_

#include "WeaponObjectMenuComponent.h"

class FireHeavyWeaponMenuComponent : public WeaponObjectMenuComponent {
public:
	virtual void fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const;

	virtual int handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const;
};

#endif /* FIREHEAVYWEAPONMENUCOMPONENT_H_ */
