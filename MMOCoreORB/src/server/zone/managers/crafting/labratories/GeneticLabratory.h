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
	String pickSpecialAttack(String a, String b, String c, String d, String e, int odds, String other);
public:
	GeneticLabratory();
	virtual ~GeneticLabratory();
	void setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess);
	void experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult);
	void initialize(ZoneServer* server);
	bool allowFactoryRun(ManufactureSchematic* manufactureSchematic);
	int getCreationCount(ManufactureSchematic* manufactureSchematic);
protected:
	float calcResistMin(float input,float mod) {
		if (input < 0)
			input = -1;
		return (input * ((input/100) + 0.15)) * mod;
	}
	// 12/22 == 12/22 = 0.5
	float calcMaxPercentage(uint32 value,uint32 diff) {
		float percent = ((float)diff/(float)value);
		if (percent > 1)
			percent = 1;
		return percent;
	}
	float getPercentagOfValue(int number, float percentage) {
		float intermediate = ((float)number) * percentage;
		return (float) ceil(intermediate);
	}
	void recalculateResist(CraftingValues* craftingValues);
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICLABRATORY_H_ */
