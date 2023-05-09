/*
 * GeneticLabratory.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: swgemu
 */

#include "GeneticLabratory.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "Genetics.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/managers/crafting/CraftingManager.h"

//#define DEBUG_GENETIC_LAB

GeneticLabratory::GeneticLabratory() {
	setLoggingName("GeneticLaboratory");
}

GeneticLabratory::~GeneticLabratory() {
}

void GeneticLabratory::initialize(ZoneServer* server) {
	SharedLabratory::initialize(server);
}

String GeneticLabratory::pickSpecialAttack(String a, String b, String c, String d, String e, int odds, String otherSpecial) {
	String effectiveSpecial = "defaultattack";
	// if no special was found in the first passed in slot pick one at random
	if (a.isEmpty() || a == otherSpecial) {
		int rand = System::random(3);
		switch(rand) {
			case 0:
				effectiveSpecial = b;
				break;
			case 1:
				effectiveSpecial = c;
				break;
			case 2:
				effectiveSpecial = d;
				break;
			case 3:
				effectiveSpecial = e;
				break;
			default:
				effectiveSpecial = "defaultattack";
				break;
		}
	} else {
		effectiveSpecial = a;
	}
	if (effectiveSpecial.contains("creature"))
		effectiveSpecial = "defaultattack";
	int roll = System::random(750);
	// roll now determined by template quality
	// we roll 0-800 if that number is < quality * 100 i.e. VHQ 100 VLQ 700 if we get less than the odds we dont stick the special
	// VLQ has a 7% chance to stick a special VHQ has 87% chance to stick it
	if (roll < odds ) {
		effectiveSpecial = "defaultattack";
	}
	if (effectiveSpecial == otherSpecial && effectiveSpecial != "defaultattack")
		effectiveSpecial = pickSpecialAttack(effectiveSpecial,b,c,d,e,odds+100,otherSpecial);// pick another default mantis #5598 max loop count is 8 (i.e. odds starting at 100, at 8 calls it picks defaultattack
	return effectiveSpecial;
}

void GeneticLabratory::recalculateResist(CraftingValues* craftingValues) {
	if (craftingValues == nullptr)
		return;

	float percentage = 0.f, min = 0.f, max = 0.f, newValue = 0.f, oldValue = 0.f;
	bool hidden = false;
	int totalAttributes = craftingValues->getTotalExperimentalAttributes();

#ifdef DEBUG_GENETIC_LAB
	info(true) << "---------- recalculateResist ----------";

	info(true) << "Total Experimental Attributes = " << totalAttributes;
#endif

	for (int i = 0; i < totalAttributes; ++i) {
		String attribute = craftingValues->getAttribute(i);
		String group = craftingValues->getAttributeGroup(attribute);

		min = craftingValues->getMinValue(attribute);
		max = craftingValues->getMaxValue(attribute);

		hidden = craftingValues->isHidden(attribute);

		percentage = craftingValues->getCurrentPercentage(attribute);
		oldValue = craftingValues->getCurrentValue(attribute);

		if (max != min) {
			if (max > min)
				newValue = (percentage * (max - min)) + min;
			else
				newValue = (float(1.0f - percentage) * (min - max)) + max;
		} else if(max == min) {
			newValue = max;
		}

		if (hidden && group == "resists") {
			craftingValues->setCurrentValue(attribute, newValue);
		}

#ifdef DEBUG_GENETIC_LAB
		info(true) << "Attribute: " << attribute << " Experimental Group: " << group << " Min: " << min << " Max: " << max << " Percentage: " << percentage << " Old Value: " << oldValue << " New Value: " << newValue;
#endif
	}

#ifdef DEBUG_GENETIC_LAB
	info(true) << "---------- END recalculateResist ----------";
#endif
}

