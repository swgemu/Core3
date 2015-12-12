/*
 * GroupLootChangedSuiCallback.h
 *
 *  Created on: March 1, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTCHANGEDSUICALLBACK_H_
#define GROUPLOOTCHANGEDSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"

class GroupLootChangedSuiCallback : public SuiCallback {
public:
	GroupLootChangedSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed || player == NULL)
			return;

		//Player clicked "Leave Group" on notification box.
		ManagedReference<GroupObject*> group = player->getGroup();
		if (group == NULL)
			return;

		GroupManager::instance()->leaveGroup(group.get(), player);
	}

};




#endif /* GROUPLOOTCHANGEDSUICALLBACK_H_ */
