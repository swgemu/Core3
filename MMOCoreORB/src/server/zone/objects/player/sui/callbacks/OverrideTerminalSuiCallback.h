/*
 * OverrideTerminalSuiCallback.h
 *
 *  Created on: Nov 1, 2012
 *      Author: root
 */

#ifndef OVERRIDETERMINALSUICALLBACK_H_
#define OVERRIDETERMINALSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/gcw/GCWManager.h"

class OverrideTerminalSuiCallback : public SuiCallback {

public:
	OverrideTerminalSuiCallback(ZoneServer* server) : SuiCallback(server) {}


	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0 )
			return;

		if(player->isDead() || player->isIncapacitated())
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if(obj == NULL || !obj->isTangibleObject())
			return;

		ManagedReference<TangibleObject*> overrideTerminal = cast<TangibleObject*>(obj.get());

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if (gcwMan == NULL)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		gcwMan->processDNASample(player, overrideTerminal, index);
	}
};






#endif /* OVERRIDETERMINALSUICALLBACK_H_ */
