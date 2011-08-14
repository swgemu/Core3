/*
 * StructurePermissionList.cpp
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */


#include "StructurePermissionList.h"
#include "server/zone/packets/ui/PermissionListCreateMessage.h"
#include "server/zone/ZoneServer.h"

StructurePermissionList::StructurePermissionList() {
	permissionLists.setNoDuplicateInsertPlan();

	//TODO: Load these from the structure template script.
	addList("ADMIN");
	addList("ENTRY");
	addList("HOPPER");
	addList("BAN");

	addSerializableVariables();
}

StructurePermissionList::StructurePermissionList(const StructurePermissionList& spl) : Object() {
	permissionLists = spl.permissionLists;

	addSerializableVariables();
}

void StructurePermissionList::addSerializableVariables() {
	addSerializableVariable("permissionLists", &permissionLists);
}

void StructurePermissionList::sendTo(CreatureObject* creature, const String& listName) {
	ZoneServer* zoneServer = creature->getZoneServer();

	if (!permissionLists.contains(listName))
		return;

	PermissionListCreateMessage* listMsg = new PermissionListCreateMessage(listName);

	SortedVector<String>* list = &permissionLists.get(listName);

	for (int i = 0; i < list->size(); ++i)
		listMsg->addName(list->get(i));

	listMsg->generateMessage();
	creature->sendMessage(listMsg);
}

int StructurePermissionList::togglePermission(const String& listName, const String& playerName) {
	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	String name = playerName.toLowerCase();

	//If they exist, remove them.
	if (list->contains(name)) {
		list->drop(name);
		return REVOKED;
	}

	list->put(name);
	return GRANTED;
}

int StructurePermissionList::grantPermission(const String& listName, const String& playerName) {
	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	list->put(playerName.toLowerCase());
	return GRANTED;
}

int StructurePermissionList::revokePermission(const String& listName, const String& playerName) {
	if (!permissionLists.contains(listName))
		return LISTNOTFOUND;

	SortedVector<String>* list = &permissionLists.get(listName);

	list->drop(playerName.toLowerCase());
	return REVOKED;
}

int StructurePermissionList::revokeAllPermissions(const String& playerName) {
	for (int i = 0; i < permissionLists.size(); ++i) {
		SortedVector<String>* list = &permissionLists.get(i);

		list->drop(playerName.toLowerCase());
	}

	return REVOKED;
}
