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

#ifndef ITEMMANAGERIMPLEMENTATION_H_
#define ITEMMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "../../../db/ServerDatabase.h"

#include "../../objects/player/Player.h"

#include "../../objects/tangible/deed/DeedObject.h"

#include "ItemManager.h"

#include "StartingItemList.h"
#include "../../objects/creature/bluefrog/BlueFrogItemSet.h"
#include "../../objects/creature/bluefrog/BlueFrogProfessionSet.h"

class ZoneServer;
class ZoneProcessServerImplementation;

class TangibleObject;

class Weapon;
class Armor;
class ResourceContainer;

class ItemManagerImplementation : public ItemManagerServant, public Lua {
	ZoneServer* server;
	ZoneProcessServerImplementation* pServer;

	uint64 nextStaticItemID;

	static StartingItemList * startingItems;
	static BlueFrogItemSet * bfItemSet;
	static BlueFrogProfessionSet * bfProfSet;

	static bool bfEnabled;

	void registerFunctions();
	void registerGlobals();
	static int addPlayerItem(lua_State * l);
	static int addBFItem(lua_State * l);
	static int addBFProf(lua_State * l);
	static int addBFGroup(lua_State * l);
	static int runItemLUAFile(lua_State* L);

	static int enableBlueFrogs(lua_State* L) {
		bfEnabled = true;

		return 1;
	}

public:
	ItemManagerImplementation(ZoneServer* serv, ZoneProcessServerImplementation* pServ);
	~ItemManagerImplementation();

	void loadStaticWorldObjects();

	void loadPlayerItems(Player* player);
	TangibleObject* getPlayerItem(Player* player, uint64 objectid);
	void loadDefaultPlayerItems(Player* player);
	void loadDefaultDatapadItems(Player* player);

	void loadPlayerDatapadItems(Player* player);

	TangibleObject* createPlayerObject(Player* player, ResultSet* result);

	static TangibleObject* createSubObject(uint64 objectid, uint32 objectcrc, const unicode& objectname, const string& objecttemp, bool equipped);

	static TangibleObject* createPlayerObjectTemplate(int objecttype, uint64 objectid, uint32 objectcrc,
			const unicode& objectname, const string& objecttemp, bool equipped,
			bool makeStats, string lootAttributes, int level);

	static TangibleObject* createTemplateFromLua(LuaObject item);

	//TODO: remove this function when a global clone() function is available for all objects
	TangibleObject* clonePlayerObjectTemplate(uint64 objectid, TangibleObject* templ);
	TangibleObject* initializeTangibleForCrafting(int objecttype,
			uint64 objectid, uint32 objectcrc, string objectn,
			string objecttemp, bool equipped);

	void giveBFItemSet(Player * player, string& set);

	void unloadPlayerItems(Player* player);

	void createPlayerItem(Player* player, TangibleObject* item);

	void createPlayerDeed(Player* player, DeedObject* item);

	void deletePlayerItem(Player* player, TangibleObject* item, bool notify);

	void savePlayerItem(Player* player, TangibleObject* item);

	void showDbStats(Player* player);
	void showDbDeleted(Player* player);

	void purgeDbDeleted(Player* player);

	// setters and getters
	inline uint64 getNextStaticObjectID() {
		return ++nextStaticItemID;
	}

	inline bool blueFrogsEnabled() {
		return bfEnabled;
	}

	inline BlueFrogVector * getBFItemList() {
		return bfItemSet->listContents();
	}

	inline BlueFrogVector * getBFProfList(string group = "root") {
		return bfProfSet->listContents(group);
	}

	inline string& getBFProf(string& key) {
		return bfProfSet->get(key);
	}

};

#endif /*ITEMMANAGERIMPLEMENTATION_H_*/





