/*
 * DestroyCommandSuiCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef DESTROYCOMMANDSUICALLBACK_H_
#define DESTROYCOMMANDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class DestroyCommandSuiCallback : public SuiCallback {
public:
	DestroyCommandSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* creature, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject().get();

		if (obj == NULL)
			return;

		if (obj->isPlayerCreature()) {
			creature->sendSystemMessage("Destroying players with this command is prohibited.");
			return;
		}


		obj->destroyObjectFromWorld(true);

		obj->destroyObjectFromDatabase(true);

		creature->sendSystemMessage("The object has been successfully destroyed from the database.");
	}
};

#endif /* DESTROYCOMMANDSUICALLBACK_H_ */
