/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WEAPONRANGES_H_
#define WEAPONRANGES_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

using server::zone::objects::tangible::weapon::WeaponObject;

class WeaponRanges : public ObjectControllerMessage {
public:
	WeaponRanges(CreatureObject* creo, WeaponObject* weao) : ObjectControllerMessage(creo->getObjectID(), 0x1B, 0x140) {
		insertLong(weao->getObjectID());
		insertFloat(weao->getIdealRange());
		insertFloat(weao->getMaxRange());
		insertInt(weao->getPointBlankAccuracy());
		insertInt(weao->getIdealAccuracy());
		insertInt(weao->getMaxRangeAccuracy());
	}

};

#endif /* WEAPONRANGES_H_ */