void GeneticLabratory::setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess) {
	if (prototype == nullptr || manufactureSchematic == nullptr)
		return;

	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	if (draftSchematic == nullptr)
		return;

#ifdef DEBUG_GENETIC_LAB
	info(true) << "---------- setInitialCraftingValues ----------";
#endif
	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();

	if (craftingValues == nullptr)
		return;

	// These 2 values are pretty standard, adding these
	float value = float(draftSchematic->getXpAmount());
	craftingValues->addExperimentalAttribute("xp", "", value, value, 0, true, AttributesMap::OVERRIDECOMBINE);

	value = manufactureSchematic->getComplexity();
	craftingValues->addExperimentalAttribute("complexity", "", value, value, 0, true, AttributesMap::OVERRIDECOMBINE);

	float modifier = calculateAssemblyValueModifier(assemblySuccess);

	// Cast component to genetic component
	if (prototype->getGameObjectType() != SceneObjectType::GENETICCOMPONENT)
		return;

	GeneticComponent* genetic = cast<GeneticComponent*>(prototype);

	if (genetic == nullptr)
		return;

#ifdef DEBUG_GENETIC_LAB
	info(true) << "Genetic Manufacturing Schematic Slot Count = " << manufactureSchematic->getSlotCount();
#endif

	// Get all of the DNA Components by their slot
	ManagedReference<DnaComponent*> physique = nullptr;
	ManagedReference<DnaComponent*> prowess = nullptr;
	ManagedReference<DnaComponent*> mental = nullptr;
	ManagedReference<DnaComponent*> psychological = nullptr;
	ManagedReference<DnaComponent*> aggression = nullptr;

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {
		// Dna Component Slots
		Reference<IngredientSlot* > ingredientSlot = manufactureSchematic->getSlot(i);

		if (ingredientSlot == nullptr || !ingredientSlot->isComponentSlot())
			continue;

		ComponentSlot* componentSlot = ingredientSlot.castTo<ComponentSlot*>();

		if (componentSlot == nullptr)
			continue;

		ManagedReference<TangibleObject*> tano = componentSlot->getPrototype();

		if (tano == nullptr || (tano->getGameObjectType() != SceneObjectType::DNACOMPONENT))
			continue;

		ManagedReference<DnaComponent*> component = tano.castTo<DnaComponent*>();

		if (component == nullptr)
			continue;

		String slotName = componentSlot->getSlotName();

#ifdef DEBUG_GENETIC_LAB
		info(true) << "Retrieving Component from slot: " << componentSlot->getSlotName();
#endif

		if (slotName == "physique_profile") {
			physique = component.get();
		} else if (slotName == "prowess_profile") {
			prowess = component.get();
		} else if (slotName == "mental_profile") {
			mental = component.get();
		} else if (slotName == "psychological_profile") {
			psychological = component.get();
		} else if (slotName == "aggression_profile") {
			aggression = component.get();
		}
	}

	// Ensure none of the components don't have a nullptr
	if (physique == nullptr || prowess == nullptr || mental == nullptr || psychological == nullptr || aggression == nullptr)
		return;

	/*

	 1. Calculate the Attribute Max Values

	*/

	// Physique: Fortitude and Hardiness
	float fortitudeMax = Genetics::physiqueFormula(physique->getForititude(), prowess->getForititude(), mental->getForititude(), psychological->getForititude(), aggression->getForititude()) * modifier;
	float hardinessMax = Genetics::physiqueFormula(physique->getHardiness(), prowess->getHardiness(), mental->getHardiness(), psychological->getHardiness(), aggression->getHardiness()) * modifier;

	// Prowess: Endurance and Dexterity
	float dexterityMax = Genetics::prowessFormula(physique->getDexterity(), prowess->getDexterity(), mental->getDexterity(), psychological->getDexterity(), aggression->getDexterity()) * modifier;
	float enduranceMax = Genetics::prowessFormula(physique->getEndurance(), prowess->getEndurance(), mental->getEndurance(), psychological->getEndurance(), aggression->getEndurance()) * modifier;

	// Mental: Intellect and Cleverness
	float intellectMax = Genetics::mentalFormula(physique->getIntellect(), prowess->getIntellect(), mental->getIntellect(), psychological->getIntellect(), aggression->getIntellect()) * modifier;
	float clevernessMax = Genetics::mentalFormula(physique->getCleverness(), prowess->getCleverness(), mental->getCleverness(), psychological->getCleverness(), aggression->getCleverness()) * modifier;

	// Physiological: Dependability and Coursage
	float dependabilityMax = Genetics::physchologicalFormula(physique->getDependency(), prowess->getDependency(), mental->getDependency(), psychological->getDependency(), aggression->getDependency()) * modifier;
	float courageMax = Genetics::physchologicalFormula(physique->getCourage(), prowess->getCourage(), mental->getCourage(), psychological->getCourage(), aggression->getCourage()) * modifier;

	// Aggression: Ferocity and Power
	float fiercenessMax = Genetics::aggressionFormula(physique->getFierceness(), prowess->getFierceness(), mental->getFierceness(), psychological->getFierceness(), aggression->getFierceness()) * modifier;
	float powerMax = Genetics::aggressionFormula(physique->getPower(), prowess->getPower(), mental->getPower(), psychological->getPower(), aggression->getPower()) * modifier;

#ifdef DEBUG_GENETIC_LAB
	info(true) << "===== Calculate Attribute Max Values =====";

	info(true) << "PHYSIQUE -- Fortitude Max: " << fortitudeMax << " Hardiness Max: " << hardinessMax;
	info(true) << "PROWESS -- Dexterity Max: " << dexterityMax << " Endurance Max: " << enduranceMax;
	info(true) << "MENTAL -- Intellect Max: " << intellectMax << " Cleverness Max: " << clevernessMax;
	info(true) << "PHYSIOLOGICAL -- Dependability Max: " << dependabilityMax << " Courage Max: " << courageMax;
	info(true) << "AGGRESSION -- Fierceness Max: " << fiercenessMax << " Power Max: " << powerMax;

	info(true) << "===== END Calculate Attribute Max Values =====";
#endif

	// Add Attribute Max Values. These will be updated based on the assembly modifier
	craftingValues->addExperimentalAttribute("fortitude", "expPhysiqueProfile", 0.0f, fortitudeMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("hardiness", "expPhysiqueProfile", 0.0f, hardinessMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("dexterity", "expProwessProfile", 0.0f, dexterityMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("endurance", "expProwessProfile",  0.0f, enduranceMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("intellect", "expMentalProfile", 0.0f, intellectMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("cleverness", "expMentalProfile", 0.0f, clevernessMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("dependability", "expPsychologicalProfile", 0.0f, dependabilityMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("courage", "expPsychologicalProfile", 0.0f, courageMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("fierceness", "expAggressionProfile", 0.0f, fiercenessMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("power", "expAggressionProfile", 0.0f, powerMax, 0, false, AttributesMap::LINEARCOMBINE);

	/*

	 3. Update attribute initial values and percentages

	*/

#ifdef DEBUG_GENETIC_LAB
	info(true) << "Total Crafting Values: " << craftingValues->getTotalExperimentalAttributes();
#endif

	float currentPercentage = 0.0f, maxPercentage = 0.0f, maxValue = 0.0f, initialValue = 0.0f, rangeValue = 0.0f, fortitude = 0.0f;
	bool hidden = false;

	for (int i = 0; i < craftingValues->getTotalExperimentalAttributes(); i++) {
		String attribute = craftingValues->getAttribute(i);
		String group = craftingValues->getAttributeGroup(attribute);

#ifdef DEBUG_GENETIC_LAB
		info(true) << " ==== Updating Attribute: " << attribute << " ====";
#endif
		if (craftingValues->isHidden(attribute))
			continue;

		maxValue = craftingValues->getMaxValue(attribute);
		initialValue = Genetics::initialValue(maxValue);

		// Set Current and Max Values
		craftingValues->setCurrentValue(attribute, initialValue);
		craftingValues->setMaxValue(attribute, 1000.0f);

		// Set Max and Current Percentages
		maxPercentage = (maxValue / 1000);
		currentPercentage = ceil(initialValue) / 1000;

		craftingValues->setCurrentPercentage(attribute, (maxPercentage - currentPercentage), maxPercentage);

		craftingValues->addValueToSend(attribute);

#ifdef DEBUG_GENETIC_LAB
		info(true) << "Current Percentage: " << currentPercentage << " Max Percentage: " << maxPercentage;
		info(true) << "Setting Attribute Value: " << initialValue << " with Max Value: " << maxValue <<  " Group: " << group;
#endif

		if (attribute == "fortitude" && initialValue >= 500.f) {
			fortitude = initialValue;

#ifdef DEBUG_GENETIC_LAB
			info(true) << "Fortitude is over 500: " << fortitude;
#endif
		}
#ifdef DEBUG_GENETIC_LAB
		info(true) << " ==== End Updating Attribute: " << attribute << " ====";
#endif
	}

	/*

		4. Calculate and Add Resistance Values

	*/

	// Check for Special Protections. They will not be overwritten by fortitude breaking 500.
	bool blastSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::BLAST);
	bool kineticSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::KINETIC);
	bool energySpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ENERGY);
	bool heatSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::HEAT);
	bool coldSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::COLD);
	bool electricSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ELECTRICITY);
	bool acidSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ACID);
	bool stunSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::STUN);
	//bool lightsaberSpecial = Genetics::hasSpecialResist(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::LIGHTSABER);

#ifdef DEBUG_GENETIC_LAB
	info(true) << "===== Special Protections =====";

	info(true) << "Blast Special Protection: " << (blastSpecial ? "True" : "False");
	info(true) << "Kinetic Special Protection: " << (kineticSpecial ? "True" : "False");
	info(true) << "Energy Special Protection: " << (energySpecial ? "True" : "False");
	info(true) << "Heat Special Protection: " << (heatSpecial ? "True" : "False");
	info(true) << "Cold Special Protection: " << (coldSpecial ? "True" : "False");
	info(true) << "Electric Special Protection: " << (electricSpecial ? "True" : "False");
	info(true) << "Acid Special Protection: " << (acidSpecial ? "True" : "False");
	info(true) << "Stun Special Protection: " << (stunSpecial ? "True" : "False");
	//info(true) << "Lightsaber Special Protection: " << (lightsaberSpecial ? "True" : "False");

	info(true) << "===== END Special Protections =====";
#endif

	bool armorReset = (fortitude > 500.f);
	float blast = 0.f, kinetic = 0.f, energy = 0.f, heat = 0.f, cold = 0.f, electric = 0.f, acid = 0.f, stun = 0.f;

	// Calculate Resistances
	if ((blastSpecial && !armorReset) || !armorReset)
		blast = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::BLAST, Genetics::BLAST_MAX);

	if ((kineticSpecial && !armorReset) || !armorReset)
		kinetic = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::KINETIC, Genetics::KINETIC_MAX);

	if ((energySpecial && !armorReset) || !armorReset)
		energy = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ENERGY, Genetics::ENERGY_MAX);

	if ((heatSpecial && !armorReset) || !armorReset)
		heat = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::HEAT, Genetics::HEAT_MAX);

	if ((coldSpecial && !armorReset) || !armorReset)
		cold = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::COLD, Genetics::COLD_MAX);

	if ((electricSpecial && !armorReset) || !armorReset)
		electric = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ELECTRICITY, Genetics::ELECTRICITY_MAX);

	if ((acidSpecial && !armorReset) || !armorReset)
		acid = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::ACID, Genetics::ACID_MAX);

	if ((stunSpecial && !armorReset) || !armorReset)
		stun = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::STUN, Genetics::STUN_MAX);

	//if ((lightsaberSpecial && !armorReset) || !armorReset)
		//lightsaber = Genetics::resistanceFormula(physique, prowess, mental, psychological, aggression, SharedWeaponObjectTemplate::LIGHTSABER, Genetics::LIGHTSABER_MAX);

