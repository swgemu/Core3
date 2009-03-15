/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef BUILDINGOBJECTIMPLEMENTATION_H_
#define BUILDINGOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

class CellObject;
class Player;
class Guild;
class Zone;

#include "BuildingObject.h"

#include "../tangible/ItemAttributes.h"

#include "StructurePermissionList.h"

#include "../player/sui/listbox/SuiListBox.h"

class BuildingObjectImplementation : public QuadTree, public BuildingObjectServant {
	SortedVector<CellObject*> cells;
	SortedVector<SceneObject*> sceneObjects;

	UnicodeString buildingName;
	String defaultName;

	String owner;
	uint64 ownerID;

	StructurePermissionList* permissionList;

	bool publicEntry;
	uint32 accessFee;
	uint32 accessTime; //In minutes

	int buildingType;

	bool persistent, updated;

	bool staticBuilding;

	bool storageLoaded;

	String templateName;

	ItemAttributes* itemAttributes;
	String attributeString;
public:
	// Using the Building Types from Planet Map - comment out the non buildings :)
	static const int UNKNOWN = 1;
	static const int BANK = 2;
	static const int CANTINA = 3;
	static const int CAPITOL = 4;
	static const int CLONING_FACILITY = 5;
	static const int GARAGE = 6;
	static const int GUILD = 7; // Should just be a "parent" type?
	static const int GUILD_COMBAT = 8;
	static const int GUILD_COMMERCE = 9;
	static const int GUILD_THEATER = 10;
	static const int GUILD_UNIVERSITY = 11;
	static const int HOTEL = 12;
	static const int MEDICAL_CENTER = 13;
	static const int SHUTTLEPORT = 14;
	static const int STARPORT = 15;
	static const int THEMEPARK = 16;
/*	static const int CITY = 17;
	static const int WAYPOINT = 18;
	static const int TRAINER = 19; //category
	static const int trainer_brawler = 20;
	static const int trainer_artisan = 21;
	static const int trainer_scout = 22;
	static const int trainer_marksman = 23;
	static const int trainer_entertainer = 24;
	static const int trainer_medic = 25;*/
	static const int JUNKSHOP = 26;
	static const int TAVERN = 27;
	static const int BARRACKS = 28;
/*	static const int vendor = 29; // category
	static const int vendor_armor = 30;
	static const int vendor_clothing = 31;
	static const int vendor_components = 32;
	static const int vendor_droids = 33;
	static const int vendor_equipment = 34;
	static const int vendor_food = 35;
	static const int vendor_housing = 36;
	static const int vendor_resources = 37;
	static const int vendor_tools = 38;
	static const int vendor_weapons = 39;
	static const int vendor_junk = 40;
	static const int terminal = 41;
	static const int terminal_bank = 42;
	static const int terminal_bazaar = 43;
	static const int terminal_mission = 44;
	static const int REBEL = 45; // SHould just be category
	static const int IMPERIAL = 46;*/
	static const int REBEL_HQ = 47;
	static const int IMPERIAL_HQ = 48;
	/*static const int CAMP = 49;*/
	static const int CITYHALL = 50;
	static const int THEATER = 51;
/*	static const int vendor_pets = 52;
	static const int vendor_medical = 53;
	static const int POI = 54;
	static const int GARAGE = 55; // weird duplicate of garage = 6? */
	static const int MUSEUM = 56;
	static const int SALON = 57;
/*	static const int space = 58; // parent category
	static const int space_recruiter = 59;
	static const int space_chassis_broker = 60;
	static const int space_chassis = 61;
	static const int trainer_starfighter_engineer = 62;
	static const int trainer_shipwright = 63;
	static const int trainer_pilot_privateer = 64;
	static const int trainer_pilot_rebel = 65;
	static const int trainer_pilot_imperial = 66;
	static const int vendor_ships = 67; */
	// SF = PvP bases
	static const int SF_REBEL_FORWARD_BASE = 68;
	static const int SF_IMPERIAL_FORWARD_BASE = 69;
	static const int SF_REBEL_MINOR_BASE = 70;
	static const int SF_IMPERIAL_MINOR_BASE = 71;
	static const int SF_REBEL_MAJOR_BASE = 72;
	static const int SF_IMPERIAL_MAJOR_BASE = 73;
	/** Overlaps with the non SF version...this is where I start to diverge from planetmapcategories
	sf_rebel_hq = 47
	sf_imperial_hq = 48 */
	static const int SF_REBEL_HQ = 74;
	static const int SF_IMPERIAL_HQ = 75;
	// Weren't in here but lets create non SF types of faction buildings (HQs are 47/48)
	static const int REBEL_FORWARD_BASE = 76;
	static const int IMPERIAL_FORWARD_BASE = 77;
	static const int REBEL_MINOR_BASE = 78;
	static const int IMPERIAL_MINOR_BASE = 79;
	static const int REBEL_MAJOR_BASE = 80;
	static const int IMPERIAL_MAJOR_BASE = 81;

public:
	BuildingObjectImplementation(uint64 oid, bool staticBuild, int bType = UNKNOWN);
	~BuildingObjectImplementation();

