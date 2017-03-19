/*
 * StructureStatusSuiCallback.h
 *
 *  Created on: Aug 15, 2011
 *      Author: crush
 */

#ifndef STRUCTURESTATUSSUICALLBACK_H_
#define STRUCTURESTATUSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class StructureStatusSuiCallback : public SuiCallback {
public:
	StructureStatusSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isListBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();

		if (obj == NULL || !obj->isStructureObject()) {
			creature->sendSystemMessage("@player_structure:no_valid_structurestatus"); //Your /structureStatus target is no longer valid. Cancelling refresh.
			return;
		}

		creature->executeObjectControllerAction(0x13F7E585, obj->getObjectID(), ""); //structureStatus
	}
};

#endif /* STRUCTURESTATUSSUICALLBACK_H_ */
