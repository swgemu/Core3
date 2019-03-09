#ifndef GENETICS_H_
#define GENETICS_H_



#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/objects/tangible/component/genetic/GeneticComponent.h"
#include "templates/params/creature/CreatureFlag.h"
#include "system/lang.h"

#include "engine/log/Logger.h"
//remove after testing

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
	// added for Testing  Mar 2019

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
			case SharedWeaponObjectTemplate::ACID:
				any = hasASpecial(a,b,c,d,e,type) || hasVulnerability(a->getAcid(),b->getAcid(),c->getAcid(), d->getAcid(), e->getAcid());
				av = normalize(a->getAcid(),a->isSpecialResist(type),any);
				bv = normalize(b->getAcid(),b->isSpecialResist(type),any);
				cv = normalize(c->getAcid(),c->isSpecialResist(type),any);
				dv = normalize(d->getAcid(),d->isSpecialResist(type),any);
				ev = normalize(e->getAcid(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::BLAST:
				any = hasASpecial(a,b,c,d,e,type) || hasVulnerability(a->getBlast(),b->getBlast(),c->getBlast(), d->getBlast(), e->getBlast());
				av = normalize(a->getBlast(),a->isSpecialResist(type),any);
				bv = normalize(b->getBlast(),b->isSpecialResist(type),any);
				cv = normalize(c->getBlast(),c->isSpecialResist(type),any);
				dv = normalize(d->getBlast(),d->isSpecialResist(type),any);
				ev = normalize(e->getBlast(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::COLD:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getCold(),b->getCold(),c->getCold(), d->getCold(), e->getCold());
				av = normalize(a->getCold(),a->isSpecialResist(type),any);
				bv = normalize(b->getCold(),b->isSpecialResist(type),any);
				cv = normalize(c->getCold(),c->isSpecialResist(type),any);
				dv = normalize(d->getCold(),d->isSpecialResist(type),any);
				ev = normalize(e->getCold(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::ELECTRICITY:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getElectric(),b->getElectric(),c->getElectric(), d->getElectric(), e->getElectric());
				av = normalize(a->getElectric(),a->isSpecialResist(type),any);
				bv = normalize(b->getElectric(),b->isSpecialResist(type),any);
				cv = normalize(c->getElectric(),c->isSpecialResist(type),any);
				dv = normalize(d->getElectric(),d->isSpecialResist(type),any);
				ev = normalize(e->getElectric(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::ENERGY:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getEnergy(),b->getEnergy(),c->getEnergy(), d->getEnergy(), e->getEnergy());
				av = normalize(a->getEnergy(),a->isSpecialResist(type),any);
				bv = normalize(b->getEnergy(),b->isSpecialResist(type),any);
				cv = normalize(c->getEnergy(),c->isSpecialResist(type),any);
				dv = normalize(d->getEnergy(),d->isSpecialResist(type),any);
				ev = normalize(e->getEnergy(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::HEAT:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getHeat(),b->getHeat(),c->getHeat(), d->getHeat(), e->getHeat());
				av = normalize(a->getHeat(),a->isSpecialResist(type),any);
				bv = normalize(b->getHeat(),b->isSpecialResist(type),any);
				cv = normalize(c->getHeat(),c->isSpecialResist(type),any);
				dv = normalize(d->getHeat(),d->isSpecialResist(type),any);
				ev = normalize(e->getHeat(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::KINETIC:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getKinetic(),b->getKinetic(),c->getKinetic(), d->getKinetic(), e->getKinetic());
				av = normalize(a->getKinetic(),a->isSpecialResist(type),any);
				bv = normalize(b->getKinetic(),b->isSpecialResist(type),any);
				cv = normalize(c->getKinetic(),c->isSpecialResist(type),any);
				dv = normalize(d->getKinetic(),d->isSpecialResist(type),any);
				ev = normalize(e->getKinetic(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::LIGHTSABER:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getSaber(),b->getSaber(),c->getSaber(), d->getSaber(), e->getSaber());
				av = normalize(a->getSaber(),a->isSpecialResist(type),any);
				bv = normalize(b->getSaber(),b->isSpecialResist(type),any);
				cv = normalize(c->getSaber(),c->isSpecialResist(type),any);
				dv = normalize(d->getSaber(),d->isSpecialResist(type),any);
				ev = normalize(e->getSaber(),e->isSpecialResist(type),any);
				break;
			case SharedWeaponObjectTemplate::STUN:
				any = hasASpecial(a,b,c,d,e,type)|| hasVulnerability(a->getStun(),b->getStun(),c->getStun(), d->getStun(), e->getStun());
				av = normalize(a->getStun(),a->isSpecialResist(type),any);
				bv = normalize(b->getStun(),b->isSpecialResist(type),any);
				cv = normalize(c->getStun(),c->isSpecialResist(type),any);
				dv = normalize(d->getStun(),d->isSpecialResist(type),any);
				ev = normalize(e->getStun(),e->isSpecialResist(type),any);
				break;
		}
		float value = ceil((av * 0.40) + (bv *0.25) + (cv * 0.05) + (dv * 0.05) + (ev * 0.25));
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
		int min = (value) ; //+ ((wQuality-5) * 5); // loose the added part to min
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
		int base = round(((dps-15.0)/ 780.0)*1000.0); // was 725.0
		return randomizeValue(base,quality);
	}

	// convert ham value to score
	static int hamToValue(float ham, int quality) {
		int base = round(((ham-50.0)/(18500)) * 1000.0); // was 17950
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
		/*int min = 0.1;
		int max = 9.3;*///these are not used, also 9.3 is not an int
		int base = 0;
		double level = 0;
		if (diet != CreatureFlag::HERBIVORE) {
			level = 8/1.701;
		} else {
			level = 7.0;
		}
		/*if (level == 0 ){ //cant be 0 as per above code
			level = 1.0;
		}*/
		base = round(((level-0.1)/(9.2)) * 1000.0);
		return randomizeValue(base,quality);
	}

	// convert resistance to value
	static float resistanceToValue(float effective, int armor,int quality,int hardiness) {
		// find effective resist
		// add some fortitude to creatures with no resists
		if (effective <= 0.0) {
			if (hardiness > 1500) effective = hardiness * 0.02;
			else effective = hardiness * 0.01;
		}

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
				return Math::max((input - (rValue +eValue)),0) * multValue;
			} else {
				return Math::max((input - (rValue +eValue)),0) / multValue;
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
		return DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, health);
	}
	static int generateDamageLevel(float dps) {
		return DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, dps);
	}
	static int generateHitLevel(float hitChance) {
		return DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL,hitChance);
	}
	static int generateRegenLevel(int Regen) {
		return DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL,Regen);
	}
	static int generteArmorLevel(int armor, float effectResist) {
		return DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, (armor * 500) +  effectResist  );
	}
	/*static int generateArmorBaseLevel(int generatedArmorLevel) {
		return DnaManager::instance()->valueForLevel(DnaManager::ARM_LEVEL,generatedArmorLevel);
	}
	static int generateBaseLevel(int statLevel, int damageLevel, int armorLevel, int regenLevel, int hitLevel) {
		return ((statLevel) + (damageLevel) + (regenLevel) + (hitLevel)) ;
	} */
	static int calculateAgentLevel(int fortitude, int health, float dps, float hit, int regen, int armor, float effective, float kin, float eng, float bla, float heat, float cold, float elec, float acid, float stun) {
		//   Added proper regen formula to petdeedimplementation
		// added fortitude variable. wont use effective

		int pfort = fortitude , tarmor = 0,rfort = 0 ;
		float Psum = 0 , Nsum = 0;
		if ( pfort >= 500) {

			tarmor = 500;
			rfort = pfort - 500;
		}
		else
			if (pfort < 500)  {
				tarmor = pfort;
				rfort = pfort;
			}


		if (kin  >= 0) Psum = Psum + kin;  else Nsum = Nsum + kin;
		if (eng  >= 0) Psum = Psum + eng;  else Nsum = Nsum + eng;
		if (bla  >= 0) Psum = Psum + bla;  else Nsum = Nsum + bla;
		if (heat >= 0) Psum = Psum + heat; else Nsum = Nsum + heat;
		if (cold >= 0) Psum = Psum + cold; else Nsum = Nsum + cold;
		if (elec >= 0) Psum = Psum + elec; else Nsum = Nsum + elec;
		if (acid >= 0) Psum = Psum + acid; else Nsum = Nsum + acid;
		if (stun >= 0) Psum = Psum + stun; else Nsum = Nsum + stun;

			float modifier = rfort/8;
			Psum  = modifier * (Psum /100);
			tarmor = tarmor + Psum;
			Nsum  = (Nsum / 100)* modifier;

	        int parmor = 0;
	        parmor = tarmor + Nsum;

			if ( parmor >1) tarmor = tarmor + Nsum;
			// data table will return cl 14 if the armor is below 50  set it to 2
	        int armorLevel = 2;
	        // already have armor send 0 .
	        if (tarmor >= 50){
			 armorLevel =  generteArmorLevel(0,tarmor);
			}
			else
				if (tarmor < 50) {
					if (Nsum < -99) armorLevel= -3;
					else
					armorLevel = 0;

				}


		int statLevel = generateStatLevel(health);
		int damageLevel = generateDamageLevel(dps);
		int hitLevel = generateHitLevel(hit);
		int regenerationLevel =  generateRegenLevel(regen);
		int level = (statLevel + damageLevel + hitLevel  + armorLevel + regenerationLevel )/5;
		return level;

	}

	// Calculate the creatures overall level as a pet.
	static int calculatePetLevel(GeneticComponent* pet) {
		// code to allow for 10k cl 10
                int avgHam = 0;
                int health = 0 ,action = 0 , mind = 0;
                int value1 = 0, value2 = 0, value3 = 0, value4 =0;
		health =pet->getHealth(); action = pet->getAction(); mind = pet->getMind();
                // need to find the min and max	
		value1 = Math::min(health,action);
		value2 = Math::min(value1,mind);
		value1 = Math::max(health,action);
		value3 = Math::max(value1,mind);
		value4 = (value2 /3 ) + value2;
		//if the min /3 + min  is less than max use the mmin /3
		if ( value4 < value3) {
                 avgHam = value2 /3;
                }
                 else
                 avgHam = (pet->getHealth() + pet->getAction() + pet->getMind()) / 3;
		if (avgHam <75) avgHam = 75;

		// do the same for regen
        int regen =0;
        int will = 0 , stam = 0, cons = 0;
        will = pet->getWillPower(); stam = pet->getStamina(); cons =pet->getConstitution();

 		value1 = Math::min(will,stam);
 		value2 = Math::min(value1,cons);
 		value1 = Math::max(will,stam);
 		value3 = Math::max(value1,cons);
 		value4 = (value2 /3 ) + value2;
 		//if the min /3 + min  is less than max use the mmin /3
 		if ( value4 < value3) {
                  regen = (value2/10) /3;
                 }
                  else
                	  regen = floor(((pet->getWillPower() + pet->getStamina() + pet->getConstitution()) /10)/ 3);
 		if (regen < 7) regen =7;

		char str[50];
		sprintf(str,"Pet regen Passed %d",regen);
		Logger::console.info(str,true);
		sprintf(str,"Pet AvgHam Passed %d",avgHam);
		Logger::console.info(str,true);






		int statLevel = DnaManager::instance()->levelForScore(DnaManager::HAM_LEVEL, avgHam);
		int dps = ((pet->getMaxDamage() + pet->getMinDamage()) / 2.0f) / pet->getSpeed();
		int damageLevel = DnaManager::instance()->levelForScore(DnaManager::DPS_LEVEL, dps) ;
		int hitLevel = DnaManager::instance()->levelForScore(DnaManager::HIT_LEVEL, pet->getHit());
	    int regenerationLevel =  DnaManager::instance()->levelForScore(DnaManager::REG_LEVEL, regen);
		// this will get us to level 60 armor , need to figure out how to do the resists

		sprintf(str,"Pet DamageLevel Passed %d",damageLevel);
		Logger::console.info(str,true);
		sprintf(str,"Pet HitLevel Passed %d",hitLevel);
		Logger::console.info(str,true);
		sprintf(str,"Pet regenLevel Passed %d",regenerationLevel);
		Logger::console.info(str,true);
		sprintf(str,"Pet StatLevel Passed %d",statLevel);
		Logger::console.info(str,true);


		int tarmor = 0;
		int  rfort = 0;
		int pfort = 0;
		pfort = pet->getFortitude();
		if ( pfort >= 500) {

			tarmor = 500;
			rfort = pfort - 500;
		}
		else
			if (pfort < 500)  {
				tarmor = pfort;
				rfort = pfort;
			}
		// get resists and split into positive or negative values
		int resistValue = 0;
		float Psum = 0;
		float Nsum = 0;
		resistValue = pet->getKinetic();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getEnergy();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getBlast();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getHeat();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getElectrical();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getCold();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getAcid();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;
		resistValue = pet->getStun();
		if (resistValue >= 0) Psum = Psum + resistValue; else Nsum = Nsum + resistValue;

		sprintf(str,"Pet Psum1 Passed %f",Psum);
		Logger::console.info(str,true);
		sprintf(str,"Pet Nsum1 Passed %f",Nsum);
		Logger::console.info(str,true);

		sprintf(str,"Pet tarmor1 Passed %d",tarmor);
		Logger::console.info(str,true);

		//Only returns -1 for vulnerables , have to pick something like -50 for each slot x remaining fortitude
		float modifier = rfort/8;
		//modifier = -0.99f * modifier;
		Psum  = modifier * (Psum /100);
		tarmor = tarmor + Psum;
		Nsum  = (Nsum / 100)* modifier;


		sprintf(str,"Pet Psum Passed %f",Psum);
		Logger::console.info(str,true);
		sprintf(str,"Pet Nsum Passed %f",Nsum);
		Logger::console.info(str,true);
		sprintf(str,"Pet tarmor2 Passed %d",tarmor);
		Logger::console.info(str,true);

        int parmor = 0;
        parmor = tarmor + Nsum;

		sprintf(str,"Pet parmor Passed %d",parmor);
		Logger::console.info(str,true);

		if ( parmor >1) tarmor = tarmor + Nsum;
		// data table will return cl 14 if the armor is below 50  set it to 2
        int armorLevel = 2;
        if (tarmor >= 50){
		 armorLevel = DnaManager::instance()->levelForScore(DnaManager::ARM_LEVEL, tarmor );
		}
		else
			// need to drive armorlevel negative for low cl pets.
		if (tarmor < 50) {
			if (Nsum < -99) armorLevel= -3;
			else
			armorLevel = 0;

		}
		sprintf(str,"Pet ArmorLevel Passed %d",armorLevel);
		Logger::console.info(str,true);




		int level = (statLevel + damageLevel + hitLevel  + armorLevel + regenerationLevel )/5;

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


