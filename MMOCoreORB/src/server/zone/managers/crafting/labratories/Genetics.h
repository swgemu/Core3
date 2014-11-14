#ifndef GENETICS_H_
#define GENETICS_H_

#include "SharedLabratory.h"
#include "engine/engine.h"
#include "server/zone/managers/creature/DnaManager.h"

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
		// we should now have the run to the max for both a and b, so determine the highest
		// if we say 14 rounds needed the max percentage would be: 14/10 = 1.4 or 140% or 100% normalized
		float maxACount = aCount/10.0f;
		float maxBCount = bCount/10.0f;
		float maxCount = maxACount > maxBCount ? maxACount : maxBCount;
		return maxCount > 1 ? 1 : maxCount;
	}
	static float normalize(float a) {
		return a < 0 ? -99 : a;
	}
	static float resistanceFormula(float a, float b, float c, float d, float e, float cap) {
		float value = round((normalize(a) * 0.4) + (normalize(b) *0.25) + (normalize(c) * 0.05) + (normalize(d) * 0.05) + (normalize(e) * 0.25));
		return value > cap ? cap : value;
	}
	static uint32 initialValue(float maxValue) {
		return round(maxValue * ((maxValue/(float)1000)+0.15));
	}
	static float determineMinResistance(float input) {
		if (input < 0) // if max is vulnerable the min is always vulnerable
			return -1;
		return round(input * ((input/100.0f) + 0.15f));
	}
	static int generateCL(int ha, int fort, int dex, int intelligence, int cle, int fie, int pow) {
		DnaManager* instance = DnaManager::instance();
		int a = instance->getLevelForStat(DnaManager::FORTITUDE,fort);
		int b = instance->getLevelForStat(DnaManager::HARDINESS,ha);
		int c = instance->getLevelForStat(DnaManager::DEXTERITY,dex);
		int d = instance->getLevelForStat(DnaManager::INTELLIGENCE,intelligence);
		int e = instance->getLevelForStat(DnaManager::CLEVERNESS,cle);
		int f = instance->getLevelForStat(DnaManager::FIERCENESS,fie);
		int g = instance->getLevelForStat(DnaManager::POWER,pow);
		return ceil( ((float)a + (float)b + (float)c + (float)d + (float)e + (float)f + (float)g) / (float)7);
	}
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICS_H_ */
