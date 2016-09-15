/*
 * GroupLootPickLooterSuiCallback.h
 *
 *  Created on: March 2, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTPICKLOOTERSUICALLBACK_H_
#define GROUPLOOTPICKLOOTERSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"


class GroupLootPickLooterSuiCallback : public SuiCallback {
public:
	GroupLootPickLooterSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		//Pre: player is locked
		//Post: player is locked

		if (cancelPressed || player == NULL || args->size() <= 0)
			return;

		int menuSelection = Integer::valueOf(args->get(0).toString()); //The row number they chose in the list.

		if (menuSelection < 0) //No selection was made but player pressed OK box.
			return;

		if (!suiBox->isListBox())
			return;
		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		//Get the objectID of the player chosen to be the Master Looter.
		uint64 newMasterLooterID = listBox->getMenuObjectID(menuSelection);

		ManagedReference<GroupObject*> group = player->getGroup();
		if (group == NULL)
			return;

		Locker glocker(group, player);

		if (group->getLeader() != player)
			return;

		//Validate the player we're trying to make ML exists and is in the group.
		ManagedReference<CreatureObject*> object = player->getZoneServer()->getObject(newMasterLooterID).castTo<CreatureObject*>();
		if (object == NULL || !object->isPlayerCreature() || !group->hasMember(object))
			return;

		//Change the Master Looter.
		GroupManager::instance()->changeMasterLooter(group, object, true);

	}

};


#endif /* GROUPLOOTPICKLOOTERSUICALLBACK_H_ */
