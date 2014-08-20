/*
 * ResourceLabratory.h
 *
 *  Created on: Aug 6, 2013
 *      Author: swgemu
 */

#ifndef RESOURCELABRATORY_H_
#define RESOURCELABRATORY_H_

#include "SharedLabratory.h"
namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class ResourceLabratory: public SharedLabratory {
public:
	ResourceLabratory();
	virtual ~ResourceLabratory();
	void setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess);
	void experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult);
	void initialize(ZoneServer* server);
	bool allowFactoryRun(ManufactureSchematic* manufactureSchematic);
	int getCreationCount(ManufactureSchematic* manufactureSchematic);
protected:
	SortedVector<String> bioMods;
	bool applyComponentStats(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic);
	String checkBioSkillMods(const String& property);
};

}
}
}
}
}
using namespace server::zone::managers::crafting::labratories;


#endif /* RESOURCELABRATORY_H_ */
