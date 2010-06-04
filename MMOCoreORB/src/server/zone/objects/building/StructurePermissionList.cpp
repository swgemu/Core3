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
}

void StructurePermissionList::sendTo(PlayerCreature* player, const String& listName) {
	ZoneServer* zoneServer = player->getZoneServer();

	PermissionListCreateMessage* listMsg = new PermissionListCreateMessage(listName);

	for (int i = 0; i < size(); ++i) {
		VectorMapEntry<uint64, uint8> entry = elementAt(i);
		uint64 playerID = entry.getKey();
		uint8 permission = entry.getValue();

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

bool StructurePermissionList::grantPermission(uint64 playerID, uint8 permission) {
	if (!contains(playerID))
		put(playerID, permission);
	else
		get(playerID) |= permission;

	return true;
}

bool StructurePermissionList::revokePermission(uint64 playerID, uint8 permission) {
	if (contains(playerID))
		get(playerID) |= ~permission;

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
