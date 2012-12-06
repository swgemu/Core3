/*
 * HQDefenseStatusCallback.h
 *
 *  Created on: Oct 27, 2012
 *      Author: root
 */

#ifndef HQDEFENSESTATUSSUICALLBACK_H_
#define HQDEFENSESTATUSSUICALLBACK_H_
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class HQDefenseStatusSuiCallback : public SuiCallback {
public:
	HQDefenseStatusSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isBuildingObject())
			return;

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan==NULL)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());
		int indx = Integer::valueOf(args->get(1).toString());

		if(indx == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		uint64 turretOID = listBox->getMenuObjectID(indx);


		if(otherPressed)
			gcwMan->sendRemoveDefenseConfirmation(building, player, turretOID);
		else
			gcwMan->sendBaseDefenseStatus(player, building);

	}
};



#endif /* HQDEFENSESTATUSCALLBACK_H_ */
