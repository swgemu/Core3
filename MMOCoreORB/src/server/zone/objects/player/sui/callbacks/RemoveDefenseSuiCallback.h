/*
 * RemoveDefenseSuiCallback.h
 *
 *  Created on: Dec 3, 2012
 *      Author: root
 */

#ifndef REMOVEDEFENSESUICALLBACK_H_
#define REMOVEDEFENSESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/gcw/GCWManager.h"

class RemoveDefenseSuiCallback : public SuiCallback {
private:
	uint64 deed;
public:
	RemoveDefenseSuiCallback(ZoneServer* server, uint64 deedID)
		: SuiCallback(server) {
		deed = deedID;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || !suiBox->isMessageBox() || player == nullptr)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == nullptr || !obj->isBuildingObject())
			return;

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();


		if (gcwMan == nullptr)
			return;

		gcwMan->removeDefense(building, player, deed);

	}
};

#endif /* REMOVEDEFENSESUICALLBACK_H_ */
