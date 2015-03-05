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
		if (cancelPressed || player == NULL || args->size() <= 0)
			return;

		int menuSelection = Integer::valueOf(args->get(0).toString()); //The row number they chose in the list.

		if (menuSelection < 0) //No selection was made but player pressed OK box.
			return;

		ManagedReference<GroupObject*> group = player->getGroup();
		if (group == NULL)
			return;

		//Validate the selection is in our looter list's range.
		int listSize = group->getMasterLooterListSize();
		if (menuSelection > listSize -1 || listSize == 0)
			return;

		//Get the objectID of the player chosen to be the Master Looter.
		//The list of players we provided was saved on the group.
		uint64 newMasterLooterID = group->getFromMasterLooterList(menuSelection);

		//Validate the player we're trying to make ML exists and is in the group.
		ManagedReference<SceneObject*> object = player->getZoneServer()->getObject(newMasterLooterID);
		if (object == NULL || !object->isPlayerCreature() || !group->hasMember(object))
			return;

		CreatureObject* newLooter = cast<CreatureObject*>(object.get());

		//Cleanup the list of potential looters.
		group->clearMasterLooterList();

		GroupManager::instance()->changeMasterLooter(group, player, newLooter, true);

	}

};




#endif /* GROUPLOOTPICKLOOTERSUICALLBACK_H_ */
