/*
 * SelectTurretDonationSuiCallback.h
 *
 *  Created on: Nov 30, 2012
 *      Author: root
 */

#ifndef SELECTTURRETDONATIONSUICALLBACK_H_
#define SELECTTURRETDONATIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class SelectTurretDonationSuiCallback : public SuiCallback {

public:
	SelectTurretDonationSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isBuildingObject())
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		int indx = Integer::valueOf(args->get(0).toString());

		if(indx < 0)
			return;

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();


		if(gcwMan==NULL)
			return;

		gcwMan->sendSelectDeedToDonate(building, player,indx);

	}
};





#endif /* SELECTTURRETDONATIONSUICALLBACK_H_ */
