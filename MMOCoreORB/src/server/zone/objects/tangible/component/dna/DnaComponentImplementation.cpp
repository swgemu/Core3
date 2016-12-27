/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/tangible/component/dna/DnaComponent.h"

void DnaComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();
}

void DnaComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);
}

String DnaComponentImplementation::convertSpecialAttack(String &attackName) {
	// default attack and basic area attack for creatures are not valid for samples
	if (attackName == "defaultattack")
		return "@combat_effects:none";
	else if (attackName == "creatureareaattack")
		return "@combat_effects:unknown_attack";
	else if (attackName.length() > 0)
		return "@combat_effects:" + attackName;
	else
		return "@combat_effects:none";
}

String DnaComponentImplementation::resistValue(float input){
	if (input < 0) {
		return "Vulnerable";
	} else {
		StringBuffer displayvalue;
		displayvalue << Math::getPrecision(input, 10);
		return displayvalue.toString();
	}
}

void DnaComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ComponentImplementation::fillAttributeList(alm,object);
	alm->insertAttribute("dna_comp_source",source);
	switch (quality){
		case 1:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_very_high");
			break;
		case 2:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_high");
			break;
		case 3:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_above_average");
			break;
		case 4:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_average");
			break;
		case 5:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_below_average");
			break;
		case 6:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_low");
			break;
		case 7:
			alm->insertAttribute("dna_comp_quality","@obj_attr_n:dna_comp_very_low");
			break;
	}

	alm->insertAttribute("dna_comp_hardiness",hardiness);
	alm->insertAttribute("dna_comp_fortitude",fortitude);
	alm->insertAttribute("dna_comp_endurance",endurance);
	alm->insertAttribute("dna_comp_intellect",intelligence);
	alm->insertAttribute("dna_comp_cleverness",cleverness);
	alm->insertAttribute("dna_comp_dependability",dependency);
	alm->insertAttribute("dna_comp_courage",courage);
	alm->insertAttribute("dna_comp_dexterity",dexterity);
	alm->insertAttribute("dna_comp_fierceness",fierceness);
	alm->insertAttribute("dna_comp_power",power);

	if (armorRating == 0)
		alm->insertAttribute("dna_comp_armor_rating","@obj_attr_n:armor_pierce_none");
	else if (armorRating == 1)
		alm->insertAttribute("dna_comp_armor_rating","@obj_attr_n:armor_pierce_light");
	else if (armorRating == 2)
		alm->insertAttribute("dna_comp_armor_rating","@obj_attr_n:armor_pierce_medium");
	else if (armorRating == 3)
		alm->insertAttribute("dna_comp_armor_rating","@obj_attr_n:armor_pierce_none");

	// Add resists
	alm->insertAttribute("dna_comp_armor_kinetic",resistValue(kinResist));
	alm->insertAttribute("dna_comp_armor_energy",resistValue(energyResist));
	alm->insertAttribute("dna_comp_armor_blast",resistValue(blastResist));
	alm->insertAttribute("dna_comp_armor_heat",resistValue(heatResist));
	alm->insertAttribute("dna_comp_armor_cold",resistValue(coldResist));
	alm->insertAttribute("dna_comp_armor_electric",resistValue(elecResist));
	alm->insertAttribute("dna_comp_armor_acid",resistValue(acidResist));
	alm->insertAttribute("dna_comp_armor_stun",resistValue(stunResist));
	alm->insertAttribute("dna_comp_armor_saber",resistValue(saberResist));
	alm->insertAttribute("spec_atk_1",convertSpecialAttack(special1));
	alm->insertAttribute("spec_atk_2",convertSpecialAttack(special2));
	alm->insertAttribute("dna_comp_ranged_attack",ranged ? "Yes" : "No");
}

bool DnaComponentImplementation::isSpecialResist(int type) {
	return specialResists & type;
}

void DnaComponentImplementation::setSpecialResist(int type) {
	specialResists |= type;
}
