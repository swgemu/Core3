#ifndef GENETICS_H_
#define GENETICS_H_

#include "SharedLabratory.h"
#include "engine/engine.h"

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
		return ((max / 10.0f) * .01f); // deterine max percentage. we will lock the stats each round after experimentation to handle adjustment our selves.
	}
	/**
	 * Genetic experiments differently, we have know formula increase per point spent.
	 * so we can calculate the max points possible for any given stat they arent as linear as resource items are.
	 */
	// demo 2,342,14
	static float maxExperimentationPercentage(float a, float b, float aMax, float bMax) {
		int count = 0;
		float workingA = a;
		float workingB = b;
		while(workingA < aMax && count < 10) {
			workingA += experimentFormula(workingB,workingA);
			workingB += experimentFormula(workingA,workingB);
			if (workingB > bMax)
				workingB = bMax;
			count++;
		}
		float max = count/10.0f;
		return max > 1 ? 1 : max;
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
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICS_H_ */
