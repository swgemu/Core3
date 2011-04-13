/*
 * PlayerStructureComponent.h
 *
 *  Created on: Mar 24, 2011
 *      Author: crush
 */

#ifndef PLAYERSTRUCTURECOMPONENT_H_
#define PLAYERSTRUCTURECOMPONENT_H_

#include "engine/engine.h"
#include "MaintenanceComponent.h"

class PlayerStructureComponent : public Object, public Logger {
	StructurePermissionList structurePermissionList;
	Reference<MaintenanceComponent*> maintenanceComponent;
	Reference<MaintenanceComponent*> powerComponent;

	uint64 deedObjectID;

public:
	PlayerStructureComponent();
	PlayerStructureComponent(const PlayerStructureComponent& psc);
	PlayerStructureComponent& operator= (const PlayerStructureComponent& psc);


};


#endif /* PLAYERSTRUCTURECOMPONENT_H_ */
