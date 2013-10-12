/*
 * PowerRegulatorSuiCallback.h
 *
 *  Created on: Nov 2, 2012
 *      Author: root
 */

#ifndef POWERREGULATORSUICALLBACK_H_
#define POWERREGULATORSUICALLBACK_H_


#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class PowerRegulatorSuiCallback : public SuiCallback {

public:
	PowerRegulatorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}


	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0 )
			return;

		if(player->isDead() || player->isIncapacitated())
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isTangibleObject())
			return;

		ManagedReference<TangibleObject*> powerRegulator = cast<TangibleObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan==NULL)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		gcwMan->handlePowerRegulatorSwitch(player,powerRegulator,index);
	}
};





#endif /* POWERREGULATORSUICALLBACK_H_ */
