/*
 * GroupLootRuleSuiCallback.h
 *
 *  Created on: March 1, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTRULESUICALLBACK_H_
#define GROUPLOOTRULESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class GroupLootRuleSuiCallback : public SuiCallback {
public:
	GroupLootRuleSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || !suiBox->isListBox() || player == NULL || args->size() <= 0)
			return;

		int selection = Integer::valueOf(args->get(0).toString()); //The row number they chose in the list.

		if (selection < 0) //Player made no selection but pressed OK.
			return;

		ManagedReference<GroupObject*> group = player->getGroup();
		if (group == NULL)
			return;

		GroupManager::instance()->changeLootRule(group, player, selection);
	}

};


#endif /* GROUPLOOTRULESUICALLBACK_H_ */
