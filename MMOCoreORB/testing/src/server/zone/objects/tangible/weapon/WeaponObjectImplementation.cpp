/*
 * WeaponObjectImplementation.cpp
 *
 *  Created on: 30/07/2009
 *      Author: victor
 */

#include "WeaponObject.h"
#include "server/zone/packets/tangible/WeaponObjectMessage3.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"

void WeaponObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WeaponObject");
}

void WeaponObjectImplementation::loadTemplateData(LuaObject* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	certified = false;

	attackType = templateData->getIntField("attackType");
	weaponEffect =  templateData->getStringField("weaponEffect");
	weaponEffectIndex = templateData->getIntField("weaponEffectIndex");

	LuaObject certifications = templateData->getObjectField("certificationsRequired");

	for (int i = 1; i <= certifications.getTableSize(); ++i) {
		certificationsRequired.add(certifications.getStringAt(i));
	}

	certifications.pop();
}

void WeaponObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending weapon object baselines");

	BaseMessage* weao3 = new WeaponObjectMessage3(_this);
	player->sendMessage(weao3);
}

void WeaponObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	bool res = isCertifiedFor(object);

	if (res) {
		alm->insertAttribute("weapon_cert_status", "Yes");
	} else {
		alm->insertAttribute("weapon_cert_status", "No");
	}
}

bool WeaponObjectImplementation::isCertifiedFor(PlayerCreature* object) {
	PlayerObject* ghost = object->getPlayerObject();

	for (int i = 0; i < certificationsRequired.size(); ++i) {
		String cert = certificationsRequired.get(i);

		if (!ghost->hasSkill(cert)) {
			return false;
		}
	}

	return true;
}
