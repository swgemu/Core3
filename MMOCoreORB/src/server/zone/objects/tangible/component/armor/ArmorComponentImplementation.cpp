/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/component/armor/ArmorComponent.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

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

	if(specialResists != CraftingValues::VALUENOTFOUND) {
		if (specialResists & WeaponObject::KINETIC)
			addProperty("kineticeffectiveness", specialbase + kinetic, 10, expProp);
		if (specialResists & WeaponObject::ENERGY)
			addProperty("energyeffectiveness", specialbase + energy, 10, expProp);
		if (specialResists & WeaponObject::BLAST)
			addProperty("blasteffectiveness", specialbase + blast, 10, expProp);
		if (specialResists & WeaponObject::STUN)
			addProperty("stuneffectiveness", specialbase + stun, 10, expProp);
		if (specialResists & WeaponObject::LIGHTSABER)
			addProperty("restraineffectiveness", specialbase + lightSaber, 10, expProp);
		if (specialResists & WeaponObject::HEAT)
			addProperty("heateffectiveness", specialbase + heat, 10, expProp);
		if (specialResists & WeaponObject::COLD)
			addProperty("coldeffectiveness", specialbase + cold, 10, expProp);
		if (specialResists & WeaponObject::ACID)
			addProperty("acideffectiveness", specialbase + acid, 10, expProp);
		if (specialResists & WeaponObject::ELECTRICITY)
			addProperty("electricaleffectiveness", specialbase + electricity, 10, expProp);
	}
}

void ArmorComponentImplementation::calculateSpecialProtection(CraftingValues* craftingValues) {

	for (int i = 0; i <= 8; ++i) {

		int type = pow((float)2,i);

		String subtitle = getStringType(type);
		float value = craftingValues->getCurrentValue(subtitle);

		if(value != CraftingValues::VALUENOTFOUND) {

			setProtectionValue(type, value);
		}
	}
}

String ArmorComponentImplementation::getStringType(int type) {

	switch(type) {
	case WeaponObject::KINETIC:
		return "kineticeffectiveness";
		break;
	case WeaponObject::ENERGY:
		return "energyeffectiveness";
	break;
	case WeaponObject::ELECTRICITY:
		return "electricaleffectiveness";
		break;
	case WeaponObject::STUN:
		return "stuneffectiveness";
		break;
	case WeaponObject::BLAST:
		return "blasteffectiveness";
		break;
	case WeaponObject::HEAT:
		return "heateffectiveness";
		break;
	case WeaponObject::COLD:
		return "coldeffectiveness";
		break;
	case WeaponObject::ACID:
		return "acideffectiveness";
		break;
	case WeaponObject::LIGHTSABER:
		return "restraineffectiveness";
		break;
	default:
		return "";
	}
}

void ArmorComponentImplementation::setProtectionValue(int type, float value) {

	if (type & WeaponObject::KINETIC)
		setKinetic(value);
	if (type & WeaponObject::ENERGY)
		setEnergy(value);
	if (type & WeaponObject::BLAST)
		setBlast(value);
	if (type & WeaponObject::STUN)
		setStun(value);
	if (type & WeaponObject::LIGHTSABER)
		setLightSaber(value);
	if (type & WeaponObject::HEAT)
		setHeat(value);
	if (type & WeaponObject::COLD)
		setCold(value);
	if (type & WeaponObject::ACID)
		setAcid(value);
	if (type & WeaponObject::ELECTRICITY)
		setElectricity(value);
}
