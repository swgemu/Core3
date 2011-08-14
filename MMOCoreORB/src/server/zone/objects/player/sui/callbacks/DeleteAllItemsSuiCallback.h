/*
 * DeleteAllItemsSuiCallback.h
 *
 *  Created on: Aug 14, 2011
 *      Author: crush
 */

#ifndef DELETEALLITEMSSUICALLBACK_H_
#define DELETEALLITEMSSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/PlayerObject.h"

class DeleteAllItemsSuiCallback : public SuiCallback {
public:
	DeleteAllItemsSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		//Send another confirmation just to be sure.
		sui->setPromptText("@player_structure:delete_all_items_second_d"); //Again, this command will delete every object in your house. Objects destroyed in this manner are not reimbursable. Are you really sure you want to do this?
		sui->setCallback(new DeleteAllItemsConfirmSuiCallback(server));

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost != NULL) {
			creature->sendMessage(sui->generateMessage());
			ghost->addSuiBox(sui);
		}
	}
};

#endif /* DELETEALLITEMSSUICALLBACK_H_ */
