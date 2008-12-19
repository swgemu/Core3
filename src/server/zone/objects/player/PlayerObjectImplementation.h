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

#ifndef PLAYEROBJECTIMPLEMENTATION_H_
#define PLAYEROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../scene/SceneObject.h"
#include "../scene/SceneObjectImplementation.h"
#include "professions/XpMap.h"

#include "../../packets/player/PlayerObjectDeltaMessage9.h"

#include "FriendsList.h"
#include "FriendsListImplementation.h"

#include "IgnoreList.h"
#include "IgnoreListImplementation.h"

class Player;
class FriendsList;
class IgnoreList;

class PlayerObjectImplementation : public PlayerObjectServant {
	Player* player;

	// PLAY8 operands
	uint32 forcePower;
	uint32 forcePowerMax;

	uint32 forceRegen;

	// PLAY8 operands
	uint32 jediState;
	XpMap experienceList;
	uint32 experienceListCount;
	String experienceData;
	uint32 waypointListCount;
	VectorMap<uint64, WaypointObject*> waypointList;

	// PLAY3 operands
	uint32 characterBitmask;
	String title;

	// Play9 operands
	uint32 drinkFilling;
	uint32 drinkFillingMax;

	uint32 foodFilling;
	uint32 foodFillingMax;

	FriendsList* friendsList;

	uint32 reverseFriendListListCount;
	Vector<uint64> reverseFriendList;

	IgnoreList* ignoreList;

	uint32 guildPermissionsBitmask;

	uint32 adminLevel;

public:

	const static int LFG = 1;
	const static int NEWBIEHELPER = 2;
	const static int ROLEPLAYER = 4;
	const static int AFK = 0x80;
	const static int LD = 0x100;
	const static int FACTIONRANK = 0x200;
	const static int ANONYMOUS = 0x80000000;

public:
	PlayerObjectImplementation(Player* player);

	~PlayerObjectImplementation();

	void sendToOwner();

	void sendTo(Player* player, bool doClose = true);

	bool isJedi() {
		return jediState != 0;
	}

	bool isOnFullForce() {
		return forcePower == getForcePowerMax();
	}

	inline uint32 getCharacterBitmask() {
		return characterBitmask;
	}

	bool setCharacterBit(uint32 bit, bool updateClient = false);
	bool clearCharacterBit(uint32 bit, bool updateClient = false);

	int getExperience(const String& xpType) {
		return experienceList.get(xpType);
	}
	
	void addExperience(const String& xpType, int xp, bool updateClient);
	void removeExperience(const String& xpType, int xp, bool updateClient);
	void loadExperience(const String& xpStr);
	String& saveExperience();

	void setCurrentTitle(String& nTitle, bool updateClient);

	inline uint32 getForcePower() {
		return forcePower;
	}

	void setForcePowerBar(uint32 fp);
	void updateMaxForcePowerBar(bool updateClient = true);

	inline void setForcePower(uint32 fp) {
		forcePower = fp;
	}

	inline uint32 getForcePowerMax() {
		forcePowerMax = player->getSkillMod("jedi_force_power_max");
		return forcePowerMax;
	}

	inline uint32 getForceRegen() {
		forceRegen = player->getSkillMod("jedi_force_power_regen");
		return forceRegen;
	}

	inline uint32 getJediState() {
		return jediState;
	}

	inline uint32 getDrinkFilling() {
		return drinkFilling;
	}

	inline uint32 getDrinkFillingMax() {
		return drinkFillingMax;
	}

	inline uint32 getFoodFilling() {
		return foodFilling;
	}

	inline uint32 getFoodFillingMax() {
		return foodFillingMax;
	}

	inline bool isDigesting() {
		if (getDrinkFilling() > 0 || getFoodFilling() > 0)
			return true;

		return false;
	}

	inline void setDrinkFilling(uint32 filling, bool updateClient = true) {
		drinkFilling = filling;

		if (updateClient) {
			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9((PlayerObject*) _this);
			dplay9->updateStomachFilling();
			dplay9->close();
			player->sendMessage(dplay9);
		}
	}

