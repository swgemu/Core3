/*
 * PlayerTeachSuiCallback.h
 *
 *  Created on: Mar 13, 2012
 *      Author: katherine
 */

#ifndef PLAYERTEACHSUICALLBACK_H_
#define PLAYERTEACHSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/PlayerTeachConfirmSuiCallback.h"

class PlayerTeachSuiCallback : public SuiCallback {
	String skillname;

public:
	PlayerTeachSuiCallback(ZoneServer* serv, const String& name) : SuiCallback(serv) {
		skillname = name;
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!sui->isListBox() || cancelPressed)
			return;

		SuiListBox* listBox = cast<SuiListBox*>( sui);

		if(!creature->isPlayerCreature())
			return;

		if(!cancelPressed) {

			// Send the player being trained a confirmation.

			ManagedReference<CreatureObject*> player = cast<CreatureObject*>(sui->getUsingObject());

			ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::TEACH_PLAYER);
			sui->setPromptTitle("@base_player:swg");
			sui->setPromptText("Someone has offered you teaching in..."); // TODO: Get actual strings.

			sui->addMenuItem("@skl_n:" + skillname);

			sui->setCancelButton(true, "Cancel");
			sui->setUsingObject(creature);

			sui->setForceCloseDistance(32);

			sui->setCallback(new PlayerTeachConfirmSuiCallback(creature->getZoneServer(), skillname));

			player->getPlayerObject()->addSuiBox(sui);
			player->sendMessage(sui->generateMessage());

			StringIdChatParameter params("teaching", "offer_given"); // You offer to teach %TT %TO.
			params.setTT(creature->getDisplayedName());
			params.setTO("@skl_n:" + skillname);
			creature->sendSystemMessage(params);


			}
		}
};


#endif /* PLAYERTEACHSUICALLBACK_H_ */