	void removeFromZone(bool doLock = true);
	void putPlayersInWorld();

	void addSceneObject(SceneObject* sceneObject);

	void givePermission(Player* enforcer, Player* recipient, uint8 permission) {
		permissionList->givePermission(enforcer, recipient, permission);
	}

	void givePermission(Player* enforcer, Guild* guild, uint8 permission) {
		permissionList->givePermission(enforcer, guild, permission);
	}

	void givePermission(Player* enforcer, const String& entryname, uint8 permission) {
		permissionList->givePermission(enforcer, entryname, permission);
	}

	void revokePermission(Player* enforcer, Player* recipient, uint8 permission) {
		permissionList->revokePermission(enforcer, recipient, permission);
	}

	void revokePermission(Player* enforcer, Guild* guild, uint8 permission) {
		permissionList->revokePermission(enforcer, guild, permission);
	}

	void revokePermission(Player* enforcer, const String& entryname, uint8 permission) {
		permissionList->revokePermission(enforcer, entryname, permission);
	}

	// Attribute Setters
	inline void setOwner(const String own) {
		setUpdated(true);
		owner = own;
		String attr("owner");
		itemAttributes->setStringAttribute(attr, owner);
	}

	inline void setOwnerID(uint64 ownerid) {
		setUpdated(true);
		ownerID = ownerid;
		String attr("ownerID");
		itemAttributes->setUnsignedLongAttribute(attr, ownerID);
	}

	inline void setPublicEntry(bool pubentry) {
		publicEntry = pubentry;
		String attr("publicEntry");
		itemAttributes->setBooleanAttribute(attr, publicEntry);
	}

	inline void setName(const String& n) {
		buildingName = n;
	}

	inline void setName(const UnicodeString& n) {
		buildingName = n;
	}

	// Attribute Getters
	inline String& getOwner() {
		return owner;
	}
	inline uint64 getOwnerID() {
		return ownerID;
	}
	inline UnicodeString& getName() {
		return buildingName;
	}
	inline String& getTemplateName() {
		templateName = "";
		return templateName;
	}

	void parseItemAttributes();
	void sendTo(Player* player, bool doClose = true);
	void sendDestroyTo(Player* player);
	void sendPermissionListTo(Player* player, uint8 listtype);
	void handlePermissionListModify(Player* enforcer, uint8 listtype, String modName, bool doAdd);

	void addCell(CellObject* cell);

	void sendCells(Player* player, bool close);
	void sendCellUpdates(Player* player);

	void notifyInsert(QuadTreeEntry* obj);
	void notifyDissapear(QuadTreeEntry* obj);

	void notifyInsertToZone(SceneObject* object);

	///Used for loading a saved permissions string from the database.
	inline void setPermissionsList(const String& permissionsString) {
		permissionList->setPermissionsFromString(permissionsString);
	}

	inline void setAttributes(String& attributeString) {
		itemAttributes->setAttributes(attributeString);
	}

	inline String& getAttributes() {
		itemAttributes->getAttributeString(attributeString);
		return attributeString;
	}

	inline bool isStatic() {
		return staticBuilding == true;
	}

	inline int getBuildingType() {
		return buildingType;
	}

	inline int getCellCount() {
		return cells.size();
	}

	inline CellObject* getCell(int idx) {
		return cells.get(idx);
	}

	bool hasCell(uint64 cellID);

	inline void setBuildingType(const int type) {
		buildingType = type;
		setDefaultName();
	}

	inline void setPersistent(bool pers) {
		persistent = pers;
	}

	inline void setUpdated(bool upd) {
		updated = upd;
	}

	inline bool isPersistent() {
		return persistent;
	}

	inline bool isUpdated() {
		return updated;
	}

	/// Is the building enterable by the public.
	inline bool isPublic() {
		return publicEntry;
	}

	void setDefaultName();

	inline String& getDefaultName() {
		return defaultName;
	}

	void lock(bool doLock = true) {
		QuadTree::lock(doLock);
	}

	void unlock(bool doLock = true) {
		QuadTree::unlock(doLock);
	}

	//itemStorage getter/setter
	bool getStorageLoaded() {
		return storageLoaded;
	}

	void setStorageLoaded(bool setter) {
		storageLoaded = setter;
	}

	inline bool isCloningFacility() {
		return buildingType == CLONING_FACILITY;
	}

	inline bool isOwnedBy(Player* player) {
		return owner == player->getFirstName().toLowerCase();
	}

	inline bool isOnAdminList(Player* player) {
		return permissionList->isOnAdminList(player);
	}

	inline bool isOnEntryList(Player* player) {
		return permissionList->isOnEntryList(player);
	}

	inline bool isOnHopperList(Player* player) {
		return permissionList->isOnHopperList(player);
	}

	inline bool isOnBanList(Player* player) {
		return permissionList->isOnBanList(player);
	}
};

#endif /*BUILDINGOBJECTIMPLEMENTATION_H_*/
