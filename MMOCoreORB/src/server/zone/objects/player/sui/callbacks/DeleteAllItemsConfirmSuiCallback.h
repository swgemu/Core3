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
#include "server/zone/objects/transaction/TransactionLog.h"

class DeleteAllItemsConfirmSuiCallback : public SuiCallback {
public:
	DeleteAllItemsConfirmSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == nullptr || !obj->isBuildingObject())
			return;

		BuildingObject* building = cast<BuildingObject*>( obj.get());

		Locker _lock(building, creature);

		TransactionLog trx(TrxCode::PLAYERMISCACTION, creature, building);

		if (trx.isVerbose()) {
			// Force a synchronous export because the objects will be deleted before we can export them!
			trx.addRelatedObject(building, true);
			trx.setExportRelatedObjects(true);
			trx.exportRelated();
		}

		building->destroyAllPlayerItems();

		creature->sendSystemMessage("@player_structure:items_deleted"); //All of the objects in your house have been deleted.
	}
};

#endif /* DELETEALLITEMSCONFIRMSUICALLBACK_H_ */
