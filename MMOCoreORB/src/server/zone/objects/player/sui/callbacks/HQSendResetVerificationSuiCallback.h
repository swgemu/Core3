/*
 * HQSendResetVerificationSuiCallback.h
 *
 *  Created on: Oct 27, 2012
 *      Author: root
 */

#ifndef HQSENDRESETVERIFICATIONSUICALLBACK_H_
#define HQSENDRESETVERIFICATIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class HQSendResetVerificationSuiCallback : public SuiCallback {
public:
	HQSendResetVerificationSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || player == NULL || cancelPressed ) {
			return;
		}
		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isBuildingObject())
			return;

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan==NULL)
			return;

		gcwMan->resetVulnerability(player, building);
	}
};




#endif /* HQSENDRESETVERIFICATIONSUICALLBACK_H_ */
