/*
 * StructureStatusSuiCallback.h
 *
 *  Created on: Aug 15, 2011
 *      Author: crush
 */

#ifndef STRUCTURESTATUSSUICALLBACK_H_
#define STRUCTURESTATUSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/gcw/GCWManager.h"


class StructureStatusSuiCallback : public SuiCallback {
public:
	StructureStatusSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isListBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();
		ManagedReference<StructureObject*> structure = sui->getStructureObject().get();

		if (obj == nullptr || creature == nullptr || structure == nullptr) {
			return;
		}

		Zone* zone = structure->getZone();

		if (zone == nullptr) {
			return;
		}

		GCWManager* gcwMan = zone->getGCWManager();

		if (gcwMan == nullptr) {
			return;
		}

		if ((structure->isGCWBase() && !gcwMan->canUseTerminals(creature, structure->asBuildingObject(), obj)) || !structure->isOnAdminList(creature)) {
			creature->sendSystemMessage("@player_structure:no_valid_structurestatus"); //Your /structureStatus target is no longer valid. Cancelling refresh.
			return;
		}

		StructureManager::instance()->reportStructureStatus(creature, structure, obj);
	}
};

#endif /* STRUCTURESTATUSSUICALLBACK_H_ */
