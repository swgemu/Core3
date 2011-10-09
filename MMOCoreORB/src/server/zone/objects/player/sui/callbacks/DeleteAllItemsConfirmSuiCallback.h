/*
 * DeleteAllItemsConfirmSuiCallback.h
 *
 *  Created on: Aug 14, 2011
 *      Author: crush
 */

#ifndef DELETEALLITEMSCONFIRMSUICALLBACK_H_
#define DELETEALLITEMSCONFIRMSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/structure/StructureManager.h"


class DeleteAllItemsConfirmSuiCallback : public SuiCallback {
public:
	DeleteAllItemsConfirmSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject();

		if (obj == NULL || !obj->isBuildingObject())
			return;

		BuildingObject* building = cast<BuildingObject*>( obj.get());

		Locker _lock(building, creature);

		building->destroyAllPlayerItems();

		creature->sendSystemMessage("@player_structure:items_deleted"); //All of the objects in your house have been deleted.
	}
};

#endif /* DELETEALLITEMSCONFIRMSUICALLBACK_H_ */
