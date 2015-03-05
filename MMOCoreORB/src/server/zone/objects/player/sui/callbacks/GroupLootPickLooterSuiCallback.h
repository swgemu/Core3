/*
 * GroupLootPickLooterSuiCallback.h
 *
 *  Created on: March 2, 2015
 *      Author: Anakis
 */

#ifndef GROUPLOOTPICKLOOTERSUICALLBACK_H_
#define GROUPLOOTPICKLOOTERSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class GroupLootPickLooterSuiCallback : public SuiCallback {
public:
	GroupLootPickLooterSuiCallback(ZoneServer* server) : SuiCallback(server) {

	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
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
		ManagedReference<SceneObject*> object = player->getZoneServer()->getObject(newMasterLooterID);
		if (object == NULL || !object->isPlayerCreature() || !group->hasMember(object))
			return;

		//Change the Master Looter.
		CreatureObject* newLooter = cast<CreatureObject*>(object.get());
		GroupManager::instance()->changeMasterLooter(group, newLooter, true);

	}

};




#endif /* GROUPLOOTPICKLOOTERSUICALLBACK_H_ */
