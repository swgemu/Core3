/*
 * PlayerQuestData.h
 *
 *  Created on: 15/11/2013
 *      Author: victor
 */

#ifndef PLAYERQUESTDATA_H_
#define PLAYERQUESTDATA_H_

#include "engine/engine.h"

class PlayerQuestData : public Object {
	uint64 ownerId;
	uint16 activeStepBitmask;
	uint16 completedStepBitmask;
	byte completedFlag;
	int questCounter;

public:
	static const int TEST_SIMPLE 					= 0;
	static const int TEST_GOTO_01 					= 1;
	static const int TEST_GOTO_02 					= 2;
	static const int TEST_GOTO_03 					= 3;
	static const int TEST_FIND_01					= 4;
	static const int TEST_ENCOUNTER_01 				= 5;
	static const int TEST_DESTROY_01 				= 6;
	static const int TEST_ESCORT_01 				= 7;
	static const int TEST_ESCORT_LOCATION 			= 8;
	static const int TEST_RANDOM 					= 9;
	static const int TEST_GIVE  					= 10;
	static const int SCT1  							= 11;
	static const int SCT2  							= 12;
	static const int SCT3  							= 13;
	static const int SCT4  							= 14;
	static const int FS_QUESTS_SAD_TASKS 			= 15;
	static const int FS_QUESTS_SAD_TASK1 			= 16;
	static const int FS_QUESTS_SAD_RETURN1 			= 17;
	static const int FS_QUESTS_SAD_TASK2 			= 18;
	static const int FS_QUESTS_SAD_RETURN2 			= 19;
	static const int FS_QUESTS_SAD_TASK3 			= 20;
	static const int FS_QUESTS_SAD_RETURN3 			= 21;
	static const int FS_QUESTS_SAD_TASK4 			= 22;
	static const int FS_QUESTS_SAD_RETURN4 			= 23;
	static const int FS_QUESTS_SAD_TASK5 			= 24;
	static const int FS_QUESTS_SAD_RETURN5 			= 25;
	static const int FS_QUESTS_SAD_TASK6 			= 26;
	static const int FS_QUESTS_SAD_RETURN6 			= 27;
	static const int FS_QUESTS_SAD_TASK7 			= 28;
	static const int FS_QUESTS_SAD_RETURN7 			= 29;
	static const int FS_QUESTS_SAD_TASK8 			= 30;
	static const int FS_QUESTS_SAD_RETURN8 			= 31;
	static const int FS_QUESTS_SAD_FINISH 			= 32;
	static const int FS_QUESTS_SAD2_TASKS 			= 33;
	static const int FS_QUESTS_SAD2_TASK1			= 34;
	static const int FS_QUESTS_SAD2_RETURN1 		= 35;
	static const int FS_QUESTS_SAD2_TASK2 			= 36;
	static const int FS_QUESTS_SAD2_RETURN2 		= 37;
	static const int FS_QUESTS_SAD2_TASK3 			= 38;
	static const int FS_QUESTS_SAD2_RETURN3 		= 39;
	static const int FS_QUESTS_SAD2_TASK4 			= 40;
	static const int FS_QUESTS_SAD2_RETURN4 		= 41;
	static const int FS_QUESTS_SAD2_TASK5 			= 42;
	static const int FS_QUESTS_SAD2_RETURN5 		= 43;
	static const int FS_QUESTS_SAD2_TASK6 			= 44;
	static const int FS_QUESTS_SAD2_RETURN6 		= 45;
	static const int FS_QUESTS_SAD2_TASK7 			= 46;
	static const int FS_QUESTS_SAD2_RETURN7 		= 47;
	static const int FS_QUESTS_SAD2_TASK8 			= 48;
	static const int FS_QUESTS_SAD2_RETURN8 		= 49;
	static const int FS_QUESTS_SAD2_FINISH 			= 50;
	static const int FS_MEDIC_PUZZLE_QUEST_01 		= 51;
	static const int FS_MEDIC_PUZZLE_QUEST_02 		= 52;
	static const int FS_MEDIC_PUZZLE_QUEST_03 		= 53;
	static const int FS_PHASE_2_CRAFT_DEFENSES_02 	= 54;
	static const int FS_PHASE_3_CRAFT_SHIELDS_02 	= 55;
	static const int FS_REFLEX_RESCUE_QUEST_00 		= 56;
	static const int FS_REFLEX_RESCUE_QUEST_01 		= 57;
	static const int FS_REFLEX_RESCUE_QUEST_02 		= 58;
	static const int FS_REFLEX_RESCUE_QUEST_03 		= 59;
	static const int FS_REFLEX_RESCUE_QUEST_04 		= 60;
	static const int FS_REFLEX_RESCUE_QUEST_05 		= 61;
	static const int FS_REFLEX_RESCUE_QUEST_06 		= 62;
	static const int FS_REFLEX_FETCH_QUEST_00 		= 63;
	static const int FS_REFLEX_FETCH_QUEST_01 		= 64;
	static const int FS_REFLEX_FETCH_QUEST_02 		= 65;
	static const int FS_REFLEX_FETCH_QUEST_03 		= 66;
	static const int FS_REFLEX_FETCH_QUEST_04 		= 67;
	static const int FS_REFLEX_FETCH_QUEST_05 		= 68;
	static const int FS_REFLEX_FETCH_QUEST_06 		= 69;
	static const int FS_CRAFT_PUZZLE_QUEST_00 		= 70;
	static const int FS_CRAFT_PUZZLE_QUEST_01 		= 71;
	static const int FS_CRAFT_PUZZLE_QUEST_02 		= 72;
	static const int FS_CRAFT_PUZZLE_QUEST_03 		= 73;
	static const int OLD_MAN_INITIAL 				= 74;
	static const int FS_THEATER_CAMP 				= 75;
	static const int DO_NOT_USE_BAD_SLOT 			= 76;
	static const int FS_GOTO_DATH 					= 77;
	static const int FS_VILLAGE_ELDER 				= 78;
	static const int OLD_MAN_FORCE_CRYSTAL 			= 79;
	static const int FS_DATH_wOMAN 					= 80;
	static const int FS_PATROL_QUEST_1 				= 81;
	static const int FS_PATROL_QUEST_2 				= 82;
	static const int FS_PATROL_QUEST_3 				= 83;
	static const int FS_PATROL_QUEST_4 				= 84;
	static const int FS_PATROL_QUEST_5 				= 85;
	static const int FS_PATROL_QUEST_6 				= 86;
	static const int FS_PATROL_QUEST_7 				= 87;
	static const int FS_PATROL_QUEST_8 				= 88;
	static const int FS_PATROL_QUEST_9 				= 89;
	static const int FS_PATROL_QUEST_10 			= 90;
	static const int FS_PATROL_QUEST_11 			= 91;
	static const int FS_PATROL_QUEST_12 			= 92;
	static const int FS_PATROL_QUEST_13 			= 93;
	static const int FS_PATROL_QUEST_14 			= 94;
	static const int FS_PATROL_QUEST_15 			= 95;
	static const int FS_PATROL_QUEST_16 			= 96;
	static const int FS_PATROL_QUEST_17 			= 97;
	static const int FS_PATROL_QUEST_18 			= 98;
	static const int FS_PATROL_QUEST_19 			= 99;
	static const int FS_PATROL_QUEST_20 			= 100;
	static const int FS_COMBAT_HEALING_1 			= 101;
	static const int FS_COMBAT_HEALING_2 			= 102;
	static const int FS_DEFEND_SET_FACTION 			= 103;
	static const int FS_DEFEND_01  					= 104;
	static const int FS_DEFEND_02 					= 105;
	static const int FS_DEFEND_REwARD_01 			= 106;
	static const int FS_DEFEND_03  					= 107;
	static const int FS_DEFEND_04  					= 108;
	static const int FS_CS_INTRO 					= 109;
	static const int FS_CS_KILL5_GUARDS 			= 110;
	static const int FS_CS_ENSURE_CAPTURE 			= 111;
	static const int FS_CS_LAST_CHANCE 				= 112;
	static const int FS_CS_ESCORT_COMMANDER_PRI 	= 113;
	static const int FS_CS_ESCORT_COMMANDER_SEC 	= 114;
	static const int FS_CS_QUEST_DONE 				= 115;
	static const int FS_THEATER_FINAL 				= 116;
	static const int OLD_MAN_FINAL  				= 117;
	static const int FS_CRAFTING4_QUEST_00 			= 118;
	static const int FS_CRAFTING4_QUEST_01 			= 119;
	static const int FS_CRAFTING4_QUEST_02 			= 120;
	static const int FS_CRAFTING4_QUEST_03 			= 121;
	static const int FS_CRAFTING4_QUEST_04 			= 122;
	static const int FS_CRAFTING4_QUEST_05 			= 123;
	static const int FS_CRAFTING4_QUEST_06 			= 124;
	static const int FS_CRAFTING4_QUEST_07 			= 125;
	static const int TwO_MILITARY  					= 126;
	static const int FS_DEFEND_REwARD_02 			= 127;
	static const int FS_DEFEND_REwARD_03 			= 128;
	static const int SURVEY_PHASE2_MAIN 			= 129;
	static const int SURVEY_PHASE2_01 				= 130;
	static const int SURVEY_PHASE2_02 				= 131;
	static const int SURVEY_PHASE2_03 				= 132;
	static const int SURVEY_PHASE2_04 				= 133;
	static const int SURVEY_PHASE2_05 				= 134;
	static const int SURVEY_PHASE2_06 				= 135;
	static const int SURVEY_PHASE2_07 				= 136;
	static const int SURVEY_PHASE2_08 				= 137;
	static const int SURVEY_PHASE3_MAIN 			= 138;
	static const int SURVEY_PHASE3_01 				= 139;
	static const int SURVEY_PHASE3_02 				= 140;
	static const int SURVEY_PHASE3_03 				= 141;
	static const int SURVEY_PHASE3_04 				= 142;
	static const int SURVEY_PHASE3_05 				= 143;
	static const int SURVEY_PHASE3_06 				= 144;
	static const int SURVEY_PHASE3_07 				= 145;
	static const int SURVEY_PHASE3_08 				= 146;
	static const int FS_SURVEY_SPECIAL_RESOURCE_01 	= 147;
	static const int FS_SURVEY_SPECIAL_RESOURCE_02 	= 148;
	static const int FS_SURVEY_SPECIAL_RESOURCE_03 	= 159;
	static const int FS_SURVEY_SPECIAL_RESOURCE_04 	= 160;
	static const int FS_SURVEY_SPECIAL_RESOURCE_05 	= 161;
	static const int FS_SURVEY_SPECIAL_RESOURCE_06 	= 162;
	static const int FS_SURVEY_SPECIAL_RESOURCE_07 	= 163;
	static const int FS_SURVEY_SPECIAL_RESOURCE_08 	= 164;
	static const int FS_SURVEY_SPECIAL_RESOURCE_09 	= 165;
	static const int FS_SURVEY_SPECIAL_RESOURCE_10 	= 166;
	static const int FS_SURVEY_SPECIAL_RESOURCE_11 	= 167;
	static const int FS_SURVEY_SPECIAL_RESOURCE_12 	= 168;
	static const int FS_SURVEY_SPECIAL_RESOURCE_13 	= 169;
	static const int FS_SURVEY_SPECIAL_RESOURCE_14 	= 170;
	static const int FS_SURVEY_SPECIAL_RESOURCE_15 	= 171;
	static const int FS_SURVEY_SPECIAL_RESOURCE_16 	= 172;
	static const int FS_DATH_wOMAN_TALK 			= 173;
	static const int FS_PATROL_QUEST_START 			= 174;
	static const int FS_REFLEX_RESCUE_QUEST_07 		= 175;
	static const int FS_SURVEY_PHASE2_REwARD 		= 176;
	static const int FS_SURVEY_PHASE3_REwARD 		= 177;
	static const int FS_DEFEND_SET_FACTION_02 		= 178;
	static const int LOOT_DATAPAD_1 				= 179;
	static const int GOT_DATAPAD  					= 180;
	static const int FS_PHASE_2_CRAFT_DEFENSES_01 	= 181;
	static const int FS_PHASE_3_CRAFT_SHIELDS_01 	= 182;
	static const int FS_PHASE_2_CRAFT_DEFENSES_MAIN = 183;
	static const int FS_PHASE_3_CRAFT_SHIELDS_MAIN 	= 184;
	static const int LOOT_DATAPAD_2  				= 185;
	static const int GOT_DATAPAD_2  				= 186;
	static const int FS_CS_QUEST_FAILED_ESCORT 		= 187;
	static const int FS_PATROL_QUEST_FINISH 		= 188;
	static const int FS_MEDIC_PUZZLE_QUEST_FINISH 	= 189;
	static const int FS_COMBAT_HEALING_FINISH 		= 190;
	static const int FS_COMBAT_REwARD_PHASE2 		= 191;
	static const int FS_REFLEX_REwARD_PHASE3 		= 192;
	static const int FS_DEFEND_wAIT_01 				= 193;
	static const int FS_DEFEND_wAIT_02 				= 194;
	static const int FS_CRAFTING4_QUEST_FINISH 		= 195;
	static const int FS_CRAFT_PUZZLE_QUEST_04 		= 196;

public:
	PlayerQuestData() : Object() {
		ownerId = 0;
		activeStepBitmask = 0;
		completedStepBitmask = 0;
		completedFlag = 0;
		questCounter = 0;
	}

