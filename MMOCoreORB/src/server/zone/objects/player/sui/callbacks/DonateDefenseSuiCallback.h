/*
 * DonateDefenseSuiCallback.h
 *
 *  Created on: Nov 30, 2012
 *      Author: root
 */

#ifndef DONATEDEFENSESUICALLBACK_H_
#define DONATEDEFENSESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class DonateDefenseSuiCallback : public SuiCallback {
protected:
	int turretSlot;

public:
	DonateDefenseSuiCallback(ZoneServer* server, int turretIndex)
		: SuiCallback(server) {
		turretSlot = turretIndex;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isBuildingObject())
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		int indx = Integer::valueOf(args->get(0).toString());

		uint64 objectid = listBox->getMenuObjectID(indx);

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan==NULL)
			return;

		gcwMan->performDefenseDontation(building, player,objectid, turretSlot);

	}
};



#endif /* DONATEDEFENSESUICALLBACK_H_ */
