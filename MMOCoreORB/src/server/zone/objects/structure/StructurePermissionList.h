/*
 * StructurePermissionList.h
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#ifndef STRUCTUREPERMISSIONLIST_H_
#define STRUCTUREPERMISSIONLIST_H_

#include <algorithm>

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/thread/Locker.h"
#include "system/thread/ReadLocker.h"
#include "system/thread/ReadWriteLock.h"
#include "system/util/SortedVector.h"
#include "system/util/VectorMap.h"

namespace server {
namespace zone {
class ZoneServer;
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
}  // namespace sys

class StructurePermissionList : public Object {
	VectorMap<String, SortedVector<String> > permissionLists;
	VectorMap<String, SortedVector<uint64> > idPermissionLists;
	String ownerName;
	uint64 ownerID;
	ReadWriteLock lock;

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
	inline bool isOnPermissionList(const String& listName, const uint64 objectID) {
		ReadLocker locker(&lock);

		if (listName != "BAN" && objectID == ownerID)
			return true;

		if (!idPermissionLists.contains(listName))
			return false;

		SortedVector<uint64>* list = &idPermissionLists.get(listName);

		return list->contains(objectID);
	}

	/**
	 * Checks to see if the number of entries in the specified list exceeds or is equal to the max number of entries allowed per list.
	 * @param listName The list that is being checked.
	 * @return Returns true if the permission list does not exist or it exceeds or equals the the max number of entries allowed per list.
	 */
	inline bool isListFull(const String& listName) {
		ReadLocker locker(&lock);

		if (!idPermissionLists.contains(listName))
			return true;

		SortedVector<uint64>* list = &idPermissionLists.get(listName);

		return list->size() >= MAX_ENTRIES;
	}

	/**
	 * Adds the specified list name to this permission list.
	 * @param listName The list to add.
	 */
	inline void addList(const String& listName) {
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
	inline void dropList(const String& listName) {
		Locker locker(&lock);

		idPermissionLists.drop(listName);
	}

	/**
	 * Checks to see if the specified list name exists.
	 * @param listName The list to check for.
	 * @return Returns true if the specified list exists, or false if it does not exist.
	 */
	inline bool containsList(const String& listName) {
		ReadLocker locker(&lock);

		return idPermissionLists.contains(listName);
	}

	void migrateLists(ZoneServer* zoneServer, uint64 ownerObjectID);
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