	PlayerQuestData(const PlayerQuestData& data) : Object() {
		initialize(data);
	}

	PlayerQuestData& operator=(const PlayerQuestData& data) {
		if (this == &data)
			return *this;

		initialize(data);

		return *this;
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		stream->writeLong(ownerId);
		stream->writeShort(activeStepBitmask);
		stream->writeShort(completedStepBitmask);
		stream->writeByte(completedFlag);
		stream->writeInt(questCounter);

		return true;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		ownerId = stream->readLong();
		activeStepBitmask = stream->readShort();
		completedStepBitmask = stream->readShort();
		completedFlag = stream->readByte();
		questCounter = stream->readInt();

		return true;
	}

	void initialize(const PlayerQuestData& data) {
		ownerId = data.ownerId;
		activeStepBitmask = data.activeStepBitmask;
		completedStepBitmask = data.completedStepBitmask;
		completedFlag = data.completedFlag;
		questCounter = data.questCounter;
	}

	uint16 getActiveStepBitmask() const {
		return activeStepBitmask;
	}

	void setActiveStepBitmask(uint16 activeStepBitmask) {
		this->activeStepBitmask = activeStepBitmask;
	}

	byte getCompletedFlag() const {
		return completedFlag;
	}

	void setCompletedFlag(byte completedFlag) {
		this->completedFlag = completedFlag;
	}

	uint16 getCompletedStepBitmask() const {
		return completedStepBitmask;
	}

	void setCompletedStepBitmask(uint16 completedStepBitmask) {
		this->completedStepBitmask = completedStepBitmask;
	}

	uint64 getOwnerId() const {
		return ownerId;
	}

	void setOwnerId(uint64 ownerId) {
		this->ownerId = ownerId;
	}

	int getQuestCounter() const {
		return questCounter;
	}

	void setQuestCounter(int questCounter) {
		this->questCounter = questCounter;
	}
};


#endif /* PLAYERQUESTDATA_H_ */
