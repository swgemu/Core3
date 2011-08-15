/*
 * FindLostItemsSuiCallback.h
 *
 *  Created on: Aug 15, 2011
 *      Author: crush
 */

#ifndef FINDLOSTITEMSSUICALLBACK_H_
#define FINDLOSTITEMSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/structure/StructureManager.h"

class FindLostItemsSuiCallback : public SuiCallback {
public:
	FindLostItemsSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isBuildingObject())
			return;

		BuildingObject* building = (BuildingObject*) obj.get();

		if (building->getZone() == NULL)
			return;

		ManagedReference<StructureManager*> structureManager = building->getZone()->getStructureManager();
		structureManager->moveFirstItemTo(creature, building);
	}
};

#endif /* FINDLOSTITEMSSUICALLBACK_H_ */
