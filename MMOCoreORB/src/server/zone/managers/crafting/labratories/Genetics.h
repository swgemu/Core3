#ifndef GENETICS_H_
#define GENETICS_H_

#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "templates/params/creature/CreatureFlag.h"

namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

//#define DEBUG_GENETIC_LAB

class Genetics {
private:
	const static short PHYSIQUE = 0;
	const static short PROWESS = 1;
	const static short MENTAL = 2;
	const static short AGRESSION = 3;
	const static short PHYSCHOLOGICAL = 4;
public:
	Genetics();
	virtual ~Genetics();

	const static constexpr float ACID_MAX = 100.0f;
	const static constexpr float BLAST_MAX = 100.0f;
	const static constexpr float COLD_MAX = 100.0f;
	const static constexpr float ELECTRICITY_MAX = 100.0f;
	const static constexpr float ENERGY_MAX = 60.0f;
	const static constexpr float HEAT_MAX = 100.0f;
	const static constexpr float KINETIC_MAX = 60.0f;
	const static constexpr float STUN_MAX = 100.0f;
	//const static constexpr float LIGHTSABER_MAX = 100.f;


	// Hardiness and Fortiture
	static float physiqueFormula(float physique, float prowess, float mental, float psychology, float aggression) {
		float result = (physique * 0.4f) + (prowess * 0.25f) + (mental * 0.05f) + (psychology * 0.05f) + (aggression * 0.25f);
		return result > 1000 ? 1000.0f : result < 0 ? 0.f : result;
	}

	// Dexterity and Endurance
	static float prowessFormula(float physique, float prowess, float mental, float psychology, float aggression) {
		float result = (physique * 0.25f) + (prowess * 0.42f) + (mental * 0.17f) + (psychology * 0.085f) + (aggression * 0.075f);
		return result > 1000 ? 1000.0f : result < 0 ? 0.f : result;
	}

	// Intellect and Cleverness
	static float mentalFormula(float physique, float prowess, float mental, float psychology, float aggression) {
		float result = (physique * 0.05f) + (prowess * 0.1f) + (mental * 0.5f) + (psychology * 0.3f) + (aggression * 0.05f);
		return result > 1000 ? 1000.0f : result < 0 ? 0.f : result;
	}

	// Dependability and Courage
	static float physchologicalFormula(float physique, float prowess, float mental, float psychology, float aggression) {
		float result = (physique * 0.09f) + (prowess * 0.05f) + (mental * 0.26f) + (psychology * 0.43f) + (aggression * 0.17f);
		return result > 1000 ? 1000.0f : result < 0 ? 0.f : result;
	}

	// Fierceness and Power
	static float aggressionFormula(float physique, float prowess, float mental, float psychology, float aggression) {
		float result = (physique * 0.17f) + (prowess * 0.16f) + (mental * 0.085f) + (psychology * 0.165f) + (aggression * 0.42f);
		return result > 1000 ? 1000.0f : result < 0 ? 0.f : result;
	}

	// Experimenting
	static float experimentFormula(float a, float b) {
		float multiplier = 140.0f;
		return ((a / (a + b) * multiplier));
	}

	static float determineMaxExperimentation(float min, float max) {
		return ceil((max / 10.0f) * .01f); // deterine max percentage. we will lock the stats each round after experimentation to handle adjustment our selves.
	}

	/**
	 * Genetic experiments differently, we have know formula increase per point spent.
	 * so we can calculate the max points possible for any given stat they arent as linear as resource items are.
	 */
	// demo 2,342,14
	static float maxExperimentationPercentage(float a, float b, float aMax, float bMax) {
		int count = 1;
		float workingA = a;
		float workingB = b;
		int aCount = 0;
		int bCount = 0;
		// max possible points in a given row is 10 i.e. 100%
		while ((workingA < aMax || workingB < bMax) && count < 11) {
			float wa = workingA;
			float wb = workingB;
			workingA += experimentFormula(wb, wa);
			workingB += experimentFormula(wa, wb);
			if (workingB > bMax) {
				bCount = count;
				workingB = bMax;
			}
			if (workingA > aMax) {
				aCount = count;
				workingA = aMax;
			}
			if (workingA == aMax && workingB == bMax) {
				count = 11;
			}
			count++;
		}
		// We know the min and max of each one, cal the % diff, and pick highest
		// float maxApercent = 100.00/(aMax/a);
		// float maxBpercent = 100.0/(bMax/b);
		// However each exp point will move it up by a chunk. soooooo good = 1 point in the given formula
		// we should now have the run to the max for both a and b, so determine the highest
		// if we say 14 rounds needed the max percentage would be: 14/10 = 1.4 or 140% or 100% normalized
		float maxACount = aCount / 10.0f;
		float maxBCount = bCount / 10.0f;
		float maxCount = maxACount > maxBCount ? maxACount : maxBCount;
		return maxCount > 1 ? 1 : maxCount;
	}

