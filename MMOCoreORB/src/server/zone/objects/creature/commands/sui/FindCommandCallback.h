/*
 * FindCommandCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef FINDCOMMANDCALLBACK_H_
#define FINDCOMMANDCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class FindCommandCallback : public SuiCallback {
public:
	FindCommandCallback(ZoneProcessServer* server)
		: SuiCallback(server) {
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
