/*
 * StructurePermissionList.h
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#ifndef STRUCTUREPERMISSIONLIST_H_
#define STRUCTUREPERMISSIONLIST_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"

class StructurePermissionList : public Serializable {
	VectorMap<String, SortedVector<String> > permissionLists;
	String ownerName;

	void addSerializableVariables();

public:
	static const int LISTNOTFOUND = 0xFF;
	static const int GRANTED = 0x00;
	static const int REVOKED = 0x01;
	static const int CANTCHANGEOWNER = 0x02;

	static const int MAX_ENTRIES = 50;

public:
	StructurePermissionList();
	StructurePermissionList(const StructurePermissionList& spl);

	/**
	 * Sends the list to the creature so that it appears in Sui format.
	 * @param creature The creature receiving the list.
	 * @param listName The list to be displayed.
	 */
	void sendTo(CreatureObject* creature, const String& listName);

	/**
	 * Toggles permission on the list for the player.
	 * @param listName The list the player is being added/removed to/from.
	 * @param playerName The name of the player.
	 * @return Returns either GRANTED or REVOKED depending on the operation that is performed.
	 */
	int togglePermission(const String& listName, const String& playerName);

	int grantPermission(const String& listName, const String& playerName);
	int revokePermission(const String& listName, const String& playerName);
	int revokeAllPermissions(const String& playerName);

	void setOwnerName(const String& name) {
		ownerName = name;
	}

	/**
	 * Checks to see if the specified player name is on the specified permission list.
	 * @param listName The list to check.
	 * @param playerName The player name to check.
	 * @return Returns false if the permission list does not exist, or the player name is not found in the list.
	 */
	inline bool isOnPermissionList(const String& listName, const String& playerName) {
		if (!permissionLists.contains(listName))
			return false;

		SortedVector<String>* list = &permissionLists.get(listName);

		return list->contains(playerName.toLowerCase());
	}

	/**
	 * Checks to see if the number of entries in the specified list exceeds or is equal to the max number of entries allowed per list.
	 * @param listName The list that is being checked.
	 * @return Returns true if the permission list does not exist or it exceeds or equals the the max number of entries allowed per list.
	 */
	inline bool isListFull(const String& listName) {
		if (!permissionLists.contains(listName))
			return true;

		SortedVector<String>* list = &permissionLists.get(listName);

		return list->size() >= MAX_ENTRIES;
	}

	/**
	 * Adds the specified list name to this permission list.
	 * @param listName The list to add.
	 */
	inline void addList(const String& listName) {
		if (permissionLists.contains(listName))
			return;

		SortedVector<String> list;
		list.setNoDuplicateInsertPlan();
		permissionLists.put(listName, list);
	}

	/**
	 * Drops the specified list name from this permission list.
	 * @param listName The list to drop.
	 */
	inline void dropList(const String& listName) {
		permissionLists.drop(listName);
	}

	/**
	 * Checks to see if the specified list name exists.
	 * @param listName The list to check for.
	 * @return Returns true if the specified list exists, or false if it does not exist.
	 */
	inline bool containsList(const String& listName) {
		return permissionLists.contains(listName);
	}
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