	/**
	 * Any special in the line
	 */
	static bool hasSpecialResist(DnaComponent* componentA, DnaComponent* componentB, DnaComponent* componentC, DnaComponent* componentD, DnaComponent* componentE, int type) {
		return componentA->isSpecialResist(type) || componentB->isSpecialResist(type) || componentC->isSpecialResist(type) || componentD->isSpecialResist(type) || componentE->isSpecialResist(type);
	}

	/**
	 * Any vulnerability int he line
	 */
	static bool hasVulnerability(float a, float b, float c, float d, float e) {
		return a < 0 || b < 0 || c < 0 || d < 0 || e < 0;
	}

	/*
		Get proper resistance for calculation
	*/
	static float getProperResistance(float value, bool special, bool override) {
#ifdef DEBUG_GENETIC_LAB
		Logger::console.info(true) << "---- GetProper Resistance -- Start Value: " << value << " -----";

		if (special)
			Logger::console.info(true) << "  Special Resist Type = TRUE";
		if (override)
			Logger::console.info(true) << "  Override By Resist = TRUE";
#endif
		// Override - Special or Vuln resistance. Special Resistance uses its value directly. Vulnerable acts as special resist of -99.f.
		if (override) {
			// Vulnerable Resist
			if (value < 0.f) {
				value = -99.f;
			// Effective Resist, overwritten to 0.f
			} else if (!special) {
				value = 0.f;
			}
		} // else - Effective Resist not overwritten by Special or Vulnerable Resist or Special Resist

#ifdef DEBUG_GENETIC_LAB
		Logger::console.info(true) << "---- END Get Proper Resistance -- Value: " << value << " -----";
#endif

		return value;
	}

