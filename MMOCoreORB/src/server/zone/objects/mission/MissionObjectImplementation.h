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

class MissionObjectImplementation : public SceneObjectImplementation {
	
	string dbKey;
	
	int terminalMask;
	
	//MISO3:
	string typeStr; //3 BASELINE ONLY
	uint32 descKey; //4 - connected to 0B
	uint32 titleKey; //4 - connected to 0C
	uint32 difficultyLevel; //5
	//6:
		float destX;
		float destY;
		uint32 destPlanetCrc;
	//
	unicode creatorName; //7
	uint32 rewardAmount; //8
	//9:
		float targetX;
		float targetY;
		uint32 targetPlanetCrc;
	//
	uint32 depictedObjCrc; //10 (0A)
	string descriptionStf; //11 (0B)
	string titleStf; //12 (0C)
	uint32 refreshCount; //13 (0D)
	uint32 typeCrc; //14 (0E)

public:
	
	MissionObjectImplementation(uint64 oid);
	
	~MissionObjectImplementation();
	
	void init();
	void sendTo(Player* player, bool doClose = true);
	void sendDeltaTo(Player* player);
	void doLinkToPlayer(Player* player);
	void sendDestroyTo(Player* player);
	
	inline void setDBKey(string& tdbk) {
		dbKey = tdbk;
	}
	
	inline string& getDBKey() {
		return dbKey;
	}
	
	inline void applyTerminalMask(int tam) {
		terminalMask |= tam;
	}
	
	inline int getTerminalMask() {
		return terminalMask;
	}
	
	inline void setTypeStr(const string& tstr) {
		typeStr = tstr;
	}
	
	inline string& getTypeStr() {
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
	
	inline void setCreatorName(const unicode& tcn) {
		creatorName = tcn;
	}
	
	inline unicode& getCreatorName() {
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
	
	inline void setDepictedObjCrc(uint32 tsdc) {
		depictedObjCrc = tsdc;
	}
	
	inline uint32 getDepictedObjCrc() {
		return depictedObjCrc;
	}
	
	inline void setDescriptionStf(const string& tds) {
		descriptionStf = tds;
	}
	
	inline string& getDescriptionStf() {
		return descriptionStf;
	}
	
	inline void setTitleStf(const string& tts) {
		titleStf = tts;
	}
	
	inline string& getTitleStf() {
		return titleStf;
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
