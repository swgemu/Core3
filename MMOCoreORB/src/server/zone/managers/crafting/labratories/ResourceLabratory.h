/*
 * ResourceLabratory.h
 *
 *  Created on: Aug 6, 2013
 *      Author: swgemu
 */

#ifndef RESOURCELABRATORY_H_
#define RESOURCELABRATORY_H_

#include <algorithm>

#include "SharedLabratory.h"
#include "system/lang/String.h"
#include "system/util/SortedVector.h"

namespace server {
namespace zone {
class ZoneServer;
namespace objects {
namespace manufactureschematic {
class ManufactureSchematic;
namespace craftingvalues {
class CraftingValues;
}  // namespace craftingvalues
}  // namespace manufactureschematic
namespace tangible {
class TangibleObject;
}  // namespace tangible
}  // namespace objects
}  // namespace zone
}  // namespace server

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