	/**
	 * Resistnce calculation formula
	 */
	static float resistanceFormula(DnaComponent* componentA, DnaComponent* componentB, DnaComponent* componentC, DnaComponent* componentD, DnaComponent* componentE, int type, int max) {
#ifdef DEBUG_GENETIC_LAB
		Logger::console.info(true) << "resistanceFormula -- Type: " << type << " Max: " << max;
#endif

		/*
			 Special and Vulnerable Resistances will nullify effective resists making them count as 0 towards the calculation.
			 Vulnerable resistances are handled as special but as -99.f.
		*/

		float aValue = 0.0f, bValue = 0.0f, cValue = 0.0f, dValue = 0.0f, eValue = 0.0f;
		bool override = false;

		switch (type) {
		case SharedWeaponObjectTemplate::ACID:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Acid - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getAcid(), componentB->getAcid(), componentC->getAcid(), componentD->getAcid(), componentE->getAcid());
			aValue = getProperResistance(componentA->getAcid(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getAcid(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getAcid(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getAcid(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getAcid(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::BLAST:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Blast - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getBlast(), componentB->getBlast(), componentC->getBlast(), componentD->getBlast(), componentE->getBlast());
			aValue = getProperResistance(componentA->getBlast(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getBlast(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getBlast(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getBlast(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getBlast(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::COLD:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Cold - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getCold(), componentB->getCold(), componentC->getCold(), componentD->getCold(), componentE->getCold());
			aValue = getProperResistance(componentA->getCold(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getCold(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getCold(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getCold(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getCold(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::ELECTRICITY:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Electricity - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getElectric(), componentB->getElectric(), componentC->getElectric(), componentD->getElectric(), componentE->getElectric());
			aValue = getProperResistance(componentA->getElectric(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getElectric(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getElectric(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getElectric(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getElectric(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::ENERGY:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Energy - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getEnergy(), componentB->getEnergy(), componentC->getEnergy(), componentD->getEnergy(), componentE->getEnergy());
			aValue = getProperResistance(componentA->getEnergy(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getEnergy(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getEnergy(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getEnergy(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getEnergy(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::HEAT:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Heat - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getHeat(), componentB->getHeat(), componentC->getHeat(), componentD->getHeat(), componentE->getHeat());
			aValue = getProperResistance(componentA->getHeat(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getHeat(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getHeat(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getHeat(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getHeat(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::KINETIC:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Kinetic - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getKinetic(), componentB->getKinetic(), componentC->getKinetic(), componentD->getKinetic(), componentE->getKinetic());
			aValue = getProperResistance(componentA->getKinetic(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getKinetic(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getKinetic(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getKinetic(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getKinetic(), componentE->isSpecialResist(type), override);
			break;
		case SharedWeaponObjectTemplate::STUN:
#ifdef DEBUG_GENETIC_LAB
			Logger::console.info(true) << " - Stun - ";
#endif
			override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getStun(), componentB->getStun(), componentC->getStun(), componentD->getStun(), componentE->getStun());
			aValue = getProperResistance(componentA->getStun(), componentA->isSpecialResist(type), override);
			bValue = getProperResistance(componentB->getStun(), componentB->isSpecialResist(type), override);
			cValue = getProperResistance(componentC->getStun(), componentC->isSpecialResist(type), override);
			dValue = getProperResistance(componentD->getStun(), componentD->isSpecialResist(type), override);
			eValue = getProperResistance(componentE->getStun(), componentE->isSpecialResist(type), override);
			break;
			/*case SharedWeaponObjectTemplate::LIGHTSABER:
	#ifdef DEBUG_GENETIC_LAB
				Logger::console.info(true) << " - Lightsaber - ";
	#endif
				override = hasSpecialResist(componentA, componentB, componentC, componentD, componentE, type) || hasVulnerability(componentA->getSaber(), componentB->getSaber(), componentC->getSaber(), componentD->getSaber(), componentE->getSaber());
				aValue = getProperResistance(componentA->getSaber(), componentA->isSpecialResist(type), override);
				bValue = getProperResistance(componentB->getSaber(), componentB->isSpecialResist(type), override);
				cValue = getProperResistance(componentC->getSaber(), componentC->isSpecialResist(type), override);
				dValue = getProperResistance(componentD->getSaber(), componentD->isSpecialResist(type), override);
				eValue = getProperResistance(componentE->getSaber(), componentE->isSpecialResist(type), override);
				break;*/
		}


		float result = (aValue * 0.4) + (bValue * 0.25) + (cValue * 0.05) + (dValue * 0.05) + (eValue * 0.25);
		result = (result > max) ? max : result;

#ifdef DEBUG_GENETIC_LAB
		Logger::console.info(true) << "Component A: " << aValue << " Component B: " << bValue << " Component C: " << cValue << " Component D: " << dValue << " Component E: " << eValue;
		Logger::console.info(true) << "Resistance Value Returned: " << result;
#endif

		return result;
	}

	static float initialValue(float maxValue) {
		return (maxValue * ((maxValue / 1000.0f) + 0.15f));
	}

	static float determineMinResistance(float input) {
		if (input < 0) // if max is vulnerable the min is always vulnerable
			return -100;
		return round(input * ((input / 100.0f) + 0.15f));
	}

	static int randomizeValue(int value, int quality) {
		int wQuality = 8 - quality; // reverse range this is not the first time.
		int min = (value) + ((wQuality - 5) * 5);
		int max = (value) + ((wQuality - 3) * 5);
		return (int)(System::random(max - min) + min);
	}
	/**
	 * New Genetics Code - washu 03/08/15
	 */
	// convert creature hit chance to cleverness value
	static int hitChanceToValue(float input, int quality) {
		int base = round(((input - 0.19) / (0.66)) * 1000.0);
		return randomizeValue(base, quality);
	}

	// convert creature damage range to power score
	static int damageToValue(float dps, int quality) {
		int base = round(((dps - 15.0) / (725.0)) * 1000.0);
		return randomizeValue(base, quality);
	}

	// convert ham value to score
	static int hamToValue(float ham, int quality) {
		int base = round(((ham - 50.0) / (17950)) * 1000.0);
		return randomizeValue(base, quality);
	}

	// convert ferocity value
	static int ferocityToValue(int level, int quality) {
		int base = (level * 45) + 90;
		return randomizeValue(base, quality);
	}

	// convert acceletation
	static int accelerationToValue(float speed, int quality) {
		int base = round(((speed - 1.0) / (4.0)) * 1000.0);
		return randomizeValue(base, quality);
	}

	// convert meat type to value
	static int meatTypeToValue(String type, int quality) {
		return randomizeValue(500, quality);
	}

	// convert diet to value
	static int dietToValue(int diet, int quality) {
		/*int min = 0.1;
		int max = 9.3;*///these are not used, also 9.3 is not an int
		int base = 0;
		double level = 0;
		if (diet != CreatureFlag::HERBIVORE) {
			level = 8 / 1.701;
		} else {
			level = 7.0;
		}
		/*if (level == 0 ){ //cant be 0 as per above code
			level = 1.0;
		}*/
		base = round(((level - 0.1) / (9.2)) * 1000.0);
		return randomizeValue(base, quality);
	}

	// convert resistance to value
	static float resistanceToValue(float effective, int armor, int quality) {
		// find effective resist
		int base = effective * 10;
		int rand = randomizeValue(base, quality);
		if (rand < 0)
			rand = 0;
		if (armor > 0)
			rand += 500;
		return rand;
	}

	// level factor rules
	static float calculateArmorLevel(float armorBase) {
		return DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, armorBase);
	}
	// dps to level range
	static float calculateDPSLevel(float maxDamage, float minDamage) {
		float dps = (maxDamage + minDamage) / 2;
		return DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, dps);
	}
	// ham level
	static float calculateHamLevel(float ham) {
		return DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, ham);
	}
	// regen level
	static float calculatRegenLevel(float regen) {
		return DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL, regen);
	}
	// hit level
	static float calculatHitLevel(float toHit) {
		return DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL, toHit);
	}

	// calculate the resistance level modifier
	static int resistMath(int input, int rating, int effectiveness, bool multiply, int multValue, int lowValue) {
		int rValue = rating * 25;
		int eValue = (effectiveness / (rating + 1));
		if (input > 0) {
			if (multiply) {
				return Math::max((input - (rValue + eValue)), 0) * multValue;
			} else {
				return Math::max((input - (rValue + eValue)), 0) / multValue;
			}
		} else {
			if (lowValue == 1) {
				return input * (rValue + eValue);
			} else {
				return input * (rValue + eValue) * lowValue;
			}
		}
	}

	// calculate the armor level for a pet
	static int calculateArmorValue(GeneticComponent* pet, int armorLevel, int baseLevel, int armorBase) {
		// Armor Level
		int level = armorLevel + 1;
		if (level < baseLevel)
			level = baseLevel;
		int eff = armorBase / 50;
		if (armorBase > 500)
			eff = (armorBase - 500) / 50;
		if (armorBase == 500)
			eff = 0;
		int armorRating = pet->getArmor();
		int resistanceLevel = 0;
		resistanceLevel += resistMath(pet->getKinetic(), armorRating, eff, true, 3, 6);
		resistanceLevel += resistMath(pet->getEnergy(), armorRating, eff, true, 3, 6);
		resistanceLevel += resistMath(pet->getBlast(), armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(pet->getHeat(), armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(pet->getCold(), armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(pet->getElectrical(), armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(pet->getAcid(), armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(pet->getStun(), armorRating, eff, false, 2.0, 1);
		level += ((float)resistanceLevel) / 10.0;
		return level;
	}
	static int calcArmorLevelByStats(int armorRating, int armorLevel, int baseLevel, int armorBase, float kinetic, float energy, float blast, float heat, float cold, float electricity, float acid, float stun) {
		int level = armorLevel + 1;
		if (level < baseLevel)
			level = baseLevel;
		int eff = armorBase / 50;
		if (armorBase > 500)
			eff = (armorBase - 500) / 50;
		if (armorBase == 500)
			eff = 0;
		int resistanceLevel = 0;
		resistanceLevel += resistMath(kinetic, armorRating, eff, true, 3, 6);
		resistanceLevel += resistMath(energy, armorRating, eff, true, 3, 6);
		resistanceLevel += resistMath(blast, armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(heat, armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(cold, armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(electricity, armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(acid, armorRating, eff, false, 2.0, 1);
		resistanceLevel += resistMath(stun, armorRating, eff, false, 2.0, 1);
		level += ((float)resistanceLevel) / 10.0;
		return level;
	}
	static int generateStatLevel(int health) {
		return (DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, health) + 1) * 6;
	}
	static int generateDamageLevel(float dps) {
		return DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, dps) * 10;
	}
	static int generateHitLevel(float hitChance) {
		return (DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL, hitChance) + 1) * 1;
	}
	static int generateRegenLevel(int hamRegen) {
		return (DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL, hamRegen / 10) + 1) * 2;
	}
	static int generteArmorLevel(int armor, float effectResist) {
		return DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, (armor * 500) + ((effectResist)*10.0));
	}
	static int generateArmorBaseLevel(int generatedArmorLevel) {
		return DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL, generatedArmorLevel);
	}
	static int generateBaseLevel(int statLevel, int damageLevel, int armorLevel, int regenLevel, int hitLevel) {
		return (((statLevel) + (damageLevel) + (regenLevel) + (hitLevel)) / 19.0) + 0.5;
	}
	static int calculateAgentLevel(int health, float dps, float hit, int regen, int armor, float effective, float kin, float eng, float bla, float heat, float cold, float elec, float acid, float stun) {
		int statLevel = generateStatLevel(health);
		int damageLevel = generateDamageLevel(dps);
		int hitLevel = generateHitLevel(hit);
		int defenseLevel = hitLevel;
		int regenerationLevel = generateRegenLevel(regen);
		int armorLevel = generteArmorLevel(armor, effective);
		int armorBase = DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL, armorLevel);
		int baseLevel = (((statLevel) + (damageLevel) + (regenerationLevel) + (hitLevel)) / 19.0) + 0.5;
		int armorLevel2 = calcArmorLevelByStats(armor, armorLevel, baseLevel, armorBase, kin, eng, bla, heat, cold, elec, acid, stun) * 2;
		if (defenseLevel < baseLevel)
			defenseLevel = baseLevel;
		int level = round((((float)(statLevel + damageLevel + hitLevel + defenseLevel + armorLevel + regenerationLevel)) / 22.0) + 0.5);
		return level;
	}
	// Calculate the creatures overall level as a pet.
	static int calculatePetLevel(GeneticComponent* pet) {
		// reverse the values out.
		int avgHam = (pet->getHealth() + pet->getAction() + pet->getMind()) / 3;
		int statLevel = (DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, avgHam) + 1) * 6;
		int damageLevel = DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, ((pet->getMaxDamage() + pet->getMinDamage()) / 2.0f) / pet->getSpeed()) * 10;
		int hitLevel = (DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL, pet->getHit()) + 1) * 1;
		int defenseLevel = hitLevel;
		int regenerationLevel = (DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL, avgHam / 10) + 1) * 2;
		int armorLevel = DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, (pet->getArmor() * 500) + ((pet->getEffectiveArmor()) * 10.0));
		int armorBase = DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL, armorLevel);
		int baseLevel = (((statLevel) + (damageLevel) + (regenerationLevel) + (hitLevel)) / 19.0) + 0.5;
		int armorLevel2 = calculateArmorValue(pet, armorLevel, baseLevel, armorBase) * 2;
		if (defenseLevel < baseLevel)
			defenseLevel = baseLevel;
		int level = round((((float)(statLevel + damageLevel + hitLevel + defenseLevel + armorLevel + regenerationLevel)) / 22.0) + 0.5);
		return level;
	}

	// Calculate the input creature levels
	static int levelForCreature(Creature* creature) {
		return creature->getLevel();
	}
};

} // namespace labratories
} // namespace crafting
} // namespace managers
} // namespace zone
} // namespace server

using namespace server::zone::managers::crafting::labratories;

#endif /* GENETICS_H_ */
