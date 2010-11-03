/*
 * FindCommandCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef FINDCOMMANDCALLBACK_H_
#define FINDCOMMANDCALLBACK_H_

#include "server/zone/objects/player/sui/SuiMessageCallback.h"

class FindCommandCallback : public SuiMessageCallback {
public:
	FindCommandCallback(ZoneClientSession* client, ZoneProcessServer* server)
		: SuiMessageCallback(client, server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		SuiListBox* listBox = (SuiListBox*) suiBox;

		uint8 maploctype = listBox->getMenuObjectID(index);

		FindCommand::findPlanetaryObject(player, maploctype);
	}
};

#endif /* FINDCOMMANDCALLBACK_H_ */
