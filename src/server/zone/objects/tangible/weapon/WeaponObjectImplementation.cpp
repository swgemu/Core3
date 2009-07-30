/*
 * WeaponObjectImplementation.cpp
 *
 *  Created on: 30/07/2009
 *      Author: victor
 */

#include "WeaponObject.h"
#include "server/zone/packets/tangible/WeaponObjectMessage3.h"

WeaponObjectImplementation::WeaponObjectImplementation(LuaObject* templateData) :
	TangibleObjectImplementation(templateData) {

	setLoggingName("WeaponObject");

	attackType = templateData->getIntField("attackType");
	weaponEffect =  templateData->getStringField("weaponEffect");
	weaponEffectIndex = templateData->getIntField("weaponEffectIndex");
}

void WeaponObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending weapon object baselines");

	BaseMessage* weao3 = new WeaponObjectMessage3(_this);
	player->sendMessage(weao3);
}
