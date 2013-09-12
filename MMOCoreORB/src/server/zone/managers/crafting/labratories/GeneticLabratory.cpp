/*
 * GeneticLabratory.cpp
 *
 *  Created on: Aug 7, 2013
 *      Author: swgemu
 */

#include "GeneticLabratory.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"

GeneticLabratory::GeneticLabratory() {
}

GeneticLabratory::~GeneticLabratory() {
}

float GeneticLabratory::applyFormula(float aVal, float bVal, float cVal, float dVal, float eVal,int formula) {
	float a = aVal;
	float b = bVal;
	float c = cVal;
	float d = dVal;
	float e = eVal;
	float rc = 0;
	if (aVal < 0)
		a = -99;
	if (bVal < 0)
		b = -99;
	if (cVal < 0)
		c = -99;
	if (dVal < 0)
		d = -99;
	if (eVal < 0)
		e = -99;
	switch (formula) {
		case PHYSIQUE:
			rc = (a * 0.4) + (b *0.25) + (c * 0.05) + (d * 0.05) + (e * 0.25);
			break;
		case PROWESS:
			rc = (a * 0.25) + (b *0.42) + (c * 0.17) + (d * 0.085) + (e * .075);
			break;
		case MENTAL:
			rc = (a * 0.05) + (b *0.1) + (c * 0.5) + (d * 0.3) + (e * .05);
			break;
		case PHYSCHOLOGICAL:
			rc = (a * 0.09) + (b *0.05) + (c * 0.26) + (d * 0.43) + (e * 0.17);
			break;
		case AGRESSION:
			rc = (a * 0.17) + (b *0.16) + (c * 0.085) + (d * 0.165) + (e * 0.42);
			break;
	}
	if (rc > 1000)
		rc = 1000;
	return rc;
}
String GeneticLabratory::pickSpecialAttack(String a, String b, String c, String d, String e, int odds) {
	String effectiveSpecial = "defaultattack";
	if (a.isEmpty()) {
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
	if (effectiveSpecial == "defaultattack" ||
		effectiveSpecial == "creatureareacombo" ||
		effectiveSpecial == "creatureareableeding" ||
		effectiveSpecial == "creatureareaknockdown" ||
		effectiveSpecial == "creatureareadisease" ||
		effectiveSpecial == "creatureareapoison")
		effectiveSpecial = "defaultattack";
	int roll = System::random(1000);
	if (roll > odds ) {
		effectiveSpecial = "defaultattack";
	}
	return effectiveSpecial;
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

	fortMax = applyFormula(phy->getForititude(),pro->getForititude(),men->getForititude(),psy->getForititude(),agr->getForititude(),PHYSIQUE);
	harMax = applyFormula(phy->getHardiness(),pro->getHardiness(),men->getHardiness(),psy->getHardiness(),agr->getHardiness(),PHYSIQUE);
	dexMax = applyFormula(phy->getDexterity(),pro->getDexterity(),men->getDexterity(),psy->getDexterity(),agr->getDexterity(),PROWESS);
	endMax = applyFormula(phy->getEndurance(),pro->getEndurance(),men->getEndurance(),psy->getEndurance(),agr->getEndurance(),PROWESS);
	intMax = applyFormula(phy->getIntellect(),pro->getIntellect(),men->getIntellect(),psy->getIntellect(),agr->getIntellect(),MENTAL);
	cleMax = applyFormula(phy->getCleverness(),pro->getCleverness(),men->getCleverness(),psy->getCleverness(),agr->getCleverness(),MENTAL);
	depMax = applyFormula(phy->getDependency(),pro->getDependency(),men->getDependency(),psy->getDependency(),agr->getDependency(),PHYSCHOLOGICAL);
	couMax = applyFormula(phy->getCourage(),pro->getCourage(),men->getCourage(),psy->getCourage(),agr->getCourage(),PHYSCHOLOGICAL);
	fieMax = applyFormula(phy->getFierceness(),pro->getFierceness(),men->getFierceness(),psy->getFierceness(),agr->getFierceness(),AGRESSION);
	powMax = applyFormula(phy->getPower(),pro->getPower(),men->getPower(),psy->getPower(),agr->getPower(),AGRESSION);

	uint32 fortMin,endMin,harMin,intMin,dexMin,cleMin,depMin,couMin,fieMin,powMin;
	fortMin = calcMin(fortMax);
	harMin = calcMin(harMax);
	dexMin = calcMin(dexMax);
	endMin = calcMin(endMax);
	intMin = calcMin(intMax);
	cleMin = calcMin(cleMax);
	depMin = calcMin(depMax);
	couMin = calcMin(couMax);
	fieMin = calcMin(fieMax);
	powMin = calcMin(powMax);

	float blast, energy, kinetic,heat,cold,electric,acid,stun,saber;
	blast = applyFormula(phy->getBlast(),pro->getBlast(),men->getBlast(),psy->getBlast(),agr->getBlast(),PHYSIQUE);
	kinetic = applyFormula(phy->getKinetic(),pro->getKinetic(),men->getKinetic(),psy->getKinetic(),agr->getKinetic(),PHYSIQUE);
	energy = applyFormula(phy->getEnergy(),pro->getEnergy(),men->getEnergy(),psy->getEnergy(),agr->getEnergy(),PHYSIQUE);
	heat = applyFormula(phy->getHeat(),pro->getHeat(),men->getHeat(),psy->getHeat(),agr->getHeat(),PHYSIQUE);
	cold = applyFormula(phy->getCold(),pro->getCold(),men->getCold(),psy->getCold(),agr->getCold(),PHYSIQUE);
	electric = applyFormula(phy->getElectric(),pro->getElectric(),men->getElectric(),psy->getElectric(),agr->getElectric(),PHYSIQUE);
	acid = applyFormula(phy->getAcid(),pro->getAcid(),men->getAcid(),psy->getAcid(),agr->getAcid(),PHYSIQUE);
	stun = applyFormula(phy->getStun(),pro->getStun(),men->getStun(),psy->getStun(),agr->getStun(),PHYSIQUE);
	saber = applyFormula(phy->getSaber(),pro->getSaber(),men->getSaber(),psy->getSaber(),agr->getSaber(),PHYSIQUE);

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

	craftingValues->addExperimentalProperty("","dna_comp_armor_kinetic",calcResistMin(kinetic,modifier),kinetic,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_blast",calcResistMin(blast,modifier),blast,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_energy",calcResistMin(energy,modifier),energy,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_heat",calcResistMin(heat,modifier),heat,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_cold",calcResistMin(cold,modifier),cold,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_electric",calcResistMin(electric,modifier),electric,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_acid",calcResistMin(acid,modifier),acid,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_stun",calcResistMin(stun,modifier),stun,0,true,CraftingManager::OVERRIDECOMBINE);
	craftingValues->addExperimentalProperty("","dna_comp_armor_saber",calcResistMin(saber,modifier),saber,0,true,CraftingManager::OVERRIDECOMBINE);

	craftingValues->setMaxPercentage("dna_comp_armor_kinetic",kinetic/100);
	craftingValues->setMaxPercentage("dna_comp_armor_blast",blast/100);
	craftingValues->setMaxPercentage("dna_comp_armor_energy",energy/100);
	craftingValues->setMaxPercentage("dna_comp_armor_heat",heat/100);
	craftingValues->setMaxPercentage("dna_comp_armor_cold",cold/100);
	craftingValues->setMaxPercentage("dna_comp_armor_electric",electric/100);
	craftingValues->setMaxPercentage("dna_comp_armor_acid",acid/100);
	craftingValues->setMaxPercentage("dna_comp_armor_stun",stun/100);
	craftingValues->setMaxPercentage("dna_comp_armor_saber",saber/100);

	if (kinetic > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_kinetic",calcResistMin(kinetic,modifier)/kinetic);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_kinetic",kinetic/100);
	if (blast > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_blast",calcResistMin(blast,modifier)/blast);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_blast",blast/100);
	if (energy > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_energy",calcResistMin(energy,modifier)/energy);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_energy",energy/100);
	if (heat > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_heat",calcResistMin(heat,modifier)/heat);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_heat",heat/100);
	if (cold > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_cold",calcResistMin(cold,modifier)/cold);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_cold",cold/100);
	if (electric > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_electric",calcResistMin(electric,modifier)/electric);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_electric",electric/100);
	if (acid > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_acid",calcResistMin(acid,modifier)/acid);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_acid",acid/100);
	if (stun > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_stun",calcResistMin(stun,modifier)/stun);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_stun",stun/100);
	if (saber > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_saber",calcResistMin(saber,modifier)/saber);
	else
		craftingValues->setCurrentPercentage("dna_comp_armor_saber",saber/100);


	// Calc the max Percentage, vs Min Percentage
	craftingValues->setMaxPercentage("fortitude",calcMaxPercentage(fortMax));
	craftingValues->setCurrentPercentage("fortitude", getAssemblyPercentage(fortMin) * modifier);

	craftingValues->setMaxPercentage("hardiness",calcMaxPercentage(harMax));
	craftingValues->setCurrentPercentage("hardiness", getAssemblyPercentage(harMin) * modifier);

	craftingValues->setMaxPercentage("dexterity",calcMaxPercentage(dexMax));
	craftingValues->setCurrentPercentage("dexterity", getAssemblyPercentage(dexMin) * modifier);

	craftingValues->setMaxPercentage("endurance",calcMaxPercentage(endMax));
	craftingValues->setCurrentPercentage("endurance", getAssemblyPercentage(endMin) * modifier);

	craftingValues->setMaxPercentage("intellect",calcMaxPercentage(intMax));
	craftingValues->setCurrentPercentage("intellect", getAssemblyPercentage(intMin) * modifier);

	craftingValues->setMaxPercentage("cleverness",calcMaxPercentage(cleMax));
	craftingValues->setCurrentPercentage("cleverness", getAssemblyPercentage(cleMin) * modifier);

	craftingValues->setMaxPercentage("dependability",calcMaxPercentage(depMax));
	craftingValues->setCurrentPercentage("dependability", getAssemblyPercentage(depMin) * modifier);

	craftingValues->setMaxPercentage("courage",calcMaxPercentage(couMax));
	craftingValues->setCurrentPercentage("courage",getAssemblyPercentage(couMin) * modifier);

	craftingValues->setMaxPercentage("fierceness",calcMaxPercentage(fieMax));
	craftingValues->setCurrentPercentage("fierceness",getAssemblyPercentage(fieMin) * modifier);

	craftingValues->setMaxPercentage("power",calcMaxPercentage(powMax));
	craftingValues->setCurrentPercentage("power", getAssemblyPercentage(powMin) * modifier);

	// Figure out the min percentage of the stats

	int quality = (phy->getQuality() + pro->getQuality() + men->getQuality() + psy->getQuality() + agr->getQuality()) / 5;
	bool ranged = false;
	int odds = 0;
	float menQual = 7 - men->getQuality();
	float psyQual = 7 - psy->getQuality();
	if (men->isRanged() || psy->isRanged()) {
		int chance = System::random(100 - (assemblySuccess * 10)); // so amazing success 100, critical falure is 20
		// did you roll exceed (7 - Quality) * 10 (VHQ is 0) so always works
		if (chance > (menQual * 10) || chance > (psyQual * 10))
			ranged = true;
	}
	odds = men->getQuality() * 100;
	// check for specials here, then we have base assemble work completed.
	// update crafting values, and/or experimentRow should handle resist calc changes. update crafting values should determine armor setup
	String sp1 = pickSpecialAttack(agr->getSpecialAttackOne(),psy->getSpecialAttackOne(),phy->getSpecialAttackOne(),men->getSpecialAttackOne(),pro->getSpecialAttackOne(),odds);
	String sp2 = pickSpecialAttack(psy->getSpecialAttackTwo(),pro->getSpecialAttackTwo(),agr->getSpecialAttackTwo(),men->getSpecialAttackTwo(),phy->getSpecialAttackTwo(),odds);
	genetic->setSpecialAttackOne(sp1);
	genetic->setSpecialAttackTwo(sp2);
	genetic->setRanged(ranged);
	genetic->setQuality(quality);
	craftingValues->recalculateValues(true);

}

void GeneticLabratory::initialize(ZoneServer* server) {
	SharedLabratory::initialize(server);

}

bool GeneticLabratory::allowFactoryRun(ManufactureSchematic* manufactureSchematic) {
	return false;
}

void GeneticLabratory::experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult){
	float modifier, newValue, valA, valB;
	String title, subtitle, subtitlesTitle;
	title = craftingValues->getVisibleExperimentalPropertyTitle(rowEffected);
	modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);

	for (int i = 0; i < craftingValues->getExperimentalPropertySubtitleSize(); ++i) {
		subtitlesTitle = craftingValues->getExperimentalPropertySubtitlesTitle(i);
		if (subtitlesTitle == title) {
			subtitle = craftingValues->getExperimentalPropertySubtitle(i);
			modifier = calculateExperimentationValueModifier(experimentationResult,pointsAttempted);
			newValue = craftingValues->getCurrentPercentage(subtitle) + modifier;

			if (newValue >= craftingValues->getMaxPercentage(subtitle))
				newValue = craftingValues->getMaxPercentage(subtitle);

			if (newValue <= 0)
				newValue = 0;

			craftingValues->setCurrentPercentage(subtitle, newValue);
		}
	}

	// bump the resists up
	if (craftingValues->getMaxValue("dna_comp_armor_kinetic") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_kinetic",craftingValues->getCurrentPercentage("dna_comp_armor_kinetic") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_blast") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_blast",craftingValues->getCurrentPercentage("dna_comp_armor_blast") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_energy") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_energy",craftingValues->getCurrentPercentage("dna_comp_armor_energy") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_heat") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_heat",craftingValues->getCurrentPercentage("dna_comp_armor_heat") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_cold") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_cold",craftingValues->getCurrentPercentage("dna_comp_armor_cold") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_electric") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_electric",craftingValues->getCurrentPercentage("dna_comp_armor_electric") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_acid") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_acid",craftingValues->getCurrentPercentage("dna_comp_armor_acid") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_stun") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_stun",craftingValues->getCurrentPercentage("dna_comp_armor_stun") + modifier);
	if (craftingValues->getMaxValue("dna_comp_armor_saber") > 0)
		craftingValues->setCurrentPercentage("dna_comp_armor_saber",craftingValues->getCurrentPercentage("dna_comp_armor_saber") + modifier);
}
