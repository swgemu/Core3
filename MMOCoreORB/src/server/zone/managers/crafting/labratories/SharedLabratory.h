/*
 * SharedLabratory.h
 *
 *  Created on: Aug 5, 2013
 *      Author: swgemu
 */

#ifndef SHAREDLABRATORY_H_
#define SHAREDLABRATORY_H_

#include "engine/engine.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/managers/skill/SkillModManager.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ComponentSlot.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/ResourceSlot.h"
#include "server/zone/managers/ZoneManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
namespace server {
namespace zone {
namespace managers {
namespace crafting {
namespace labratories {

class SharedLabratory :  public Object, public Logger{
public:
	SharedLabratory();
	virtual ~SharedLabratory();
	// setup the initial combine values
	virtual void setInitialCraftingValues(TangibleObject* prototype, ManufactureSchematic* manufactureSchematic, int assemblySuccess) = 0;
	// allow each lab to handle the experimation results. You can callback to the crafting manage to determine changes if you wish
	virtual void experimentRow(CraftingValues* craftingValues,int rowEffected, int pointsAttempted, float failure, int experimentationResult) = 0;
	virtual void initialize(ZoneServer* server);
	virtual float getWeightedValue(ManufactureSchematic* manufactureSchematic, int type);
	virtual bool allowFactoryRun(ManufactureSchematic* manufactureSchematic);
	virtual int getCreationCount(ManufactureSchematic* manufactureSchematic) = 0;
protected:
	ManagedReference<ZoneServer*> zoneServer;
	float calculateExperimentationValueModifier(int experimentationResult, int pointsAttempted);
	float calculateAssemblyValueModifier(int assemblyResult);
	float getAssemblyPercentage(float value);
};

}
}
}
}
}
using namespace server::zone::managers::crafting::labratories;

#endif /* SHAREDLABRATORY_H_ */
