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
	String experimentalPropTitle, attributeName;
	float percentage = 0.f, min = 0.f, max = 0.f, newValue = 0.f, oldValue = 0.f;
	bool hidden = false;
	for (int i = 0; i < craftingValues->getSubtitleCount(); ++i) {

		attributeName = craftingValues->getExperimentalPropertySubtitle(i);

		experimentalPropTitle = craftingValues->getExperimentalPropertyTitle(attributeName);

		min = craftingValues->getMinValue(attributeName);
		max = craftingValues->getMaxValue(attributeName);

		hidden = craftingValues->isHidden(attributeName);

		percentage = craftingValues->getCurrentPercentage(attributeName);//experimentalPropTitle);

		oldValue = craftingValues->getCurrentValue(attributeName);

		if(max != min) {
			if (max > min)
				newValue = (percentage * (max - min)) + min;
			else
				newValue = (float(1.0f - percentage) * (min - max)) + max;
		} else if(max == min) {
			newValue = max;
		}
		if (hidden && experimentalPropTitle == "resists") {
			craftingValues->setCurrentValue(attributeName, newValue);
		}
	}

}
void GeneticLabratory::setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess) {

	if(manufactureSchematic == NULL || manufactureSchematic->getDraftSchematic() == NULL)
		return;
	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();
	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	float value, maxPercentage, currentPercentage, weightedSum;
	String itemName;
	// These 2 values are pretty standard, adding these
	itemName = "xp";
	value = float(draftSchematic->getXpAmount());
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, true, CraftingManager::OVERRIDECOMBINE);
	itemName = "complexity";
	value = manufactureSchematic->getComplexity();
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, true, CraftingManager::OVERRIDECOMBINE);
	float modifier = calculateAssemblyValueModifier(assemblySuccess);
	// Cast component to genetic
	if (!prototype->isComponent())
		return;

	GeneticComponent* genetic = cast<GeneticComponent*>(prototype);
	HashTable<String, ManagedReference<DnaComponent*> > slots;
	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {
		// Dna Component Slots
		Reference<IngredientSlot* > iSlot = manufactureSchematic->getSlot(i);
		ComponentSlot* cSlot = cast<ComponentSlot*>(iSlot.get());
		ManagedReference<TangibleObject*> tano = cSlot->getPrototype();
		ManagedReference<DnaComponent*> component = cast<DnaComponent*>( tano.get());
		slots.put(cSlot->getSlotName(),component);
	}
	// At this point we have all the DNA slots. Update the craftingvalue accordingly
	DnaComponent* phy = slots.get("physique_profile").get();
	DnaComponent* pro = slots.get("prowess_profile").get();
	DnaComponent* men = slots.get("mental_profile").get();
	DnaComponent* psy = slots.get("psychological_profile").get();
	DnaComponent* agr = slots.get("aggression_profile").get();
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
	bool spBlast = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::BLAST);
	bool spKinetic = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::KINETIC);
	bool spEnergy = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ENERGY);
	bool spHeat = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::HEAT);
	bool spCold = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::COLD);
	bool spElectric = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ELECTRICITY);
	bool spAcid = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ACID);
	bool spStun = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::STUN);
	bool spSaber = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::LIGHTSABER);
	// Calculate resists
	// 1 percent: (1000 - 0) / 100.0f;
	float blastMax, energyMax, kineticMax,heatMax,coldMax,electricMax,acidMax,stunMax,saberMax;
	blastMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::BLAST,100.0f);
	kineticMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::KINETIC,60.0f);
	energyMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::ENERGY,60.0f);
	heatMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::HEAT,100.0f);
	coldMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::COLD,100.0f);
	electricMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::ELECTRICITY,100.0f);
	acidMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::ACID,100.0f);
	stunMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::STUN,100.0f);
	saberMax = Genetics::resistanceFormula(phy,pro,men,psy,agr,WeaponObject::LIGHTSABER,100.0f);
	// lets clear the special bit if it moved to effective range.
	if(saberMax == 0) {
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
	if(acidMax == 0) {
		spAcid = false;
		acidMax = 100;
	}
	if(stunMax == 0) {
		spStun = false;
		stunMax = 100;
	}

	// Step 2. At this point we know the max values for all stats and we have calculated any armor specials needed
	// So now we need to setup the min and initial values of stats and define the experimental attributes. // Ranges are 0 to 100 for any one of these
	// set current value to be 70% less than max calculated as the experimentation range. i.e.
	craftingValues->addExperimentalProperty("expPhysiqueProfile","fortitude",0,fortMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPhysiqueProfile","hardiness",0,harMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expProwessProfile","dexterity",0,dexMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expProwessProfile","endurance",0,endMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expMentalProfile","intellect",0,intMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expMentalProfile","cleverness",0,cleMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPsychologicalProfile","dependability",0,depMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPsychologicalProfile","courage",0,couMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expAggressionProfile","fierceness",0,fieMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expAggressionProfile","power",0,powMax,0,false,CraftingManager::LINEARCOMBINE);
	String title;
	int armorBase = 0;
	int effectiveness = 0;
	for(int i=0;i<craftingValues->getExperimentalPropertySubtitleSize();i++) {
		title = craftingValues->getExperimentalPropertySubtitle(i);
		if (craftingValues->isHidden(title))
			continue;
		// We need to accoutn for assembly percentage. do some swapping around as well.
		float maxValue = craftingValues->getMaxValue(title);
		float initialValue = Genetics::initialValue(craftingValues->getMaxValue(title));
		// determine max percentage
		craftingValues->setMaxPercentage(title, maxValue/1000.0f);
		craftingValues->setMaxValue(title,1000);
		// using assembly to accoutn for a 1 +% increase
		currentPercentage = getAssemblyPercentage(initialValue) * modifier;
		//craftingValues->setMaxPercentage(title, maxPercentage);
		craftingValues->setCurrentPercentage(title, currentPercentage);
		if (title == "fortitude") {
			armorBase = craftingValues->getCurrentValue(title);
		}
	}
	int armorValue = armorBase/500;
	effectiveness = (int)(((armorBase - (armorValue * 500)) / 50) * 5);
	// Store off armor data
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_kinetic",spKinetic ? kineticMax : kineticMax < 0 ? -1 : effectiveness,kineticMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_blast",spBlast ? blastMax : blastMax < 0 ? -1 : effectiveness, blastMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_energy",spEnergy ? energyMax : energyMax < 0 ? -1 : effectiveness, energyMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_heat",spHeat ? heatMax : heatMax < 0 ? -1 :  effectiveness ,heatMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_cold",spCold ? coldMax : coldMax < 0 ? -1 : effectiveness ,coldMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_electric",spElectric ? electricMax : electricMax < 0 ? -1 : effectiveness ,electricMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_acid",spAcid ? acidMax : acidMax < 0 ? -1 : effectiveness ,acidMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_stun",spStun ? stunMax : stunMax < 0 ? -1 : effectiveness ,stunMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_saber",spSaber ? saberMax : saberMax < 0 ? -1 : effectiveness ,saberMax,0,true,CraftingManager::OVERRIDECOMBINE);
	// Store off special information
	craftingValues->addExperimentalProperty("specials","kineticeffectiveness",spKinetic ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","blasteffectiveness",spBlast ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","energyeffectiveness",spEnergy ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","heateffectiveness",spHeat ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","coldeffectiveness",spCold ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","electricityeffectiveness",spElectric ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","acideffectiveness",spAcid ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","stuneffectiveness",spStun ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","lightsabereffectiveness",spSaber ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
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

bool GeneticLabratory::allowFactoryRun(ManufactureSchematic* manufactureSchematic) {
	return false;
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
	String title, subtitle, subtitlesTitle, screwedTitle;
	title = craftingValues->getVisibleExperimentalPropertyTitle(rowEffected);
	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(i);
		if (subtitlesTitle == title) {
			subtitle = craftingValues->getExperimentalPropertySubtitle(i);
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
				screwedTitle = craftingValues->getExperimentalPropertySubtitle(which);
				float current = craftingValues->getCurrentPercentage(which);
				craftingValues->setCurrentPercentage(screwedTitle,current * (-0.1)); // reduce a random attribute by 10%
			}
			//modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);
			newValue = craftingValues->getCurrentPercentage(subtitle) + modifier;
			if (newValue > craftingValues->getMaxPercentage(subtitle))
				newValue = craftingValues->getMaxPercentage(subtitle);

			if (newValue < 0)
				newValue = 0;

			craftingValues->setCurrentPercentage(subtitle, newValue);
		}
	}
	craftingValues->recalculateValues(false);
	float currentFort = craftingValues->getCurrentValue("fortitude");
	int armorValue = currentFort/500;
	float currentEffective = (int)(((currentFort - (armorValue * 500)) / 50) * 5);
	title = craftingValues->getExperimentalPropertyTitle("resists");
	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		if (subtitlesTitle == title) {
			subtitle = craftingValues->getExperimentalPropertySubtitle(i);
			if (craftingValues->getMaxValue(subtitle) != craftingValues->getCurrentValue(i)) {
				craftingValues->setCurrentValue(subtitle,currentEffective);
			}
		}
	}
}
