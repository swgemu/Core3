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

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (cancelPressed || player == NULL)
			return;

		//Player clicked "Leave Group" on notification box.
		GroupManager* manager = GroupManager::instance();

		ManagedReference<GroupObject*> group = player->getGroup();
		if (group == NULL)
			return;

		manager->leaveGroup(group.get(), player);
	}

};




#endif /* GROUPLOOTCHANGEDSUICALLBACK_H_ */
