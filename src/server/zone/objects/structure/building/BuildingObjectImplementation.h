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

#include "BuildingObject.h"
#include "../StructurePermissionList.h"

class BuildingObjectImplementation : public QuadTree, public BuildingObjectServant {
protected:
	StructurePermissionList* permissionList;

	SortedVector<CellObject*> cells;
	SortedVector<SceneObject*> sceneObjects;

	uint8 buildingType;

	bool staticBuilding;
	bool publicStructure;

	void init();

public:
	// Using the Building Types from Planet Map
	static const uint8 UNKNOWN = 1;
	static const uint8 BANK = 2;
	static const uint8 CANTINA = 3;
	static const uint8 CAPITOL = 4;
	static const uint8 CLONING_FACILITY = 5;
	static const uint8 GARAGE = 6;
	static const uint8 GUILD = 7; // Should just be a "parent" type?
	static const uint8 GUILD_COMBAT = 8;
	static const uint8 GUILD_COMMERCE = 9;
	static const uint8 GUILD_THEATER = 10;
	static const uint8 GUILD_UNIVERSITY = 11;
	static const uint8 HOTEL = 12;
	static const uint8 MEDICAL_CENTER = 13;
	static const uint8 SHUTTLEPORT = 14;
	static const uint8 STARPORT = 15;
	static const uint8 THEMEPARK = 16;
/*	static const uint8 CITY = 17;
	static const uint8 WAYPOINT = 18;
	static const uint8 TRAINER = 19; //category
	static const uint8 trainer_brawler = 20;
	static const uint8 trainer_artisan = 21;
	static const uint8 trainer_scout = 22;
	static const uint8 trainer_marksman = 23;
	static const uint8 trainer_entertainer = 24;
	static const uint8 trainer_medic = 25;*/
	static const uint8 JUNKSHOP = 26;
	static const uint8 TAVERN = 27;
	static const uint8 BARRACKS = 28;
/*	static const uint8 vendor = 29; // category
	static const uint8 vendor_armor = 30;
	static const uint8 vendor_clothing = 31;
	static const uint8 vendor_components = 32;
	static const uint8 vendor_droids = 33;
	static const uint8 vendor_equipment = 34;
	static const uint8 vendor_food = 35;
	static const uint8 vendor_housing = 36;
	static const uint8 vendor_resources = 37;
	static const uint8 vendor_tools = 38;
	static const uint8 vendor_weapons = 39;
	static const uint8 vendor_junk = 40;
	static const uint8 terminal = 41;
	static const uint8 terminal_bank = 42;
	static const uint8 terminal_bazaar = 43;
	static const uint8 terminal_mission = 44;
	static const uint8 REBEL = 45; // Should just be category
	static const uint8 IMPERIAL = 46;*/
	static const uint8 REBEL_HQ = 47;
	static const uint8 IMPERIAL_HQ = 48;
	static const uint8 CAMP = 49;
	static const uint8 CITYHALL = 50;
	static const uint8 THEATER = 51;
/*	static const uint8 vendor_pets = 52;
	static const uint8 vendor_medical = 53;*/
	static const uint8 POI = 54;
	/*static const uint8 GARAGE = 55; // weird duplicate of garage = 6? */
	static const uint8 MUSEUM = 56;
	static const uint8 SALON = 57;
/*	static const uint8 space = 58; // parent category
	static const uint8 space_recruiter = 59;
	static const uint8 space_chassis_broker = 60;
	static const uint8 space_chassis = 61;
	static const uint8 trainer_starfighter_engineer = 62;
	static const uint8 trainer_shipwright = 63;
	static const uint8 trainer_pilot_privateer = 64;
	static const uint8 trainer_pilot_rebel = 65;
	static const uint8 trainer_pilot_imperial = 66;
	static const uint8 vendor_ships = 67; */
	// SF = PvP bases
	static const uint8 SF_REBEL_FORWARD_BASE = 68;
	static const uint8 SF_IMPERIAL_FORWARD_BASE = 69;
	static const uint8 SF_REBEL_MINOR_BASE = 70;
	static const uint8 SF_IMPERIAL_MINOR_BASE = 71;
	static const uint8 SF_REBEL_MAJOR_BASE = 72;
	static const uint8 SF_IMPERIAL_MAJOR_BASE = 73;
	/** Overlaps with the non SF version...this is where I start to diverge from planetmapcategories
	sf_rebel_hq = 47
	sf_imperial_hq = 48 */
	static const uint8 SF_REBEL_HQ = 74;
	static const uint8 SF_IMPERIAL_HQ = 75;
	// Weren't in here but lets create non SF types of faction buildings (HQs are 47/48)
	static const uint8 REBEL_FORWARD_BASE = 76;
	static const uint8 IMPERIAL_FORWARD_BASE = 77;
	static const uint8 REBEL_MINOR_BASE = 78;
	static const uint8 IMPERIAL_MINOR_BASE = 79;
	static const uint8 REBEL_MAJOR_BASE = 80;
	static const uint8 IMPERIAL_MAJOR_BASE = 81;

public:
	BuildingObjectImplementation(uint64 objid, uint8 buildingtype = UNKNOWN, bool staticbuilding = false);
	~BuildingObjectImplementation();

