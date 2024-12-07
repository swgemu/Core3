#include "server/zone/objects/ship/components/ShipMissileComponent.h"

void ShipMissileComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("@obj_attr_n:volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	alm->insertAttribute("@obj_attr_n:wpn_comp_damage_min", String::valueOf(Math::getPrecision(minDamage, 5)));
	alm->insertAttribute("@obj_attr_n:wpn_comp_damage_max", String::valueOf(Math::getPrecision(maxDamage, 5)));
	alm->insertAttribute("@obj_attr_n:refire_rate", String::valueOf(Math::getPrecision(refireRate, 7)));
	alm->insertAttribute("@obj_attr_n:effective_shields", String::valueOf(Math::getPrecision(missileShieldEffectiveness, 5)));
	alm->insertAttribute("@obj_attr_n:effective_armor", String::valueOf(Math::getPrecision(missileArmorEffectiveness, 5)));
	alm->insertAttribute("@obj_attr_n:ammo", String::valueOf(Math::getPrecision(ammunition, 0)));
	
}