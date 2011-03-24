/*
 * FindCommandSuiCallback.cpp
 *
 *  Created on: Mar 23, 2011
 *      Author: crush
 */

#include "../FindCommand.h"

void FindCommandSuiCallback::run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
	if (!suiBox->isListBox() || cancelPressed)
		return;

	if (args->size() < 1)
		return;

	int index = Integer::valueOf(args->get(0).toString());

	SuiListBox* listBox = (SuiListBox*) suiBox;

	uint8 maploctype = listBox->getMenuObjectID(index);

	FindCommand::findPlanetaryObject(player, maploctype);
}
