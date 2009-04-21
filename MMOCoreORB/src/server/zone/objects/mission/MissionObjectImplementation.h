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

#ifndef MISSIONOBJECTIMPLEMENTATION_H_
#define MISSIONOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../scene/SceneObject.h"
#include "../scene/SceneObjectImplementation.h"

#include "../player/Player.h"
#include "../player/PlayerImplementation.h"

#include "../tangible/TangibleObject.h"
#include "../tangible/TangibleObjectImplementation.h"

#include "MissionObjective.h"
#include "MissionObjectiveImplementation.h"

class MissionObjectImplementation : public SceneObjectImplementation {

	String dbKey;

	int terminalMask;
	bool instantComplete; //Complete immediately if all objectives are fulfilled (no return to npc for eval)
	bool completed;
	bool failed;
	String statusStr; // Status string that gives readable details on what is/isnt complete

	//Owner of mission (might change to Creature so AI can run missions..?)
	ManagedReference<Player> ownerObject;

	Container* deliverContainer;
	Container* awardContainer;

	Vector<MissionObjective*> objectiveList;
	String objectiveDefaults;

	//MISO3:
	String typeStr; //3 BASELINE ONLY
	uint32 descKey; //4 - connected to 0B
	uint32 titleKey; //4 - connected to 0C
	uint32 difficultyLevel; //5
	//6:
		float destX;
		float destY;
		uint32 destPlanetCrc;
	//
	UnicodeString creatorName; //7
	uint32 rewardAmount; //8
	//9:
		float targetX;
		float targetY;
		uint32 targetPlanetCrc;
		String targetName;
	//
	uint32 depictedObjCrc; //10 (0A)
	String descriptionStf; //11 (0B)
	String descriptionStr;
	String titleStf; //12 (0C)
	String titleStr;
	uint32 refreshCount; //13 (0D)
	uint32 typeCrc; //14 (0E)

public:

	MissionObjectImplementation(uint64 oid, Player* owner = NULL);
	~MissionObjectImplementation();

	void init();

	/////
	//Asset Setup
	/////
	void assetSetup();
	void assetPart(bool award);


	/////
	//Network Sends:
	/////
	void sendTo(Player* player, bool doClose = true);
	void sendDeltaTo(Player* player);
	void doLinkToPlayer(Player* player);
	void sendDestroyTo(Player* player);

	/////

	inline void setOwner(Player* player) {
		ownerObject = player;
	}

	Player* getOwner() {
		return ownerObject;
	}

	/////
	//Internal Tracking Methods:
	/////

	inline void setDBKey(const String& tdbk) {
		dbKey = tdbk;
	}

	inline String& getDBKey() {
		return dbKey;
	}

	inline void applyTerminalMask(int tam) {
		terminalMask |= tam;
	}

	inline int getTerminalMask() {
		return terminalMask;
	}

	inline String& getStatusStr() {
		return statusStr;
	}

	//Container: For giving to player to complete a delivery
	void addDeliverItem(TangibleObject* item);
	TangibleObject* getDeliverItem(uint64 oid);
	void removeDeliverItem(SceneObject* item);

	//Container: Items to award player on mission completion
	void addAwardItem(TangibleObject* item);
	TangibleObject* getAwardItem(uint64 oid);
	void removeAwardItem(SceneObject* item);

	/////
	//Objectives
	/////

	inline void setObjectiveDefaults(const String& od) {
		objectiveDefaults = od;
	}

	inline String& getObjectiveDefaults() {
		return objectiveDefaults;
	}

	inline bool isInstantComplete() {
		return instantComplete;
	}

	inline void setInstantComplete(bool temp) {
		instantComplete = temp;
	}

	inline bool isComplete() {
		return completed;
	}

	inline bool isFailure() {
		return failed;
	}

	void addObjective(MissionObjective* mo, bool doLock = true);
	void spawnObjectives(const String& objectives, bool doLock = true);
	void serializeObjectives(String& ret, bool doLock = true);
	int updateStatus(int type, uint32 objCrc, const String& str, String& updateStr, int increment, bool doLock = true);
	void checkComplete(bool doLock = false);



	/////
	//Generic Mission Information Variables:
	//All are used in the MissionObject3 packet
	/////

	inline void setTypeStr(const String& tstr) {
		typeStr = tstr;
	}

	inline String& getTypeStr() {
		return typeStr;
	}

	inline void setDescKey(int tdk) {
		descKey = tdk;
	}

	inline uint32 getDescKey() {
		return descKey;
	}

	inline void setTitleKey(int ttk) {
		titleKey = ttk;
	}

	inline uint32 getTitleKey() {
		return titleKey;
	}

	inline void setDifficultyLevel(uint32 tdlv) {
		difficultyLevel = tdlv;
	}

	inline uint32 getDifficultyLevel() {
		return difficultyLevel;
	}

	inline void setDestX(float tdx) {
		destX = tdx;
	}

	inline float getDestX() {
		return destX;
	}

	inline void setDestY(float tdy) {
		destY = tdy;
	}

	inline float getDestY() {
		return destY;
	}

	inline void setDestPlanetCrc(uint32 tpc) {
		destPlanetCrc = tpc;
	}

	inline uint32 getDestPlanetCrc() {
		return destPlanetCrc;
	}

	inline void setCreatorName(const UnicodeString& tcn) {
		creatorName = tcn;
	}

	inline UnicodeString& getCreatorName() {
		return creatorName;
	}

	inline void setReward(uint32 tr) {
		rewardAmount = tr;
	}

	inline uint32 getReward() {
		return rewardAmount;
	}

	inline void setTargetX(float ttx) {
		targetX = ttx;
	}

	inline float getTargetX() {
		return targetX;
	}

	inline void setTargetY(float tty) {
		targetY = tty;
	}

	inline float getTargetY() {
		return targetY;
	}

	inline void setTargetPlanetCrc(uint32 tpc) {
		targetPlanetCrc = tpc;
	}

	inline uint32 getTargetPlanetCrc() {
		return targetPlanetCrc;
	}

	inline void setTargetName(const String& tds) {
		targetName = tds;
	}

	inline String& getTargetName() {
		return targetName;
	}

	inline void setDepictedObjCrc(uint32 tsdc) {
		depictedObjCrc = tsdc;
	}

	inline uint32 getDepictedObjCrc() {
		return depictedObjCrc;
	}

	inline void setDescriptionStf(const String& tds) {
		descriptionStf = tds;
	}

	inline String& getDescriptionStf() {
		return descriptionStf;
	}

	inline void setDescription(const String& tds) {
		descriptionStr = tds;
	}

	inline String& getDescription() {
		return descriptionStr;
	}

	inline void setTitleStf(const String& tts) {
		titleStf = tts;
	}

	inline String& getTitleStf() {
		return titleStf;
	}

	inline void setTitle(const String& tts) {
		titleStr = tts;
	}

	inline String& getTitle() {
		return titleStr;
	}

	inline void setRefreshCount(uint32 trc) {
		refreshCount = trc;
	}

	inline uint32 getRefreshCount() {
		return refreshCount;
	}

	inline void setTypeCrc(uint32 ttc) {
		typeCrc = ttc;
	}

	inline uint32 getTypeCrc() {
		return typeCrc;
	}

	friend class MissionObjectMessage3;
	friend class MissionObjectMessage6;
	friend class MissionObjectDeltaMessage3;

};

#endif /*MISSIONOBJECTIMPLEMENTATION_H_*/
