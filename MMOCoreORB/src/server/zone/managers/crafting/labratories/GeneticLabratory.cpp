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

	uint32 harMax, fortMax, endMax,intMax, dexMax,cleMax,depMax,couMax,fieMax,powMax;

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

	uint32 fortMin,endMin,harMin,intMin,dexMin,cleMin,depMin,couMin,fieMin,powMin;
	fortMin = Genetics::initialValue(fortMax);
	harMin = Genetics::initialValue(harMax);
	dexMin = Genetics::initialValue(dexMax);
	endMin = Genetics::initialValue(endMax);
	intMin = Genetics::initialValue(intMax);
	cleMin = Genetics::initialValue(cleMax);
	depMin = Genetics::initialValue(depMax);
	couMin = Genetics::initialValue(couMax);
	fieMin = Genetics::initialValue(fieMax);
	powMin = Genetics::initialValue(powMax);
	bool spBlast = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::BLAST);
	bool spKinetic = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::KINETIC);
	bool spEnergy = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ENERGY);
	bool spHeat = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::HEAT);
	bool spCold = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::COLD);
	bool spElectric = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ELECTRICITY);
	bool spAcid = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::ACID);
	bool spStun = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::STUN);
	bool spSaber = Genetics::hasASpecial(phy,pro,men,psy,agr,WeaponObject::LIGHTSABER);

	// Need to revist now for special protections
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

	float blastMin, energyMin, kineticMin, heatMin, coldMin, electricMin, acidMin, stunMin, saberMin;
	blastMin = Genetics::determineMinResistance(blastMax);
	kineticMin = Genetics::determineMinResistance(kineticMax);
	energyMin = Genetics::determineMinResistance(energyMax);
	heatMin = Genetics::determineMinResistance(heatMax);
	coldMin = Genetics::determineMinResistance(coldMax);
	electricMin = Genetics::determineMinResistance(electricMax);
	acidMin = Genetics::determineMinResistance(acidMax);
	stunMin = Genetics::determineMinResistance(stunMax);
	saberMin = Genetics::determineMinResistance(saberMax);

	if(saberMax < 0)
		spSaber = false;
	if (blastMax < 0)
		spBlast = false;
	if (kineticMax < 0)
		spKinetic = false;
	if (energyMax < 0)
		spEnergy = false;
	if (heatMax < 0)
		spHeat = false;
	if (coldMax < 0)
		spCold = false;
	if (electricMax < 0)
		spElectric = false;
	if(acidMax < 0)
		spAcid = false;
	if(stunMax < 0)
		spStun = false;

	craftingValues->addExperimentalProperty("expPhysiqueProfile","fortitude",fortMin,fortMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPhysiqueProfile","hardiness",harMin,harMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expProwessProfile","dexterity",dexMin,dexMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expProwessProfile","endurance",endMin,endMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expMentalProfile","intellect",intMin,intMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expMentalProfile","cleverness",cleMin,cleMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPsychologicalProfile","dependability",depMin,depMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expPsychologicalProfile","courage",couMin,couMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expAggressionProfile","fierceness",fieMin,fieMax,0,false,CraftingManager::LINEARCOMBINE);
	craftingValues->addExperimentalProperty("expAggressionProfile","power",powMin,powMax,0,false,CraftingManager::LINEARCOMBINE);

	craftingValues->addExperimentalProperty("resists","dna_comp_armor_kinetic",kineticMin,kineticMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_blast",blastMin,blastMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_energy",energyMin,energyMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_heat",heatMin,heatMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_cold",coldMin,coldMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_electric",electricMin,electricMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_acid",acidMin,acidMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_stun",stunMin,stunMax,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("resists","dna_comp_armor_saber",saberMin,saberMax,0,true,CraftingManager::OVERRIDECOMBINE);

	craftingValues->addExperimentalProperty("specials","kineticeffectiveness",spKinetic ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","blasteffectiveness",spBlast ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","energyeffectiveness",spEnergy ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","heateffectiveness",spHeat ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","coldeffectiveness",spCold ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("specials","electricityeffectiveness",spElectric ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("special","acideffectiveness",spAcid ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("special","stuneffectiveness",spStun ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("special","lightsabereffectiveness",spSaber ? 1: 0,1,0,true,CraftingManager::OVERRIDECOMBINE);

	craftingValues->setMaxPercentage("dna_comp_armor_kinetic",1);
	craftingValues->setMaxPercentage("dna_comp_armor_blast",1);
	craftingValues->setMaxPercentage("dna_comp_armor_energy",1);
	craftingValues->setMaxPercentage("dna_comp_armor_heat",1);
	craftingValues->setMaxPercentage("dna_comp_armor_cold",1);
	craftingValues->setMaxPercentage("dna_comp_armor_electric",1);
	craftingValues->setMaxPercentage("dna_comp_armor_acid",1);
	craftingValues->setMaxPercentage("dna_comp_armor_stun",1);
	craftingValues->setMaxPercentage("dna_comp_armor_saber",1);

	craftingValues->setCurrentPercentage("dna_comp_armor_kinetic",spKinetic ? 1 : (kineticMin/kineticMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_blast",spBlast ? 1 : (blastMin/blastMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_energy",spEnergy ? 1 : (energyMin/energyMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_heat",spHeat ? 1: (heatMin/heatMax) * modifier );
	craftingValues->setCurrentPercentage("dna_comp_armor_cold",spCold ? 1: (coldMin/coldMax) * modifier );
	craftingValues->setCurrentPercentage("dna_comp_armor_electric",spElectric ? 1 : (electricMin/electricMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_acid",spAcid ? 1 : (acidMin/acidMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_stun",spStun ? 1: (stunMin/stunMax) * modifier);
	craftingValues->setCurrentPercentage("dna_comp_armor_saber",spSaber ? 1: (saberMin/saberMax) * modifier);
	// update special to be their calculated max

	// Calc the max Percentage, vs Min Percentage genetic can always got up to 100% for a given title
	craftingValues->setMaxPercentage("fortitude", Genetics::maxExperimentationPercentage(fortMin,harMin,fortMax,harMax));
	craftingValues->setCurrentPercentage("fortitude",getAssemblyPercentage(fortMin) * modifier);

	craftingValues->setMaxPercentage("hardiness",Genetics::maxExperimentationPercentage(harMin,fortMin,harMax,fortMax));
	craftingValues->setCurrentPercentage("hardiness",getAssemblyPercentage(harMin) * modifier);

	craftingValues->setMaxPercentage("dexterity",Genetics::maxExperimentationPercentage(dexMin,endMin,dexMax,endMax));
	craftingValues->setCurrentPercentage("dexterity",getAssemblyPercentage(dexMin) * modifier);

	craftingValues->setMaxPercentage("endurance",Genetics::maxExperimentationPercentage(endMin,dexMin,endMax,dexMax));
	craftingValues->setCurrentPercentage("endurance",getAssemblyPercentage(endMin) * modifier);

	craftingValues->setMaxPercentage("intellect",Genetics::maxExperimentationPercentage(intMin,cleMin,intMax,cleMax));
	craftingValues->setCurrentPercentage("intellect",getAssemblyPercentage(intMin) * modifier);

	craftingValues->setMaxPercentage("cleverness",Genetics::maxExperimentationPercentage(cleMin,intMin,cleMax,intMax));
	craftingValues->setCurrentPercentage("cleverness",getAssemblyPercentage(cleMin) * modifier);

	craftingValues->setMaxPercentage("dependability",Genetics::maxExperimentationPercentage(depMin,couMin,depMax,couMax));
	craftingValues->setCurrentPercentage("dependability",getAssemblyPercentage(dexMin) * modifier);

	craftingValues->setMaxPercentage("courage",Genetics::maxExperimentationPercentage(couMin,depMin,couMax,depMax));
	craftingValues->setCurrentPercentage("courage",getAssemblyPercentage(couMin) * modifier);

	craftingValues->setMaxPercentage("fierceness",Genetics::maxExperimentationPercentage(fieMin,powMin,fieMax,powMax));
	craftingValues->setCurrentPercentage("fierceness",getAssemblyPercentage(fieMin) * modifier);

	craftingValues->setMaxPercentage("power",Genetics::maxExperimentationPercentage(powMin,fieMin,powMax,fieMax));
	craftingValues->setCurrentPercentage("power",getAssemblyPercentage(powMin) * modifier);

	int quality = ( ((float)phy->getQuality() * 0.2)+ ((float)pro->getQuality()*0.2) + ((float)men->getQuality()*0.2) + ((float)psy->getQuality()*0.2) + ((float)agr->getQuality()*0.2));
	bool ranged = false;
	int odds = 0;
	float menQual = 7 - men->getQuality();
	float psyQual = 7 - psy->getQuality();
	if (men->isRanged() || psy->isRanged()) {
		int chance = System::random((assemblySuccess * 10)-100); // so amazing success 100, critical falure is 20
		// did you roll exceed (7 - Quality) * 10 (VHQ is 0) so always works
		if (chance > (menQual * 10) || chance > (psyQual * 10))
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
	//int level = (phy->getLevel() + pro->getLevel() + men->getLevel() + psy->getLevel() + agr->getLevel()) / 5;
	//genetic->setLevel(level);
	craftingValues->recalculateValues(true);
	recalculateResist(craftingValues);
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
	float modifier, newValue, valA, valB;
	String title, subtitle, subtitlesTitle;
	title = craftingValues->getVisibleExperimentalPropertyTitle(rowEffected);
	modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);
	// We need to change this to increase in a more linear fashion and determine percentages inverse
	String prop1 = "";
	String prop2 = "";
	Vector<String> others;
	float a = 0;
	float b = 0;
	float maxA = 0;
	float maxB = 0;
	others.add("dexterity");
	others.add("endurance");
	others.add("intellect");
	others.add("cleverness");
	others.add("dependability");
	others.add("courage");
	others.add("fierceness");
	others.add("power");
	others.add("hardiness");
	others.add("fortitude");

	if (title == "expPhysiqueProfile") {
		prop1 = "hardiness";
		prop2 = "fortitude";
	}
	if (title == "expProwessProfile") {
		prop1 = "dexterity";
		prop2 = "endurance";
	}
	if (title == "expMentalProfile") {
		prop1 = "intellect";
		prop2 = "cleverness";
	}
	if (title == "expPsychologicalProfile") {
		prop1 = "dependability";
		prop2 = "courage";
	}
	if (title == "expAggressionProfile") {
		prop1 = "fierceness";
		prop2 = "power";
	}
	others.removeElement(prop1);
	others.removeElement(prop2);
	bool reduceA = false;
	bool reduceB = false;
	// get a random 2nd title

	switch(experimentationResult) {
		case CraftingManager::CRITICALFAILURE:
			int which = System::random(1);
			if (which == 0) {
				reduceA = true;
			} else {
				reduceB = true;
			}
			break;
	}
	float boost = 0.1f;
	for(int i=0;i<pointsAttempted;i++) {
		craftingValues->unlockValue(prop1);
		craftingValues->unlockValue(prop2);
		a = craftingValues->getCurrentValue(prop1);
		b = craftingValues->getCurrentValue(prop2);
		maxA = craftingValues->getMaxValue(prop1);
		maxB = craftingValues->getMaxValue(prop2);
		// this is per point add this for each point spent we use slightly diff calcs than resources since we need to work on 2 at once in a relation ship
		// we need to detmine how much it goes up per point as a percentage
		// so a/(a+b) * 140
		//    b/(a+b) * 140
		// this is the amount we increase
		float increaseA = Genetics::experimentFormula(b,a);
		float increaseB = Genetics::experimentFormula(a,b);

		if (CraftingManager::CRITICALFAILURE == experimentationResult) {
			boost = -0.08f;
			if (reduceA){
				increaseA = -increaseA * 0.08;
				increaseB = -increaseB * 0.08;
			}
			else{
				increaseA -= increaseA * 0.09;
				increaseB -= increaseB * 0.09;
			}
			if (reduceB){
				increaseA = -increaseA * 0.08;
				increaseB = -increaseB * 0.08;
			}
			else{
				increaseA -= increaseA * 0.09;
				increaseB -= increaseB * 0.09;
			}
			a += increaseA;
			b += increaseB;
			if (b > maxB)
				b = maxB;
			if (a > maxA)
				a = maxA;
			float cap = craftingValues->getCurrentPercentage(prop1);
			float cbp = craftingValues->getCurrentPercentage(prop2);
			cap += boost;
			cbp += boost;
			if (cbp > 1)
				cbp = 1;
			if (cap > 1)
				cap = 1;
			craftingValues->setCurrentValue(prop1,a);
			craftingValues->setCurrentValue(prop2,b);
			craftingValues->setCurrentPercentage(prop1,cap);
			craftingValues->setCurrentPercentage(prop2,cbp);
			craftingValues->lockValue(prop1);
			craftingValues->lockValue(prop2);

			if (System::random(100) < 20) {
				// increase other property by a percentage point
				int index = System::random(others.size()-1);
				String p = others.get(index);
				int newValue = craftingValues->getCurrentValue(p);
				int oValue = newValue;
				int maxValue = craftingValues->getMaxValue(p);
				newValue = getPercentagOfValue(newValue,0.02);
				newValue += oValue;
				if (newValue > maxValue)
					newValue = maxValue;
				craftingValues->setCurrentPercentage(p,craftingValues->getCurrentPercentage(p) + 0.02);
				craftingValues->setCurrentValue(p,newValue);
			}
		} else {
			if (experimentationResult == CraftingManager::AMAZINGSUCCESS) {
				boost = 0.15;
				increaseA *= 0.05;
				increaseB *= 0.05;
			}
			if (experimentationResult == CraftingManager::GREATSUCCESS)
				boost = 0.1;
			if (experimentationResult == CraftingManager::GOODSUCCESS) {
				boost = 0.08;
				increaseA -= increaseA * 0.02;
				increaseB -= increaseB * 0.02;
			}
			if (experimentationResult == CraftingManager::MODERATESUCCESS) {
				boost = 0.075;
				increaseA -= increaseA * 0.025;
				increaseB -= increaseB * 0.025;
			}
			if (experimentationResult == CraftingManager::SUCCESS) {
				boost = 0.01;
				increaseA -= increaseA * 0.09;
				increaseB -= increaseB * 0.09;
			}
			if (experimentationResult == CraftingManager::MARGINALSUCCESS) {
				boost = 0.00;
				increaseA = 0;
				increaseB = 0;
			}
			if (experimentationResult == CraftingManager::OK) {
				boost = -0.04;
				increaseA = -increaseA * 0.04;
				increaseB = -increaseB * 0.04;
			}
			if (experimentationResult == CraftingManager::BARELYSUCCESSFUL) {
				boost = -0.07;
				increaseA = -increaseA * 0.07;
				increaseB = -increaseB * 0.07;
			}
			a += increaseA;
			b += increaseB;
			if (b > maxB)
				b = maxB;
			if (a > maxA)
				a = maxA;
			float cap = craftingValues->getCurrentPercentage(prop1);
			float cbp = craftingValues->getCurrentPercentage(prop2);
			cap += boost;
			cbp += boost;
			if (cbp > 1)
				cbp = 1;
			if (cap > 1)
				cap = 1;
			craftingValues->setCurrentValue(prop1,a);
			craftingValues->setCurrentValue(prop2,b);
			craftingValues->setCurrentPercentage(prop1,cap);
			craftingValues->setCurrentPercentage(prop2,cbp);
			craftingValues->lockValue(prop1);
			craftingValues->lockValue(prop2);
		}
	}
	// we have an initial value: and a max value inrease by same percentage as the experimented row. so 10 points of great success would be 100% on the resist values
	if (craftingValues->getCurrentPercentage("dna_comp_armor_kinetic") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_kinetic",craftingValues->getCurrentPercentage("dna_comp_armor_kinetic") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_blast") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_blast",craftingValues->getCurrentPercentage("dna_comp_armor_blast") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_energy") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_energy",craftingValues->getCurrentPercentage("dna_comp_armor_energy") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_heat") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_heat",craftingValues->getCurrentPercentage("dna_comp_armor_heat") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_cold") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_cold",craftingValues->getCurrentPercentage("dna_comp_armor_cold") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_electric") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_electric",craftingValues->getCurrentPercentage("dna_comp_armor_electric") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_acid") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_acid",craftingValues->getCurrentPercentage("dna_comp_armor_acid") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_stun") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_stun",craftingValues->getCurrentPercentage("dna_comp_armor_stun") + boost);

	if (craftingValues->getCurrentPercentage("dna_comp_armor_saber") < 1)
		craftingValues->setCurrentPercentage("dna_comp_armor_saber",craftingValues->getCurrentPercentage("dna_comp_armor_saber") + boost);

	recalculateResist(craftingValues);
}
