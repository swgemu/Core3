/*
 * OverrideTerminalSuiCallback.h
 *
 *  Created on: Nov 1, 2012
 *      Author: root
 */

#ifndef OVERRIDETERMINALSUICALLBACK_H_
#define OVERRIDETERMINALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/gcw/GCWManager.h"

class OverrideTerminalSuiCallback : public SuiCallback {
	String dnaString;
public:
	OverrideTerminalSuiCallback(ZoneServer* server, String dnaCode)
		: SuiCallback(server) {
		dnaString = dnaCode;
	}


	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0 )
			return;

		if(player->isDead() || player->isIncapacitated())
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if(obj == NULL || !obj->isTangibleObject())
			return;

		ManagedReference<TangibleObject*> overrideTerminal = cast<TangibleObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if(gcwMan==NULL)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		gcwMan->processDNASample(player, overrideTerminal, dnaString, index);


	}
};






#endif /* OVERRIDETERMINALSUICALLBACK_H_ */
