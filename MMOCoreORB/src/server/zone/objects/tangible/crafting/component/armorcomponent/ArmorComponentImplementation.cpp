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

#include "ArmorComponentImplementation.h"
#include "ArmorComponent.h"


ArmorComponentImplementation::ArmorComponentImplementation(uint64 objectid,
		uint32 tempCRC, const UnicodeString& n, const String& tempn) :
	ArmorComponentServant(objectid, tempCRC, n, tempn) {

	init();
}

ArmorComponentImplementation::ArmorComponentImplementation(
		CreatureObject* creature, uint32 tempCRC, const UnicodeString& n,
		const String& tempn) : ArmorComponentServant(creature, tempCRC, n, tempn) {

	init();
}
ArmorComponentImplementation::ArmorComponentImplementation(
		ArmorComponent* component, uint64 oid) : ArmorComponentServant(component, oid) {

	init();
	for(int i = 0; i < component->getSpecialResistCount(); ++i) {
	    specialResists.add(component->getSpecialResist(i));
	}
	ComponentImplementation::ComponentImplementation((Component*)component, oid);
}

ArmorComponentImplementation::~ArmorComponentImplementation() {
	attributeMap.removeAll();
	precisionMap.removeAll();
	titleMap.removeAll();
	hiddenMap.removeAll();
	keyList.removeAll();
	specialResists.removeAll();
}

void ArmorComponentImplementation::init() {

	objectSubType = ARMORCOMPONENT;

	setSpecialProtection();

	ComponentImplementation::init();
}

void ArmorComponentImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {

	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	ComponentImplementation::updateCraftingValues(draftSchematic);

	setPropertyToHidden("armor_special_effectiveness");

	String expProp = "exp_resistance";
	float specialbase = craftingValues->getCurrentValue("armor_special_effectiveness");

	for (int i = 0; i < specialResists.size(); ++i) {
		String special = specialResists.get(i);
		addProperty(special, specialbase, 10, expProp);
	}
}

void ArmorComponentImplementation::setSpecialProtection() {

	switch(objectCRC){
	case 0xC8C59EF9: // Acid Protection Layer
	case 0x6FBB3CC9: // Heavy Acid Protection Layer
		specialResists.add("acideffectiveness");
		break;
	case 0xED3461C9: // Blast Protection Layer
	case 0x7CFE57C2: // Heavy Blast Protection Layer
	case 0x67060B10: // Padded Armor Segment
	case 0xB713990E: // Advanced Padded Armor Segment
		specialResists.add("blasteffectiveness");
		break;
	case 0x42ABD9E0: // Cold Protection Layer
	case 0xE5D57BD0: // Heavy Cold Protection Layer
		specialResists.add("coldeffectiveness");
		break;
	case 0x82C7B14B: // Electrical Protection Layer
	case 0xAD666CEE: // Heavy Electrical Protection Layer
	case 0xD65EF856: // Composite Armor Segment
	case 0xA4C289AE: // Advanced Composite Armor Segment
		specialResists.add("electricaleffectiveness");
		break;
	case 0xAF2D1CB7: // Energy Protection Layer
	case 0x44C7319E: // Heavy Energy Protection Layer
	case 0x44971745: // Bone Armor Segment
	case 0xA7BBB35F: // Advanced Bone Armor Segment
	case 0x50E2DB8B: // Tantel Armor Segment
	case 0x02137816: // Advanced Tantel Armor Segment
		specialResists.add("energyeffectiveness");
		break;
	case 0xA4055A20: // Environmental Protection Layer UNUSED - No String values
	case 0x61BE0B35: // Environmental Protection Layer UNUSED - No String values
		specialResists.add("environmental_heateffectiveness");
		break;
	case 0xBA489710: // Heat Protection Layer
	case 0x1D363520: // Heavy Heat Protection Layer

		specialResists.add("heateffectiveness");
		break;
	case 0x7CE3F061: // Kinetic Protection Layer
	case 0x782C3479: // Heavy Kinetic Protection Layer
	case 0x89F45781: // Ubese Armor Segment
	case 0x3D905284: // Advanced Ubese Armor Segment
	case 0xD43CBA0E: // Chitin Armor Segment
	case 0xA77314AC: // Advanced Chitin Armor Segment
	case 0x9D67060E: // RIS Armor Segment
		specialResists.add("kineticeffectiveness");
		break;
	case 0xE6EC889F: // Lightsaber Protection Layer
	case 0x02158412: // Heavy Lightsaber Protection Layer
		specialResists.add("restraineffectiveness");
		break;
	case 0x0C182EA1: // Stun Protection Layer
	case 0xAB658C91: // Heavy Stun Protection Layer
		specialResists.add("stuneffectiveness");
		break;
	case 0x47CB53BB: // Mabari Armor Segment
	case 0x9D608A2F: // Advanced Mabari Armor Segment
		specialResists.add("heateffectiveness");
		specialResists.add("blasteffectiveness");
		break;
	case 0xD2CCC066: // Nightsister Protection Layer
	case 0xB29D37B7: // RIS Protection Layer
	case 0xD7C0FE13: // Heavy Protection Layer
		break;
	}
}

