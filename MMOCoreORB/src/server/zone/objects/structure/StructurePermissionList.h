/*
 * StructurePermissionList.h
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#ifndef STRUCTUREPERMISSIONLIST_H_
#define STRUCTUREPERMISSIONLIST_H_

#include "engine/engine.h"
#include "engine/util/json_utils.h"

#include "server/zone/objects/creature/CreatureObject.h"

class StructurePermissionList : public Object {
	VectorMap<String, SortedVector<String> > permissionLists;
	VectorMap<String, SortedVector<uint64> > idPermissionLists;
	String ownerName;
	uint64 ownerID;
	mutable ReadWriteLock lock;

private:
	int writeObjectMembers(ObjectOutputStream* stream);
	bool readObjectMember(ObjectInputStream* stream, const String& name);

public:
	enum {
		LISTNOTFOUND    = 0xFF,
		GRANTED         = 0x00,
		REVOKED         = 0x01,
		CANTCHANGEOWNER = 0x02
	};

	enum {
		MAX_ENTRIES = 50
	};

public:
	StructurePermissionList();
	StructurePermissionList(const StructurePermissionList& spl);

	StructurePermissionList& operator=(const StructurePermissionList& list);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	/**
	 * Sends the list to the creature so that it appears in Sui format.
	 * @param creature The creature receiving the list.
	 * @param listName The list to be displayed.
	 */
	void sendTo(CreatureObject* creature, const String& listName);

	/**
	 * Toggles permission on the list for the player.
	 * @param listName The list the player is being added/removed to/from.
	 * @param objectID The oid of the player/guild.
	 * @return Returns either GRANTED or REVOKED depending on the operation that is performed.
	 */
	int togglePermission(const String& listName, const uint64 objectID);

	int grantPermission(const String& listName, const uint64 objectID);
	int revokePermission(const String& listName, const uint64 objectID);
	int revokeAllPermissions(const uint64 objectID);
	void revokeAllPermissions();

	friend void to_json(nlohmann::json& j, const StructurePermissionList& p);

	void setOwner(const uint64 objectID) {
		Locker locker(&lock);

		ownerID = objectID;
	}

	inline uint64 getOwner() const {
		return ownerID;
	}

	/**
	 * Checks to see if the specified player name is on the specified permission list.
	 * @param listName The list to check.
	 * @param playerName The player name to check.
	 * @return Returns false if the permission list does not exist, or the player name is not found in the list.
	 */
	bool isOnPermissionList(const String& listName, const uint64 objectID) const;

	/**
	 * Checks to see if the number of entries in the specified list exceeds or is equal to the max number of entries allowed per list.
	 * @param listName The list that is being checked.
	 * @return Returns true if the permission list does not exist or it exceeds or equals the the max number of entries allowed per list.
	 */
	bool isListFull(const String& listName) const;

	/**
	 * Adds the specified list name to this permission list.
	 * @param listName The list to add.
	 */
	void addList(const String& listName) {
		Locker locker(&lock);

		if (idPermissionLists.contains(listName))
			return;

		SortedVector<uint64> list;
		list.setNoDuplicateInsertPlan();
		idPermissionLists.put(listName, list);
	}

	/**
	 * Drops the specified list name from this permission list.
	 * @param listName The list to drop.
	 */
	void dropList(const String& listName) {
		Locker locker(&lock);

		idPermissionLists.drop(listName);
	}

	/**
	 * Checks to see if the specified list name exists.
	 * @param listName The list to check for.
	 * @return Returns true if the specified list exists, or false if it does not exist.
	 */
	bool containsList(const String& listName) const {
		ReadLocker locker(&lock);

		return idPermissionLists.contains(listName);
	}

	void migrateLists(ZoneServer* zoneServer, uint64 ownerObjectID);
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