	inline void setDrinkFillingMax(uint32 filling) {
		drinkFillingMax = filling;
	}

	inline void setFoodFilling(uint32 filling, bool updateClient = true) {
		foodFilling = filling;

		if (updateClient) {
			PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9((PlayerObject*) _this);
			dplay9->updateStomachFilling();
			dplay9->close();
			player->sendMessage(dplay9);
		}
	}

	inline void setFoodFillingMax(uint32 filling) {
		foodFillingMax = filling;
	}


	inline void changeDrinkFilling(uint32 filling, bool updateClient = true) {
		setDrinkFilling(MAX(MIN(drinkFillingMax, filling + drinkFilling),0), updateClient);
	}

	inline void changeFoodFilling(uint32 filling, bool updateClient = true) {
		setFoodFilling(MAX(MIN(foodFillingMax, filling + foodFilling), 0), updateClient);
	}

	void updateWaypoint(WaypointObject* wp);

	WaypointObject* getWaypoint(uint64 id);

	int getWaypointListSize();

	void addWaypoint(WaypointObject* wp, bool updateClient);

	bool removeWaypoint(WaypointObject* wp, bool updateClient);

	inline Player* getPlayer() {
		return player;
	}

	inline String& getCurrentTitle() {
		return title;
	}

	inline void setTitle(String& temptitle) {
		title = temptitle;
	}

	inline uint32 getExperienceListCount() {
		return experienceListCount;
	}

	inline uint32 getNewExperienceListCount(int cnt) {
		return experienceListCount += 1;
	}

	inline uint32 getWaypointListCount() {
		return waypointListCount;
	}

	inline uint32 getNewWaypointListCount(int cnt) {
		return waypointListCount += cnt;
	}



	//Friendlist
	inline FriendsList* getFriendsList() {
		return friendsList;
	}

	inline void addFriend(String& name, String& inServer) {
		friendsList->addFriend(name, inServer);
	}

	void pokeReverseFriendList(uint64 playID);
	void removeFromReverseFriendList(uint64 playID);

	int getReverseFriendListSize() {
		return reverseFriendList.size();
	}

	uint64 getReverseFriendListEntry(int i) {
		return reverseFriendList.get(i);
	}

	inline void friendsMagicNumberReset() {
		friendsList->friendsMagicNumberReset();
	}

	inline void removeFriend(String& name) {
		friendsList->removeFriend(name);
	}

	inline void saveFriends() {
		friendsList->saveFriends();
	}

	inline void loadFriends() {
		friendsList->loadFriends();
	}

	inline void updateAllFriends(PlayerObject* playerObject) {
		friendsList->updateAllFriends(playerObject);
	}

	inline void findFriend(String& name, PlayerManager* playerManager) {
		friendsList->findFriend(name, playerManager);
	}

	//Ignorelist
	inline IgnoreList* getIgnoreList() {
		return ignoreList;
	}

	inline void addIgnore(String& name, String& inServer) {
		ignoreList->addIgnore(name, inServer);
	}

	inline void ignoreMagicNumberReset() {
		ignoreList->ignoreMagicNumberReset();
	}

	inline void removeIgnore(String& name) {
		ignoreList->removeIgnore(name);
	}

	inline void saveIgnore() {
		ignoreList->saveIgnore();
	}

	inline void loadIgnore() {
		ignoreList->loadIgnore();
	}

	void setAdminLevel(uint32 level, bool updateClient = true);

	inline uint32 getAdminLevel() {
		return adminLevel;
	}

	void saveWaypoints(Player* player);
	WaypointObject* searchWaypoint(Player* play, const String& name, int mode);

	friend class Player;

	friend class PlayerObjectMessage3;
	friend class PlayerObjectMessage6;
	friend class PlayerObjectMessage8;
	friend class PlayerObjectMessage9;
	friend class PlayerObjectDeltaMessage3;
	friend class PlayerObjectDeltaMessage6;
	friend class PlayerObjectDeltaMessage8;
	friend class PlayerObjectDeltaMessage9;

	friend class PlayerManager;

};

#endif /*PLAYEROBJECTIMPLEMENTATION_H_*/