	void serialize();
	void deserialize();

	void removeFromZone(bool doLock = true);
	void notifyInsert(QuadTreeEntry* obj);
	void notifyDissapear(QuadTreeEntry* obj);

	void notifyInsertToZone(SceneObject* object);

	void putPlayersInWorld();

	void parseItemAttributes();

	void sendTo(Player* player, bool close = true);
	virtual void sendCellsTo(Player* player, bool close = true);
	virtual void sendCellUpdatesTo(Player* player);
	virtual void sendPermissionListTo(Player* player, const String& listname);
	virtual void sendConfirmDestroyTo(Player* player);

	void addCell(CellObject* cell);
	void addSceneObject(SceneObject* sceneobject);

	bool containsCell(uint64 cellid);

	void modifyPermissionList(Player* player, const String& listname, const String& entryname, bool add = true);

	//Setters
	inline void setBuildingType(uint8 type) {
		buildingType = type;
		String attr("buildingType");
		itemAttributes->setIntAttribute(attr, buildingType);
	}

	inline void setStaticBuilding(bool value) {
		staticBuilding = value;
		String attr("staticBuilding");
		itemAttributes->setBooleanAttribute(attr, staticBuilding);
	}

	inline void setPublicStructure(bool value) {
		publicStructure = value;
		String attr("publicStructure");
		itemAttributes->setBooleanAttribute(attr, publicStructure);
	}


	inline void setPermissionsList(const String& permissionsString) {
		permissionList->parsePermissionsString(permissionsString);
	}

	//Getters
	inline uint8 getBuildingType() {
		return buildingType;
	}

	inline CellObject* getCell(int idx) {
		return cells.get(idx);
	}

	inline uint32 getCellCount() {
		return cells.size();
	}

	inline bool isCloningFacility() {
		return (buildingType == CLONING_FACILITY);
	}

	inline bool isPublicStructure() {
		return publicStructure;
	}

	inline bool isStaticBuilding() {
		return staticBuilding;
	}

	inline bool isOwnedBy(Player* player) {
		return (getOwnerCharacterID() == player->getCharacterID());
	}

	inline bool isOnAdminList(Player* player) {
		return (isOwnedBy(player) || permissionList->isOnAdminList(player));
	}

	inline bool isOnEntryList(Player* player) {
		return (isOwnedBy(player) || permissionList->isOnEntryList(player));
	}

	inline bool isOnHopperList(Player* player) {
		return (isOwnedBy(player) || permissionList->isOnHopperList(player));
	}

	inline bool isOnBanList(Player* player) {
		return permissionList->isOnBanList(player);
	}
};

#endif /*BUILDINGOBJECTIMPLEMENTATION_H_*/
