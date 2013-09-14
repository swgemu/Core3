/*
 * GeneticLabratory.h
 *
 *  Created on: Aug 7, 2013
 *      Author: swgemu
 */

#ifndef GENETICLABRATORY_H_
#define GENETICLABRATORY_H_

#include "SharedLabratory.h"
#include "engine/engine.h"

namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class GeneticLabratory: public SharedLabratory {
private:
	const static short PHYSIQUE = 0;
	const static short PROWESS = 1;
	const static short MENTAL = 2;
	const static short AGRESSION = 3;
	const static short PHYSCHOLOGICAL = 4;
	float applyFormula(float a, float b, float c, float d, float e,int formula);
	String pickSpecialAttack(String a, String b, String c, String d, String e, int odds);
public:
	GeneticLabratory();
	virtual ~GeneticLabratory();
	void setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess);
	void experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult);
	void initialize(ZoneServer* server);
	bool allowFactoryRun(ManufactureSchematic* manufactureSchematic);
protected:
	uint32 calcMin(float input) {
		return Math::getPrecision( (input * ((input/1000) + 0.15)),0);
	}
	float calcResistMin(float input,float mod) {
		if (input < 0)
			input = -99;
		return (input * ((input/1000) + 0.15)) * mod;
	}
	float calcMaxPercentage(uint32 value) {
		float percent = ((float)value/(float)1000);
		if (percent > 1)
			percent = 1;
		return percent;
	}

};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICLABRATORY_H_ */