#ifdef DEBUG_GENETIC_LAB
	info(true) << "===== Calculate Resistances =====";

	info(true) << "Blast Resistance: " << blast;
	info(true) << "Kinetic Resistance: " << kinetic;
	info(true) << "Energy Resistance: " << energy;
	info(true) << "Heat Resistance: " << heat;
	info(true) << "Cold Resistance: " << cold;
	info(true) << "Electric Resistance: " << electric;
	info(true) << "Acid Resistance: " << acid;
	info(true) << "Stun Resistance: " << stun;
	//info(true) << "Lightsaber Resistance: " << lightsaber;

	info(true) << "===== END Calculate Resistances =====";
#endif

	// Add Resistance Values
	craftingValues->addExperimentalAttribute("dna_comp_armor_kinetic", "resists", -99.f, Genetics::KINETIC_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_kinetic", kinetic);

	craftingValues->addExperimentalAttribute("dna_comp_armor_blast", "resists", -99.f, Genetics::BLAST_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_blast", blast);

	craftingValues->addExperimentalAttribute("dna_comp_armor_energy", "resists", -99.f, Genetics::ENERGY_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_energy", energy);

	craftingValues->addExperimentalAttribute("dna_comp_armor_heat", "resists", -99.f, Genetics::HEAT_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_heat", heat);

	craftingValues->addExperimentalAttribute("dna_comp_armor_cold", "resists", -99.f, Genetics::COLD_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_cold", cold);

	craftingValues->addExperimentalAttribute("dna_comp_armor_electric", "resists", -99.f, Genetics::ELECTRICITY_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_electric", electric);

	craftingValues->addExperimentalAttribute("dna_comp_armor_acid", "resists", -99.f, Genetics::ACID_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_acid", acid);

	craftingValues->addExperimentalAttribute("dna_comp_armor_stun", "resists", -99.f, Genetics::STUN_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->setCurrentValue("dna_comp_armor_stun", stun);

	//craftingValues->addExperimentalAttribute("dna_comp_armor_saber", "resists", -99.f, Genetics::LIGHTSABER_MAX, 0, true, AttributesMap::OVERRIDECOMBINE);
	//craftingValues->setCurrentValue("dna_comp_armor_saber", lightsaber);

	// Store Special Resistances
	craftingValues->addExperimentalAttribute("kineticeffectiveness", "specials", kineticSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("blasteffectiveness", "specials", blastSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("energyeffectiveness", "specials", energySpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("heateffectiveness", "specials", heatSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("coldeffectiveness", "specials", coldSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("electricityeffectiveness", "specials", electricSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("acideffectiveness", "specials", acidSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("stuneffectiveness", "specials", stunSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	//craftingValues->addExperimentalAttribute("lightsabereffectiveness", "specials", lightsaberSpecial ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);

	/*

		5. Determine Quality, Ranged, Special Attacks and Level

	*/

	// Determine Quality
	float quality = (physique->getQuality() * 0.2f) + (prowess->getQuality() * 0.2f) + (mental->getQuality() * 0.2f) + (psychological->getQuality() * 0.2f) + (aggression->getQuality() * 0.2f);

	// Ranged Attack
	bool ranged = false;

	float menQual = mental->getQuality() - 1;
	float psyQual = psychological->getQuality() - 1;

	if (mental->isRanged() || psychological->isRanged()) {
		int chance = System::random(100 - (assemblySuccess * 10)); // so amazing success 100, critical falure is 20

		// did you roll exceed (7 - Quality) * 10 (VHQ is 0) so always works
		if (chance >= (menQual * 10) || chance >= (psyQual * 10))
			ranged = true;
	}

	// Special Attacks
	int odds = quality * 100;

	// update crafting values, and/or experimentRow should handle resist calc changes. update crafting values should determine armor setup
	String special1 = pickSpecialAttack(aggression->getSpecialAttackOne(), psychological->getSpecialAttackOne(), physique->getSpecialAttackOne(), mental->getSpecialAttackOne(), prowess->getSpecialAttackOne(), odds, "defaultattack");
	String special2 = pickSpecialAttack(psychological->getSpecialAttackTwo(), prowess->getSpecialAttackTwo(), aggression->getSpecialAttackTwo(), mental->getSpecialAttackTwo(), physique->getSpecialAttackTwo(), odds, special1);

	genetic->setSpecialAttackOne(special1);
	genetic->setSpecialAttackTwo(special2);
	genetic->setRanged(ranged);
	genetic->setQuality(quality);

	// determine avg sample levels to choose a level of this template for output generation
	int level = Genetics::physchologicalFormula(physique->getLevel(), prowess->getLevel(), mental->getLevel(), psychological->getLevel(), aggression->getLevel());
	genetic->setLevel(level);
}

int GeneticLabratory::getCreationCount(ManufactureSchematic* manufactureSchematic) {
	return 1;
}

void GeneticLabratory::experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult){
	// we can 'run super' then reset our resists accordingly as well as armor base.
	//
	// TODO:
	// Step 1. Perform normal experimentiton run
	// Step 2. Recalculate armor base, and effective resist based on armor base. (armor base is fort)
	// Step 3. Profit.
	// RULES: AMAZING + 15% (+5% if lucky), GREAT: 1% GOOD: 0.5% MODERATE: 0.25% SUCCESS: 0.15% MARGINAL: 0% OK: -0.5% BARELY: -1% CRITICAL FAILURE: -1% + random state reduced by 10%
	// use normal line mechanics, just add the extra in.

	float modifier = 0, newValue = 0;
	String experimentedGroup = craftingValues->getVisibleAttributeGroup(rowEffected);

	for (int i = 0; i < craftingValues->getTotalExperimentalAttributes(); ++i) {
		String attribute = craftingValues->getAttribute(i);
		String group = craftingValues->getAttributeGroup(attribute);

		if (group != experimentedGroup) {
			continue;
		}

		if (experimentationResult == CraftingManager::AMAZINGSUCCESS)
			modifier = 0.15f * (float)pointsAttempted; //
		if (experimentationResult == CraftingManager::GREATSUCCESS)
			modifier = 0.10 * (float)pointsAttempted; //
		if (experimentationResult == CraftingManager::GOODSUCCESS)
			modifier = 0.05 * (float)pointsAttempted;
		if (experimentationResult == CraftingManager::MODERATESUCCESS)
			modifier = 0.025 * (float)pointsAttempted;
		if (experimentationResult == CraftingManager::SUCCESS)
			modifier = 0.015 * (float)pointsAttempted;
		if (experimentationResult == CraftingManager::MARGINALSUCCESS)
			modifier = 0.0;
		if (experimentationResult == CraftingManager::OK)
			modifier = -0.05 * (float)pointsAttempted;
		if (experimentationResult == CraftingManager::BARELYSUCCESSFUL)
			modifier = -0.1 * (float)pointsAttempted;
		if (experimentationResult == CraftingManager::CRITICALFAILURE) {
			modifier = -0.1 * (float)pointsAttempted;
			// pick a random attribute
			int which = System::random(10);
			while(which != i) {
				which = System::random(10);
			}

			String failedGroup = craftingValues->getAttribute(which);

			float current = craftingValues->getCurrentPercentage(which);
			craftingValues->setCurrentPercentage(failedGroup, current * (-0.1)); // reduce a random attribute by 10%
		}

		//modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);
		newValue = craftingValues->getCurrentPercentage(attribute) + modifier;

		if (newValue > craftingValues->getMaxPercentage(attribute))
			newValue = craftingValues->getMaxPercentage(attribute);

		if (newValue < 0)
			newValue = 0;

		craftingValues->setCurrentPercentage(attribute, newValue);
	}

	craftingValues->recalculateValues(false);

	float currentFort = craftingValues->getCurrentValue("fortitude");
	int armorValue = currentFort/500;
	float currentEffective = (int)(((currentFort - (armorValue * 500)) / 50) * 5);

	for (int i = 0; i < craftingValues->getTotalExperimentalAttributes(); ++i) {
		String attribute = craftingValues->getAttribute(i);
		String group = craftingValues->getAttributeGroup(attribute);

		float minValue = craftingValues->getMinValue(attribute);

		if (group == "resists" && minValue >= 0) {
			float maxValue = craftingValues->getMaxValue(attribute);

			if (craftingValues->getCurrentValue(i) < maxValue) {
				craftingValues->setCurrentValue(attribute, Math::min(currentEffective, maxValue));
			}
		}
	}
}
