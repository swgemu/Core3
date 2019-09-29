/*
 * JamUplinkSuiCallback.h
 *
 *  Created on: Oct 31, 2012
 *      Author: root
 */

#ifndef JAMUPLINKSUICALLBACK_H_
#define JAMUPLINKSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/managers/gcw/GCWManager.h"

class JamUplinkSuiCallback : public SuiCallback {
public:
	JamUplinkSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}


	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || !suiBox->isListBox() || player == nullptr || args->size() <= 0 )
			return;

		if (player->isDead() || player->isIncapacitated())
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == nullptr)
			return;

		TangibleObject* uplinkTerm = cast<TangibleObject*>(obj.get());

		ManagedReference<BuildingObject*> building = obj->getParentRecursively(SceneObjectType::FACTIONBUILDING).castTo<BuildingObject*>();

		if (building == nullptr)
			return;

		GCWManager* gcwMan = player->getZone()->getGCWManager();

		if (gcwMan == nullptr)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		gcwMan->verifyUplinkBand(player, building, index, uplinkTerm);
	}
};





#endif /* JAMUPLINKSUICALLBACK_H_ */
