#ifndef GENETICS_H_
#define GENETICS_H_

#include "SharedLabratory.h"
#include "engine/engine.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "server/zone/objects/creature/CreatureFlag.h"
namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

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

	static float physiqueFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.4) + (b *0.25) + (c * 0.05) + (d * 0.05) + (e * 0.25));
		return rc > 1000 ? 1000.0 : rc < 0 ? 0 : rc;
	}

	static float prowessFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.25) + (b *0.42) + (c * 0.17) + (d * 0.085) + (e * .075));
		return rc > 1000 ? 1000.0 : rc < 0 ? 0 : rc;
	}

	static float mentalFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.05) + (b *0.1) + (c * 0.5) + (d * 0.3) + (e * .05));
		return rc > 1000 ? 1000.0 : rc < 0 ? 0 : rc;
	}

	static float aggressionFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.17) + (b *0.16) + (c * 0.085) + (d * 0.165) + (e * 0.42));
		return rc > 1000 ? 1000.0 : rc < 0 ? 0 : rc;
	}

	static float physchologicalFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.09) + (b *0.05) + (c * 0.26) + (d * 0.43) + (e * 0.17));
		return rc > 1000 ? 1000.0 : rc < 0 ? 0 : rc;
	}

	static float experimentFormula(float a, float b) {
		float multiplier = 140.0;
		return (round( (a/(a+b)*multiplier)));
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
		while( (workingA < aMax || workingB < bMax) && count < 11) {
			float wa = workingA;
			float wb = workingB;
			workingA += experimentFormula(wb,wa);
			workingB += experimentFormula(wa,wb);
			if (workingB > bMax) {
				bCount = count;
				workingB = bMax;
			}
			if (workingA > aMax) {
				aCount = count;
				workingA = aMax;
			}
			if (workingA == aMax && workingB == bMax){
				count = 11;
			}
			count++;
		}
		// We know the min and max of each one, cal the % diff, and pick highest
		//float maxApercent = 100.00/(aMax/a);
		//float maxBpercent = 100.0/(bMax/b);
		// However each exp point will move it up by a chunk. soooooo good = 1 point in the given formula
		// we should now have the run to the max for both a and b, so determine the highest
		// if we say 14 rounds needed the max percentage would be: 14/10 = 1.4 or 140% or 100% normalized
		float maxACount = aCount/10.0f;
		float maxBCount = bCount/10.0f;
		float maxCount = maxACount > maxBCount ? maxACount : maxBCount;
		return maxCount > 1 ? 1 : maxCount;
	}

	/**
	 * Any special in the line
	 */
	static bool hasASpecial(DnaComponent* a, DnaComponent* b, DnaComponent* c, DnaComponent* d, DnaComponent* e,int type) {
		return a->isSpecialResist(type) || b->isSpecialResist(type) || c->isSpecialResist(type) || d->isSpecialResist(type) || e->isSpecialResist(type);
	}

	/**
	 * Any vulnerability int he line
	 */
	static bool hasVulnerability(float a, float b, float c, float d, float e) {
		return a < 0 || b < 0 || c < 0 || d < 0 || e < 0;
	}

	/**
	 * Normlaize a vlaue for resist cals
	 */
	static float normalize(float a,bool special, bool override) {
		if(a < 0)
			return -100;
		if (special) {
			return a;
		}
		if (override) {
			return 0;
		}
		return a;
	}

	/**
	 * Resistnce calculation formula
	 */
	static float resistanceFormula(DnaComponent* a, DnaComponent* b, DnaComponent* c, DnaComponent* d, DnaComponent* e, int type, int max) {
		float av = 0, bv = 0, cv = 0, dv = 0, ev = 0;
		bool any = false;
		switch(type) {
			case WeaponObject::ACID:
				any = hasASpecial(a,b,c,d,e,type) || hasVulnerability(a->getAcid(),b->getAcid(),c->getAcid(), d->getAcid(), e->getAcid());
				av = normalize(a->getAcid(),a->isSpecialResist(type),any);
				bv = normalize(b->getAcid(),b->isSpecialResist(type),any);
				cv = normalize(c->getAcid(),c->isSpecialResist(type),any);
				dv = normalize(d->getAcid(),d->isSpecialResist(type),any);
				ev = normalize(e->getAcid(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::BLAST:
				any = hasASpecial(a,b,c,d,e,type) || hasVulnerability(a->getBlast(),b->getBlast(),c->getBlast(), d->getBlast(), e->getBlast());
				av = normalize(a->getBlast(),a->isSpecialResist(type),any);
				bv = normalize(b->getBlast(),b->isSpecialResist(type),any);
				cv = normalize(c->getBlast(),c->isSpecialResist(type),any);
				dv = normalize(d->getBlast(),d->isSpecialResist(type),any);
				ev = normalize(e->getBlast(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::COLD:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getCold(),b->getCold(),c->getCold(), d->getCold(), e->getCold());
				av = normalize(a->getCold(),a->isSpecialResist(type),any);
				bv = normalize(b->getCold(),b->isSpecialResist(type),any);
				cv = normalize(c->getCold(),c->isSpecialResist(type),any);
				dv = normalize(d->getCold(),d->isSpecialResist(type),any);
				ev = normalize(e->getCold(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::ELECTRICITY:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getElectric(),b->getElectric(),c->getElectric(), d->getElectric(), e->getElectric());
				av = normalize(a->getElectric(),a->isSpecialResist(type),any);
				bv = normalize(b->getElectric(),b->isSpecialResist(type),any);
				cv = normalize(c->getElectric(),c->isSpecialResist(type),any);
				dv = normalize(d->getElectric(),d->isSpecialResist(type),any);
				ev = normalize(e->getElectric(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::ENERGY:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getEnergy(),b->getEnergy(),c->getEnergy(), d->getEnergy(), e->getEnergy());
				av = normalize(a->getEnergy(),a->isSpecialResist(type),any);
				bv = normalize(b->getEnergy(),b->isSpecialResist(type),any);
				cv = normalize(c->getEnergy(),c->isSpecialResist(type),any);
				dv = normalize(d->getEnergy(),d->isSpecialResist(type),any);
				ev = normalize(e->getEnergy(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::HEAT:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getHeat(),b->getHeat(),c->getHeat(), d->getHeat(), e->getHeat());
				av = normalize(a->getHeat(),a->isSpecialResist(type),any);
				bv = normalize(b->getHeat(),b->isSpecialResist(type),any);
				cv = normalize(c->getHeat(),c->isSpecialResist(type),any);
				dv = normalize(d->getHeat(),d->isSpecialResist(type),any);
				ev = normalize(e->getHeat(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::KINETIC:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getKinetic(),b->getKinetic(),c->getKinetic(), d->getKinetic(), e->getKinetic());
				av = normalize(a->getKinetic(),a->isSpecialResist(type),any);
				bv = normalize(b->getKinetic(),b->isSpecialResist(type),any);
				cv = normalize(c->getKinetic(),c->isSpecialResist(type),any);
				dv = normalize(d->getKinetic(),d->isSpecialResist(type),any);
				ev = normalize(e->getKinetic(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::LIGHTSABER:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getSaber(),b->getSaber(),c->getSaber(), d->getSaber(), e->getSaber());
				av = normalize(a->getSaber(),a->isSpecialResist(type),any);
				bv = normalize(b->getSaber(),b->isSpecialResist(type),any);
				cv = normalize(c->getSaber(),c->isSpecialResist(type),any);
				dv = normalize(d->getSaber(),d->isSpecialResist(type),any);
				ev = normalize(e->getSaber(),e->isSpecialResist(type),any);
				break;
		}
		float value = ceil((av * 0.41) + (bv *0.25) + (cv * 0.04) + (dv * 0.04) + (ev * 0.25));
		return value > max ? max : value;
	}

	static uint32 initialValue(float maxValue) {
		return round(maxValue * ((maxValue/(float)1000)+0.15));
	}

	static float determineMinResistance(float input) {
		if (input < 0) // if max is vulnerable the min is always vulnerable
			return -100;
		return round(input * ((input/100.0f) + 0.15f));
	}
	static int randomizeValue(int value, int quality) {
		int wQuality = 8 - quality; // reverse range this is not the first time.
		int min = (value) + ((wQuality-5) * 5);
		int max = (value) + ((wQuality-3) * 5);
		return (int) (System::random(max-min) + min);
	}
	/**
	 * New Genetics Code - washu 03/08/15
	 */
	// convert creature hit chance to cleverness value
	static int hitChanceToValue(float input,int quality) {
		int base = round(((input-0.19)/(0.66)) * 1000.0);
		return randomizeValue(base,quality);
	}

	// convert creature damage range to power score
	static int damageToValue(float dps, int quality) {
		int base = round(((dps-15.0)/(725.0))*1000.0);
		return randomizeValue(base,quality);
	}

	// convert ham value to score
	static int hamToValue(float ham, int quality) {
		int base = round(((ham-50.0)/(17950)) * 1000.0);
		return randomizeValue(base,quality);
	}

	// convert ferocity value
	static int ferocityToValue(int level, int quality) {
		int base = (level * 45) + 90;
		return randomizeValue(base,quality);
	}

	// convert acceletation
	static int accelerationToValue(float speed, int quality) {
		int base = round(((speed-1.0)/(4.0)) * 1000.0);
		return randomizeValue(base,quality);
	}

	// convert meat type to value
	static int meatTypeToValue(String type, int quality) {
		return randomizeValue(500,quality);
	}

	// convert diet to value
	static int dietToValue(int diet, int quality) {
		int min = 0.1;
		int max = 9.3;
		int base = 0;
		int level = 0;
		if (diet != CreatureFlag::HERBIVORE) {
			level = 8/1.701;
		} else {
			level = 7.0;
		}
		if (level == 0 ){
			level = 1.0;
		}
		base = round(((level-0.1)/(9.2)) * 1000.0);
		return randomizeValue(base,quality);
	}

	// convert resistance to value
	static float resistanceToValue(float effective, int armor,int quality) {
		// find effective resist
		int base = effective * 10;
		int rand = randomizeValue(base,quality);
		if (rand < 0)
			rand = 0;
		if (armor > 0)
			rand += 500;
		return rand;
	}

	// level factor rules
	static float calculateArmorLevel(float armorBase) {
		return DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL,armorBase);
	}
	// dps to level range
	static float calculateDPSLevel(float maxDamage, float minDamage) {
		float dps = (maxDamage + minDamage)/2;
		return DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL,dps);
	}
	// ham level
	static float calculateHamLevel(float ham) {
		return DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL,ham);
	}
	// regen level
	static float calculatRegenLevel(float regen) {
		return DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL,regen);
	}
	// hit level
	static float calculatHitLevel(float toHit) {
		return DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL,toHit);
	}

	// calculate the resistance level modifier
	static int resistMath(int input, int rating, int effectiveness,bool multiply,int multValue, int lowValue) {
		int rValue = rating * 25;
		int eValue = ( effectiveness / (rating + 1));
		if(input > 0) {
			if (multiply) {
				return MAX((input - (rValue +eValue)),0) * multValue;
			} else {
				return MAX((input - (rValue +eValue)),0) / multValue;
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
		int eff = armorBase/50;
		if (armorBase > 500)
			eff = (armorBase-500)/50;
		if (armorBase == 500)
			eff = 0;
		int armorRating = pet->getArmor();
		int resistanceLevel = 0;
		resistanceLevel += resistMath(pet->getKinetic(),armorRating,eff,true,3,6);
		resistanceLevel += resistMath(pet->getEnergy(),armorRating,eff,true,3,6);
		resistanceLevel += resistMath(pet->getBlast(),armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(pet->getHeat(),armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(pet->getCold(),armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(pet->getElectrical(),armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(pet->getAcid(),armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(pet->getStun(),armorRating,eff,false,2.0,1);
		level += ((float) resistanceLevel) / 10.0;
		return level;
	}
	static int calcArmorLevelByStats(int armorRating, int armorLevel, int baseLevel, int armorBase, float kinetic, float energy, float blast, float heat, float cold, float electricity, float acid, float stun) {
		int level = armorLevel + 1;
		if (level < baseLevel)
			level = baseLevel;
		int eff = armorBase/50;
		if (armorBase > 500)
			eff = (armorBase-500)/50;
		if (armorBase == 500)
			eff = 0;
		int resistanceLevel = 0;
		resistanceLevel += resistMath(kinetic,armorRating,eff,true,3,6);
		resistanceLevel += resistMath(energy,armorRating,eff,true,3,6);
		resistanceLevel += resistMath(blast,armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(heat,armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(cold,armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(electricity,armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(acid,armorRating,eff,false,2.0,1);
		resistanceLevel += resistMath(stun,armorRating,eff,false,2.0,1);
		level += ((float) resistanceLevel) / 10.0;
		return level;

	}
	static int generateStatLevel(int health) {
		return (DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, health)+1) * 6;
	}
	static int generateDamageLevel(float dps) {
		return DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, dps) * 10;
	}
	static int generateHitLevel(float hitChance) {
		return (DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL,hitChance) + 1) * 1;
	}
	static int generateRegenLevel(int hamRegen) {
		return (DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL,hamRegen/10) + 1)* 2;
	}
	static int generteArmorLevel(int armor, float effectResist) {
		return DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, (armor * 500) + (( effectResist) * 10.0)  );
	}
	static int generateArmorBaseLevel(int generatedArmorLevel) {
		return DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL,generatedArmorLevel);
	}
	static int generateBaseLevel(int statLevel, int damageLevel, int armorLevel, int regenLevel, int hitLevel) {
		return (((statLevel) + (damageLevel) + (regenLevel) + (hitLevel)) / 19.0) + 0.5;
	}
	static int calculateAgentLevel(int health, float dps, float hit, int regen, int armor, float effective, float kin, float eng, float bla, float heat, float cold, float elec, float acid, float stun) {
		int statLevel = generateStatLevel(health);
		int damageLevel = generateDamageLevel(dps);
		int hitLevel = generateHitLevel(hit);
		int defenseLevel = hitLevel;
		int regenerationLevel =  generateRegenLevel(regen);
		int armorLevel = generteArmorLevel(armor,effective);
		int armorBase = DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL,armorLevel);
		int baseLevel = (((statLevel) + (damageLevel) + (regenerationLevel) + (hitLevel)) / 19.0) + 0.5;
		int armorLevel2 = calcArmorLevelByStats(armor,armorLevel,baseLevel,armorBase, kin,eng, bla,heat,cold,elec,acid,stun) * 2;
		if (defenseLevel < baseLevel)
			defenseLevel = baseLevel;
		int level = round((((float)(statLevel + damageLevel + hitLevel + defenseLevel + armorLevel + regenerationLevel ))/22.0) + 0.5);
		return level;
	}
	// Calculate the creatures overall level as a pet.
	static int calculatePetLevel(GeneticComponent* pet) {
		// reverse the values out.
		int statLevel = (DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, pet->getHealth())+1) * 6;
		int damageLevel = DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, (pet->getMaxDamage() + pet->getMinDamage()) / 2) * 10;
		int hitLevel = (DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL, pet->getHit()) + 1) * 1;
		int defenseLevel = hitLevel;
		int regenerationLevel =  (DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL,pet->getAction()/10) + 1)* 2;
		int armorLevel = DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, (pet->getArmor() * 500) + (( pet->getEffectiveArmor()) * 10.0)  );
		int armorBase = DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL,armorLevel);
		int baseLevel = (((statLevel) + (damageLevel) + (regenerationLevel) + (hitLevel)) / 19.0) + 0.5;
		int armorLevel2 = calculateArmorValue(pet, armorLevel, baseLevel, armorBase) * 2;
		if (defenseLevel < baseLevel)
			defenseLevel = baseLevel;
		int level = round((((float)(statLevel + damageLevel + hitLevel + defenseLevel + armorLevel + regenerationLevel ))/22.0) + 0.5);
		return level;
	}

	// Calculate the input creature levels
	static int levelForCreature(Creature* creature) {
		return creature->getLevel();
	}
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICS_H_ */
