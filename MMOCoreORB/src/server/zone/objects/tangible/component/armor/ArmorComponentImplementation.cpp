/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "ArmorComponent.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

void ArmorComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();

}

void ArmorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	if(firstUpdate) {
		setPropertyToHidden("armor_special_effectiveness");

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
