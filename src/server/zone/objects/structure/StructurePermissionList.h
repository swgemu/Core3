/*
 * StructurePermissionList.h
 *
 *  Created on: May 9, 2010
 *      Author: crush
 */

#ifndef STRUCTUREPERMISSIONLIST_H_
#define STRUCTUREPERMISSIONLIST_H_

#include "engine/engine.h"

#include "server/zone/objects/player/PlayerCreature.h"

class StructurePermissionList : public VectorMap<uint64, uint8> {
public:
	//List Permissions
	static const uint8 BANLIST = 0x01;
	static const uint8 HOPPERLIST = 0x02;
	static const uint8 ENTRYLIST = 0x04;
	static const uint8 VENDORLIST = 0x08;
	static const uint8 ADMINLIST = 0x10;

	static const uint8 OWNER = ~BANLIST;
	static const uint8 VENDOR = VENDORLIST | ENTRYLIST;
	static const uint8 ADMIN = ADMINLIST | VENDOR | HOPPERLIST;

public:
	StructurePermissionList();

	void sendTo(PlayerCreature* player, uint8 permission);
	void sendTo(PlayerCreature* player, const String& listName);

	bool addPermission(uint64 playerID, uint8 permission);
	bool removePermission(uint64 playerID, uint8 permission);

	String getListName(uint8 permission);
	uint8 getPermissionFromListName(const String& listName);

	bool hasPermission(uint64 playerID, uint8 permission) {
		return (get(playerID) & permission);
	}

	inline bool isOwner(uint64 playerID) {
		return (get(playerID) & OWNER);
	}

	inline bool isOnAdminList(uint64 playerID) {
		return (get(playerID) & ADMINLIST);
	}

	inline bool isOnBanList(uint64 playerID) {
		return (get(playerID) & BANLIST);
	}

	inline bool isOnEntryList(uint64 playerID) {
		return (get(playerID) & ENTRYLIST);
	}

	inline bool isOnVendorList(uint64 playerID) {
		return (get(playerID) & VENDORLIST);
	}

	inline bool isOnHopperList(uint64 playerID) {
		return (get(playerID) & HOPPERLIST);
	}
};

#endif /* STRUCTUREPERMISSIONLIST_H_ */
