/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/component/armor/ArmorComponent.h"
#include "templates/tangible/SharedWeaponObjectTemplate.h"

void ArmorComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();

}

void ArmorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	if(firstUpdate) {
		setPropertyToHidden("armor_special_effectiveness");
		setPropertyToHidden("armor_special_type");

		kinetic = 0;
		energy = 0;
		electricity = 0;
		stun = 0;
		blast = 0;
		heat = 0;
		cold = 0;
		acid = 0;
		lightSaber = 0;

		calculateSpecialProtection(values);
	}

	String expProp = "exp_resistance";
	float specialbase = values->getCurrentValue("armor_special_effectiveness");
	int specialResists = values->getCurrentValue("armor_special_type");

	if (specialResists != ValuesMap::VALUENOTFOUND) {
		if (specialResists & SharedWeaponObjectTemplate::KINETIC)
			addProperty("kineticeffectiveness", specialbase + kinetic, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::ENERGY)
			addProperty("energyeffectiveness", specialbase + energy, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::BLAST)
			addProperty("blasteffectiveness", specialbase + blast, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::STUN)
			addProperty("stuneffectiveness", specialbase + stun, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::LIGHTSABER)
			addProperty("restraineffectiveness", specialbase + lightSaber, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::HEAT)
			addProperty("heateffectiveness", specialbase + heat, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::COLD)
			addProperty("coldeffectiveness", specialbase + cold, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::ACID)
			addProperty("acideffectiveness", specialbase + acid, 10, expProp);
		if (specialResists & SharedWeaponObjectTemplate::ELECTRICITY)
			addProperty("electricaleffectiveness", specialbase + electricity, 10, expProp);
	}
}

void ArmorComponentImplementation::calculateSpecialProtection(CraftingValues* craftingValues) {

	for (int i = 0; i <= 8; ++i) {
		int type = pow((float)2, i);

		String subtitle = getStringType(type);
		float value = craftingValues->getCurrentValue(subtitle);

		if (value != ValuesMap::VALUENOTFOUND) {
			setProtectionValue(type, value);
		}
	}
}

String ArmorComponentImplementation::getStringType(int type) {

	switch(type) {
	case SharedWeaponObjectTemplate::KINETIC:
		return "kineticeffectiveness";
		break;
	case SharedWeaponObjectTemplate::ENERGY:
		return "energyeffectiveness";
	break;
	case SharedWeaponObjectTemplate::ELECTRICITY:
		return "electricaleffectiveness";
		break;
	case SharedWeaponObjectTemplate::STUN:
		return "stuneffectiveness";
		break;
	case SharedWeaponObjectTemplate::BLAST:
		return "blasteffectiveness";
		break;
	case SharedWeaponObjectTemplate::HEAT:
		return "heateffectiveness";
		break;
	case SharedWeaponObjectTemplate::COLD:
		return "coldeffectiveness";
		break;
	case SharedWeaponObjectTemplate::ACID:
		return "acideffectiveness";
		break;
	case SharedWeaponObjectTemplate::LIGHTSABER:
		return "restraineffectiveness";
		break;
	default:
		return "";
	}
}

void ArmorComponentImplementation::setProtectionValue(int type, float value) {

	if (type & SharedWeaponObjectTemplate::KINETIC)
		setKinetic(value);
	if (type & SharedWeaponObjectTemplate::ENERGY)
		setEnergy(value);
	if (type & SharedWeaponObjectTemplate::BLAST)
		setBlast(value);
	if (type & SharedWeaponObjectTemplate::STUN)
		setStun(value);
	if (type & SharedWeaponObjectTemplate::LIGHTSABER)
		setLightSaber(value);
	if (type & SharedWeaponObjectTemplate::HEAT)
		setHeat(value);
	if (type & SharedWeaponObjectTemplate::COLD)
		setCold(value);
	if (type & SharedWeaponObjectTemplate::ACID)
		setAcid(value);
	if (type & SharedWeaponObjectTemplate::ELECTRICITY)
		setElectricity(value);
}
