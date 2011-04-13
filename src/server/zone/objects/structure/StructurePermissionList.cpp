/*
 * StructurePermissionList.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "StructurePermissionList.h"
#include "server/zone/packets/ui/PermissionListCreateMessage.h"
#include "server/zone/ZoneServer.h"

StructurePermissionList::StructurePermissionList()
		: VectorMap<uint64, uint8>() {
	setInsertPlan(NO_DUPLICATE);
	setNullValue(0);
}

void StructurePermissionList::sendTo(PlayerCreature* player, const String& listName) {
	ZoneServer* zoneServer = player->getZoneServer();

	PermissionListCreateMessage* listMsg = new PermissionListCreateMessage(listName);

	uint8 permission = getPermissionFromListName(listName);

	//Little hack that handles admin list displaying...
	if (permission == ADMIN)
		permission = ADMINLIST;

	for (int i = 0; i < size(); ++i) {
		VectorMapEntry<uint64, uint8>* entry = &elementAt(i);
		uint64 playerID = entry->getKey();
		uint8 playerPermission = entry->getValue();

		if (!(playerPermission & permission))
			continue;

		ManagedReference<SceneObject*> obj = zoneServer->getObject(playerID);

		if (obj == NULL || !obj->isPlayerCreature())
			continue;

		PlayerCreature* listedPlayer = (PlayerCreature*) obj.get();
		listMsg->addName(listedPlayer->getFirstName());
	}

	listMsg->generateMessage(); //must be called after adding all the names to the list

	player->sendMessage(listMsg);
}

void StructurePermissionList::sendTo(PlayerCreature* player, uint8 permission) {
	String listName = getListName(permission);

	sendTo(player, listName);
}

bool StructurePermissionList::addPermission(uint64 playerID, uint8 permission) {
	if (!contains(playerID)) {
		put(playerID, permission);
	} else {
		if (permission == BANLIST)
			get(playerID) = 0; //If adding to ban list, then remove all permissions first.

		get(playerID) |= permission;
	}

	return true;
}

bool StructurePermissionList::removePermission(uint64 playerID, uint8 permission) {
	if (!contains(playerID))
		return false;

	get(playerID) &= ~permission;

	return true;
}

String StructurePermissionList::getListName(uint8 permission) {
	switch (permission) {
	case BANLIST:
		return "BAN";
	case ENTRYLIST:
		return "ENTRY";
	case VENDORLIST:
		return "VENDOR";
	case HOPPERLIST:
		return "HOPPER";
	}

	return "ADMIN";
}

uint8 StructurePermissionList::getPermissionFromListName(const String& listName) {
	if (listName == "BAN")
		return BANLIST;
	else if (listName == "ENTRY")
		return ENTRYLIST;
	else if (listName == "VENDOR")
		return VENDORLIST;
	else if (listName == "HOPPER")
		return HOPPERLIST;
	else
		return ADMIN;
}
