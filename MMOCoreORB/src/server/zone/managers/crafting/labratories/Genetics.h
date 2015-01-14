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
	static bool hasASpecial(DnaComponent* a, DnaComponent* b, DnaComponent* c, DnaComponent* d, DnaComponent* e,int type) {
		return a->isSpecialResist(type) || b->isSpecialResist(type) || c->isSpecialResist(type) || d->isSpecialResist(type) || e->isSpecialResist(type);
	}
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
	static float resistanceFormula(DnaComponent* a, DnaComponent* b, DnaComponent* c, DnaComponent* d, DnaComponent* e, int type, int max) {
		float av,bv,cv,dv,ev;
		bool any = false;
		switch(type) {
			case WeaponObject::ACID:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getAcid(),a->isSpecialResist(type),any);
				bv = normalize(b->getAcid(),b->isSpecialResist(type),any);
				cv = normalize(c->getAcid(),c->isSpecialResist(type),any);
				dv = normalize(d->getAcid(),d->isSpecialResist(type),any);
				ev = normalize(e->getAcid(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::BLAST:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getBlast(),a->isSpecialResist(type),any);
				bv = normalize(b->getBlast(),b->isSpecialResist(type),any);
				cv = normalize(c->getBlast(),c->isSpecialResist(type),any);
				dv = normalize(d->getBlast(),d->isSpecialResist(type),any);
				ev = normalize(e->getBlast(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::COLD:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getCold(),a->isSpecialResist(type),any);
				bv = normalize(b->getCold(),b->isSpecialResist(type),any);
				cv = normalize(c->getCold(),c->isSpecialResist(type),any);
				dv = normalize(d->getCold(),d->isSpecialResist(type),any);
				ev = normalize(e->getCold(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::ELECTRICITY:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getElectric(),a->isSpecialResist(type),any);
				bv = normalize(b->getElectric(),b->isSpecialResist(type),any);
				cv = normalize(c->getElectric(),c->isSpecialResist(type),any);
				dv = normalize(d->getElectric(),d->isSpecialResist(type),any);
				ev = normalize(e->getElectric(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::ENERGY:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getEnergy(),a->isSpecialResist(type),any);
				bv = normalize(b->getEnergy(),b->isSpecialResist(type),any);
				cv = normalize(c->getEnergy(),c->isSpecialResist(type),any);
				dv = normalize(d->getEnergy(),d->isSpecialResist(type),any);
				ev = normalize(e->getEnergy(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::HEAT:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getHeat(),a->isSpecialResist(type),any);
				bv = normalize(b->getHeat(),b->isSpecialResist(type),any);
				cv = normalize(c->getHeat(),c->isSpecialResist(type),any);
				dv = normalize(d->getHeat(),d->isSpecialResist(type),any);
				ev = normalize(e->getHeat(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::KINETIC:
				any = hasASpecial(a,b,c,d,e,type);
				av = normalize(a->getKinetic(),a->isSpecialResist(type),any);
				bv = normalize(b->getKinetic(),b->isSpecialResist(type),any);
				cv = normalize(c->getKinetic(),c->isSpecialResist(type),any);
				dv = normalize(d->getKinetic(),d->isSpecialResist(type),any);
				ev = normalize(e->getKinetic(),e->isSpecialResist(type),any);
				break;
			case WeaponObject::LIGHTSABER:
				any = hasASpecial(a,b,c,d,e,type);
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
	static int generateCL(float hamTotal, float toHit, float speed, float damage, float kinetic, float blast, float heat, float cold, float energy, float electricy, float acid, float stun, float armorRating) {
		// calculate resists
		float base = ((float)(hamTotal-100.0)) * toHit * (((float)(damage+80.0))/speed);
		float armor = armorRating == 0 ? 1.125 : 0.75;
		float rKinetic = kinetic >= 0 ? kinetic : armorRating == 0 ? 0 : -50;
		float rBlast = blast >= 0 ? blast : armorRating == 0 ? 0 : -50;
		float rHeat = heat >= 0 ? heat : armorRating == 0 ? 0 : -50;
		float rCold = cold >= 0 ? cold : armorRating == 0 ? 0 : -50;
		float rEnergy = energy >= 0 ? energy : armorRating == 0 ? 0 : -50;
		float rElectricity = electricy >= 0 ? electricy : armorRating == 0 ? 0 : -50;
		float rAcid = acid >= 0 ? acid : armorRating == 0 ? 0 : -50;
		float rStun = stun >= 0 ? stun : armorRating == 0 ? 0 : -50;
		// We need to maybe handle special resists differently for the calc, we also need to adust for newer informaiton
		float resist = 1 - (0.35*rKinetic/100) - (0.35*rEnergy/100) - (0.05*rBlast/100) - (0.05*rHeat/100) - (0.05*rCold/100) - (0.05*rElectricity/100) - (0.05*rAcid/100) - (0.05*rStun/100);
		return floor( (1.5/(float)100) * (Math::sqrt(base/(armor * resist))+7));
	}
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICS_H_ */
