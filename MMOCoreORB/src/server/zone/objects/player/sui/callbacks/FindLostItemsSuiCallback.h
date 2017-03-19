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

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL || !obj->isBuildingObject())
			return;

		BuildingObject* building = cast<BuildingObject*>( obj.get());

		if (building->getZone() == NULL)
			return;

		StructureManager::instance()->moveFirstItemTo(creature, building);
	}
};

#endif /* FINDLOSTITEMSSUICALLBACK_H_ */
