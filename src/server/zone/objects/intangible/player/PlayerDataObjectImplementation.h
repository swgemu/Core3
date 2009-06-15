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

#ifndef PLAYERDATAOBJECTIMPLEMENTATION_H_
#define PLAYERDATAOBJECTIMPLEMENTATION_H_

#include "PlayerDataObject.h"
#include "FriendsList.h"
#include "../../../ZoneClientSession.h"
#include "../../tangible/creature/player/PlayerObject.h"

class PlayerObject;
class PlayerDataObjectImplementation : public PlayerDataObjectServant {
protected:
	ManagedReference<ZoneClientSession> zoneClient;
	ManagedReference<PlayerObject> linkedPlayer;
	//WaypointList* waypointList;
	FriendsList* friendsList;
	FriendsList* ignoreList;
	//SkillsList* skillsList;
	//DraftSchematicsList* draftSchematics;
	//ExperienceList* experienceList;

	String currentTitle;

	uint32 forcePower;
	uint32 forcePowerMax;

	uint32 characterBitmask;
	uint32 languageID;
	uint32 fillingFood;
	uint32 fillingFoodMax;
	uint32 fillingDrink;
	uint32 fillingDrinkMax;
	uint32 jediState;

	uint8 accessLevel;

public:
	//Client side permissions - 0 = Player
	static const uint8 CSR = 1;
	static const uint8 DEVELOPER = 2;

public:
	PlayerDataObjectImplementation(uint64 objectid);
	~PlayerDataObjectImplementation();

	void sendTo(PlayerObject* player, bool close);
	void sendToOwner();

	//Setters
	inline void setClient(ZoneClientSession* client) {
		zoneClient = client;
	}

	inline void setAccessLevel(uint8 level) {
		accessLevel = level;
	}

	inline void setLinkedPlayer(PlayerObject* player) {
		linkedPlayer = player;
	}

	inline void setCharacterBitmask(uint32 bitmask) {
		characterBitmask = bitmask;
	}

	inline void setCurrentTitle(const String& title) {
		currentTitle = title;
	}

	inline void setForcePower(uint32 power) {
		forcePower = power;
	}

	inline void setForcePowerMax(uint32 power) {
		forcePowerMax = power;
	}

	inline void setFoodFilling(uint32 filling) {
		fillingFood = filling;
	}

	inline void setFoodFillingMax(uint32 filling) {
		fillingFoodMax = filling;
	}

	inline void setDrinkFilling(uint32 filling) {
		fillingDrink = filling;
	}

	inline void setDrinkFillingMax(uint32 filling) {
		fillingDrinkMax = filling;
	}

	inline void setLanguageID(uint32 id) {
		languageID = id;
	}

	inline void setJediState(uint32 jedistate) {
		jediState = jedistate;
	}

	//Getters
	inline ZoneClientSession* getClient() {
		return zoneClient;
	}

	inline uint8 getAccessLevel() {
		return accessLevel;
	}

	inline PlayerObject* getLinkedPlayer() {
		return linkedPlayer.get();
	}

	inline uint32 getCharacterBitmask() {
		return characterBitmask;
	}

	inline String& getCurrentTitle() {
		return currentTitle;
	}

	inline uint32 getForcePower() {
		return forcePower;
	}

	inline uint32 getForcePowerMax() {
		return forcePowerMax;
	}

	inline uint32 getFoodFilling() {
		return fillingFood;
	}

	inline uint32 getFoodFillingMax() {
		return fillingFoodMax;
	}

	inline uint32 getDrinkFilling() {
		return fillingDrink;
	}

	inline uint32 getDrinkFillingMax() {
		return fillingDrinkMax;
	}

	inline uint32 getLanguageID() {
		return languageID;
	}

	inline uint32 getJediState() {
		return jediState;
	}

	inline bool isPrivileged() {
		return (accessLevel > 0);
	}
};

#endif /*PLAYERDATAOBJECTIMPLEMENTATION_H_*/
