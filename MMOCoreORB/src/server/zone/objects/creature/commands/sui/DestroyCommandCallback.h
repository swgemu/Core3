/*
 * DestroyCommandCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef DESTROYCOMMANDCALLBACK_H_
#define DESTROYCOMMANDCALLBACK_H_

#include "server/zone/objects/player/sui/SuiMessageCallback.h"

class DestroyCommandCallback : public SuiMessageCallback {
public:
	DestroyCommandCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL)
			return;

		if (obj->isPlayerCreature()) {
			player->sendSystemMessage("Destroying players with this command is prohibited.");
			return;
		}

		if (obj->isInQuadTree())
			obj->removeFromZone();

		obj->destroyObjectFromDatabase(true);

		player->sendSystemMessage("The object has been successfully destroyed from the database.");
	}
};

#endif /* DESTROYCOMMANDCALLBACK_H_ */
