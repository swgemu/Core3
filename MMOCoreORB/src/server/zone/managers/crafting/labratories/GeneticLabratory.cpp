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

GeneticLabratory::GeneticLabratory() {
}

GeneticLabratory::~GeneticLabratory() {
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
	float percentage = 0.f, min = 0.f, max = 0.f, newValue = 0.f, oldValue = 0.f;
	bool hidden = false;

	for (int i = 0; i < craftingValues->getTotalExperimentalAttributes(); ++i) {
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
	}

}
void GeneticLabratory::setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess) {
	if (manufactureSchematic == nullptr)
		return;

	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();

	if (draftSchematic == nullptr)
		return;

	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	float value, maxPercentage, currentPercentage, weightedSum;
	String itemName;

	// These 2 values are pretty standard, adding these
	value = float(draftSchematic->getXpAmount());
	craftingValues->addExperimentalAttribute("xp", "", value, value, 0, true, AttributesMap::OVERRIDECOMBINE);

	value = manufactureSchematic->getComplexity();
	craftingValues->addExperimentalAttribute("complexity", "", value, value, 0, true, AttributesMap::OVERRIDECOMBINE);

	float modifier = calculateAssemblyValueModifier(assemblySuccess);

	// Cast component to genetic
	if (!prototype->isComponent())
		return;

	GeneticComponent* genetic = cast<GeneticComponent*>(prototype);

	if (genetic == nullptr)
		return;

	HashTable<String, ManagedReference<DnaComponent*> > slots;

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {
		// Dna Component Slots
		Reference<IngredientSlot* > iSlot = manufactureSchematic->getSlot(i);
		ComponentSlot* cSlot = iSlot.castTo<ComponentSlot*>();

		if (cSlot == nullptr)
			continue;

		ManagedReference<TangibleObject*> tano = cSlot->getPrototype();

		if (tano == nullptr)
			continue;

		ManagedReference<DnaComponent*> component = tano.castTo<DnaComponent*>();

		if (component == nullptr)
			continue;

		slots.put(cSlot->getSlotName(), component);
	}

	// At this point we have all the DNA slots. Update the craftingvalue accordingly
	DnaComponent* phy = slots.get("physique_profile").get();
	DnaComponent* pro = slots.get("prowess_profile").get();
	DnaComponent* men = slots.get("mental_profile").get();
	DnaComponent* psy = slots.get("psychological_profile").get();
	DnaComponent* agr = slots.get("aggression_profile").get();

	if (phy == nullptr || pro == nullptr || men == nullptr || psy == nullptr || agr == nullptr)
		return;

	// REVAMP FROM HERE DOWN.
	// STEP 1. Determine Attributes
	uint32 harMax, fortMax, endMax,intMax, dexMax,cleMax,depMax,couMax,fieMax,powMax;

	// Calculate the max values i.e. the weighter resource avergae.
	fortMax = Genetics::physiqueFormula(phy->getForititude(),pro->getForititude(),men->getForititude(),psy->getForititude(),agr->getForititude());
	harMax = Genetics::physiqueFormula(phy->getHardiness(),pro->getHardiness(),men->getHardiness(),psy->getHardiness(),agr->getHardiness());
	dexMax = Genetics::prowessFormula(phy->getDexterity(),pro->getDexterity(),men->getDexterity(),psy->getDexterity(),agr->getDexterity());
	endMax = Genetics::prowessFormula(phy->getEndurance(),pro->getEndurance(),men->getEndurance(),psy->getEndurance(),agr->getEndurance());
	intMax = Genetics::mentalFormula(phy->getIntellect(),pro->getIntellect(),men->getIntellect(),psy->getIntellect(),agr->getIntellect());
	cleMax = Genetics::mentalFormula(phy->getCleverness(),pro->getCleverness(),men->getCleverness(),psy->getCleverness(),agr->getCleverness());
	depMax = Genetics::physchologicalFormula(phy->getDependency(),pro->getDependency(),men->getDependency(),psy->getDependency(),agr->getDependency());
	couMax = Genetics::physchologicalFormula(phy->getCourage(),pro->getCourage(),men->getCourage(),psy->getCourage(),agr->getCourage());
	fieMax = Genetics::aggressionFormula(phy->getFierceness(),pro->getFierceness(),men->getFierceness(),psy->getFierceness(),agr->getFierceness());
	powMax = Genetics::aggressionFormula(phy->getPower(),pro->getPower(),men->getPower(),psy->getPower(),agr->getPower());

	// acknowledge any specials found in the experimentation line. this means specials will not modify later by experimentaiton as its an overlay value.
	bool spBlast = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::BLAST);
	bool spKinetic = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::KINETIC);
	bool spEnergy = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ENERGY);
	bool spHeat = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::HEAT);
	bool spCold = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::COLD);
	bool spElectric = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ELECTRICITY);
	bool spAcid = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ACID);
	bool spStun = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::STUN);
	bool spSaber = Genetics::hasASpecial(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::LIGHTSABER);

	// Calculate resists
	// 1 percent: (1000 - 0) / 100.0f;
	float blastMax, energyMax, kineticMax,heatMax,coldMax,electricMax,acidMax,stunMax,saberMax;
	blastMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::BLAST,100.0f);
	kineticMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::KINETIC,60.0f);
	energyMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ENERGY,60.0f);
	heatMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::HEAT,100.0f);
	coldMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::COLD,100.0f);
	electricMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ELECTRICITY,100.0f);
	acidMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::ACID,100.0f);
	stunMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::STUN,100.0f);
	saberMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,SharedWeaponObjectTemplate::LIGHTSABER,100.0f);

	// lets clear the special bit if it moved to effective range.
	if (saberMax == 0) {
		spSaber = false;
		saberMax = 100;
	}
	if (blastMax == 0) {
		spBlast = false;
		blastMax = 100;
	}
	if (kineticMax == 0) {
		spKinetic = false;
		kineticMax = 60;
	}
	if (energyMax == 0) {
		spEnergy = false;
		energyMax = 60;
	}
	if (heatMax == 0) {
		spHeat = false;
		heatMax = 100;
	}
	if (coldMax == 0) {
		spCold = false;
		coldMax = 100;
	}
	if (electricMax == 0) {
		spElectric = false;
		electricMax = 100;
	}
	if (acidMax == 0) {
		spAcid = false;
		acidMax = 100;
	}
	if (stunMax == 0) {
		spStun = false;
		stunMax = 100;
	}

	// Step 2. At this point we know the max values for all stats and we have calculated any armor specials needed
	// So now we need to setup the min and initial values of stats and define the experimental attributes. // Ranges are 0 to 100 for any one of these
	// set current value to be 70% less than max calculated as the experimentation range. i.e.
	craftingValues->addExperimentalAttribute("fortitude", "expPhysiqueProfile", 0, fortMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("hardiness", "expPhysiqueProfile", 0, harMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("dexterity", "expProwessProfile", 0, dexMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("endurance", "expProwessProfile",  0, endMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("intellect", "expMentalProfile", 0, intMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("cleverness", "expMentalProfile", 0, cleMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("dependability", "expPsychologicalProfile", 0, depMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("courage", "expPsychologicalProfile", 0, couMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("fierceness", "expAggressionProfile", 0, fieMax, 0, false, AttributesMap::LINEARCOMBINE);
	craftingValues->addExperimentalAttribute("power", "expAggressionProfile", 0, powMax, 0, false, AttributesMap::LINEARCOMBINE);

	int armorBase = 0;
	int effectiveness = 0;

	for (int i = 0; i < craftingValues->getTotalExperimentalAttributes(); i++) {
		String attriute = craftingValues->getAttribute(i);

		if (craftingValues->isHidden(attriute))
			continue;

		// We need to accoutn for assembly percentage. do some swapping around as well.
		float maxValue = craftingValues->getMaxValue(attriute);
		float initialValue = Genetics::initialValue(craftingValues->getMaxValue(attriute));

		// determine max percentage
		craftingValues->setMaxPercentage(attriute, maxValue/1000.0f);
		craftingValues->setMaxValue(attriute,1000);

		// using assembly to accoutn for a 1 +% increase
		currentPercentage = getAssemblyPercentage(initialValue) * modifier;

		//craftingValues->setMaxPercentage(attriute, maxPercentage);
		craftingValues->setCurrentPercentage(attriute, currentPercentage);

		if (attriute == "fortitude") {
			armorBase = craftingValues->getCurrentValue(attriute);
		}
	}

	int armorValue = armorBase/500;
	effectiveness = (int)(((armorBase - (armorValue * 500)) / 50) * 5);

	// Store off armor data
	craftingValues->addExperimentalAttribute("dna_comp_armor_kinetic", "resists", spKinetic ? kineticMax : kineticMax < 0 ? -1 : effectiveness, kineticMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_blast", "resists", spBlast ? blastMax : blastMax < 0 ? -1 : effectiveness, blastMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_energy", "resists", spEnergy ? energyMax : energyMax < 0 ? -1 : effectiveness, energyMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_heat", "resists", spHeat ? heatMax : heatMax < 0 ? -1 :  effectiveness, heatMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_cold", "resists", spCold ? coldMax : coldMax < 0 ? -1 : effectiveness, coldMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_electric", "resists", spElectric ? electricMax : electricMax < 0 ? -1 : effectiveness, electricMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_acid", "resists", spAcid ? acidMax : acidMax < 0 ? -1 : effectiveness, acidMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_stun", "resists", spStun ? stunMax : stunMax < 0 ? -1 : effectiveness, stunMax, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("dna_comp_armor_saber", "resists", spSaber ? saberMax : saberMax < 0 ? -1 : effectiveness, saberMax, 0, true, AttributesMap::OVERRIDECOMBINE);

	// Store off special information
	craftingValues->addExperimentalAttribute("kineticeffectiveness", "specials", spKinetic ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("blasteffectiveness", "specials", spBlast ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("energyeffectiveness", "specials", spEnergy ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("heateffectiveness", "specials", spHeat ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("coldeffectiveness", "specials", spCold ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("electricityeffectiveness", "specials", spElectric ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("acideffectiveness", "specials", spAcid ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("stuneffectiveness", "specials", spStun ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);
	craftingValues->addExperimentalAttribute("lightsabereffectiveness", "specials", spSaber ? 1 : 0, 1, 0, true, AttributesMap::OVERRIDECOMBINE);

	int quality = ( ((float)phy->getQuality() * 0.2)+ ((float)pro->getQuality()*0.2) + ((float)men->getQuality()*0.2) + ((float)psy->getQuality()*0.2) + ((float)agr->getQuality()*0.2));
	bool ranged = false;
	int odds = 0;
	float menQual = men->getQuality() - 1;
	float psyQual = psy->getQuality() - 1;

	if (men->isRanged() || psy->isRanged()) {
		int chance = System::random(100-(assemblySuccess * 10)); // so amazing success 100, critical falure is 20
		// did you roll exceed (7 - Quality) * 10 (VHQ is 0) so always works
		if (chance >= (menQual * 10) || chance >= (psyQual * 10))
			ranged = true;
	}

	odds = quality * 100;
	// check for specials here, then we have base assemble work completed.
	// update crafting values, and/or experimentRow should handle resist calc changes. update crafting values should determine armor setup
	String sp1 = pickSpecialAttack(agr->getSpecialAttackOne(),psy->getSpecialAttackOne(),phy->getSpecialAttackOne(),men->getSpecialAttackOne(),pro->getSpecialAttackOne(),odds,"defaultattack");
	String sp2 = pickSpecialAttack(psy->getSpecialAttackTwo(),pro->getSpecialAttackTwo(),agr->getSpecialAttackTwo(),men->getSpecialAttackTwo(),phy->getSpecialAttackTwo(),odds,sp1);
	genetic->setSpecialAttackOne(sp1);
	genetic->setSpecialAttackTwo(sp2);
	genetic->setRanged(ranged);
	genetic->setQuality(quality);

	// determine avg sample levels to choose a level of this template for output generation
	int level = Genetics::physchologicalFormula(phy->getLevel(),pro->getLevel(),men->getLevel(), psy->getLevel() ,agr->getLevel());
	genetic->setLevel(level);

	craftingValues->recalculateValues(true);
}

void GeneticLabratory::initialize(ZoneServer* server) {
	SharedLabratory::initialize(server);

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
