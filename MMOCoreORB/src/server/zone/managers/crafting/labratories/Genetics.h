#ifndef GENETICS_H_
#define GENETICS_H_

#include "SharedLabratory.h"
#include "engine/engine.h"
#include "server/zone/managers/creature/DnaManager.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"

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
		return rc > 1000 ? 1000.0 : rc;
	}
	static float prowessFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.25) + (b *0.42) + (c * 0.17) + (d * 0.085) + (e * .075));
		return rc > 1000 ? 1000.0 : rc;
	}
	static float mentalFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.05) + (b *0.1) + (c * 0.5) + (d * 0.3) + (e * .05));
		return rc > 1000 ? 1000.0 : rc;
	}
	static float aggressionFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.17) + (b *0.16) + (c * 0.085) + (d * 0.165) + (e * 0.42));
		return rc > 1000 ? 1000.0 : rc;
	}
	static float physchologicalFormula(float a,float b,float c,float d,float e){
		float rc = ceil((a * 0.09) + (b *0.05) + (c * 0.26) + (d * 0.43) + (e * 0.17));
		return rc > 1000 ? 1000.0 : rc;
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
			return -99;
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
		float av,bv,cv,dv,ev;
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
		float value = round(physiqueFormula(av,bv,cv,dv,ev));
		return value > max ? max : value;
	}

	static uint32 initialValue(float maxValue) {
		return round(maxValue * ((maxValue/(float)1000)+0.15));
	}

	static float determineMinResistance(float input) {
		if (input < 0) // if max is vulnerable the min is always vulnerable
			return -99;
		return round(input * ((input/100.0f) + 0.15f));
	}

	/**
	 * Generate damage factor
	 */
	static float generateDamageFactor(float hit, float speed, float maxDamage) {
		return (((maxDamage-10.0) * 0.5) * hit) * speed;
	}

	/**
	 * Generate ham factor
	 */
	static float generateHamFactor(float h, float a, float m) {
		return ((h+a+m)/1500.0) - 3;
	}

	/**
	 * Generate positive factor
	 */
	static float generatePositiveFactor(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		return (a+b+c+d+e+f+g+h+i)/25.0;
	}

	/**
	 * Generate negative fctor
	 */
	static float generateNegativeFactor(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		float factor = -5.0;
		return (a * factor) + (b * factor) + (c * factor)+ (d * factor)+ (e * factor)+ (f * factor)+ (g * factor)+ (h * factor)+ (i * factor);
	}

	/**
	 * Generate the special factor for CL
	 * params: kinetic, blast, energy, stun, cold, acid, heat, electricity, saber
	 */
	static float generateSpecialFactor(float a, float b, float c, float d, float e, float f, float g, float h, float i) {
		float div = 5.0;
		float accumulator = 0;
		accumulator = (a/div) + (b/div) + (c/div) + (d/div) + (e/div) + (f/div) + (g/div) + (h/div) + (i/div);
		return accumulator * 2.50;
	}

	/** reversal formulas **/

	/**
	 * Reverse Ham value
	 */
	static int reverseHam(int value, int quality) {
		float x = value/18;
		int min = x - (35 + quality);
		int max = x + (11 - quality);
		if (min < 0)
			min = 0;
		return (int) (System::random(max-min) + min);
	}

	/**
	 * Reverse damage value
	 */
	static int reverseDamage(int value, int quality) {
		float x = round(((float)value) * 0.8);
		int min = x - (35 + quality);
		int max = x + (11 - quality);
		if (min < 0)
			min = 0;
		return (int)(System::random(max-min) + min);
	}
	static float reverseHit(float hit, int quality) {
		float x = round((hit - 0.19) * 1500.0);
		float min = x - (9 + quality);
		if (min < 0)
			min = 0;
		float max = x + (21 - quality);
		return (float)(System::random(max-min) + min);
	}
	static float reverseResistance(float effective, int armor) {
		// find effective resist
		// multiply effective resist * 10 to get base + 500 for armor
		// so rancor level 75 comes out with 250 + 500 - the wiggle.
		float min = (effective * 10) - 10;
		float max = (effective * 10 ) + 20;
		float score = 0;
		if (min < 0)
			min = 0;
		score = System::random(max - min) + min;
		if (score < 0)
			score = 0;
		if (armor > 0) {
			score += 500;
		}
		return score;
	}

};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICS_H_ */
