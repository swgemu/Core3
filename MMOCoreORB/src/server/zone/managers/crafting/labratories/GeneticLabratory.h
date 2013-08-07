/*
 * GeneticLabratory.h
 *
 *  Created on: Aug 7, 2013
 *      Author: swgemu
 */

#ifndef GENETICLABRATORY_H_
#define GENETICLABRATORY_H_

#include "SharedLabratory.h"

namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class GeneticLabratory: public SharedLabratory {
public:
	GeneticLabratory();
	virtual ~GeneticLabratory();
	void setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess);
	void experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult);
	void initialize(ZoneServer* server);
};

}
}
}
}
}

using namespace server::zone::managers::crafting::labratories;
#endif /* GENETICLABRATORY_H_ */
