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
	enum {
		TEST_SIMPLE                       = 0,
		TEST_GOTO_01                      = 1,
		TEST_GOTO_02                      = 2,
		TEST_GOTO_03                      = 3,
		TEST_FIND_01                      = 4,
		TEST_ENCOUNTER_01                 = 5,
		TEST_DESTROY_01                   = 6,
		TEST_ESCORT_01                    = 7,
		TEST_ESCORT_LOCATION              = 8,
		TEST_RANDOM                       = 9,
		TEST_GIVE                         = 10,
		SCT1                              = 11,
		SCT2                              = 12,
		SCT3                              = 13,
		SCT4                              = 14,
		FS_QUESTS_SAD_TASKS               = 15,
		FS_QUESTS_SAD_TASK1               = 16,
		FS_QUESTS_SAD_RETURN1             = 17,
		FS_QUESTS_SAD_TASK2               = 18,
		FS_QUESTS_SAD_RETURN2             = 19,
		FS_QUESTS_SAD_TASK3               = 20,
		FS_QUESTS_SAD_RETURN3             = 21,
		FS_QUESTS_SAD_TASK4               = 22,
		FS_QUESTS_SAD_RETURN4             = 23,
		FS_QUESTS_SAD_TASK5               = 24,
		FS_QUESTS_SAD_RETURN5             = 25,
		FS_QUESTS_SAD_TASK6               = 26,
		FS_QUESTS_SAD_RETURN6             = 27,
		FS_QUESTS_SAD_TASK7               = 28,
		FS_QUESTS_SAD_RETURN7             = 29,
		FS_QUESTS_SAD_TASK8               = 30,
		FS_QUESTS_SAD_RETURN8             = 31,
		FS_QUESTS_SAD_FINISH              = 32,
		FS_QUESTS_SAD2_TASKS              = 33,
		FS_QUESTS_SAD2_TASK1              = 34,
		FS_QUESTS_SAD2_RETURN1            = 35,
		FS_QUESTS_SAD2_TASK2              = 36,
		FS_QUESTS_SAD2_RETURN2            = 37,
		FS_QUESTS_SAD2_TASK3              = 38,
		FS_QUESTS_SAD2_RETURN3            = 39,
		FS_QUESTS_SAD2_TASK4              = 40,
		FS_QUESTS_SAD2_RETURN4            = 41,
		FS_QUESTS_SAD2_TASK5              = 42,
		FS_QUESTS_SAD2_RETURN5            = 43,
		FS_QUESTS_SAD2_TASK6              = 44,
		FS_QUESTS_SAD2_RETURN6            = 45,
		FS_QUESTS_SAD2_TASK7              = 46,
		FS_QUESTS_SAD2_RETURN7            = 47,
		FS_QUESTS_SAD2_TASK8              = 48,
		FS_QUESTS_SAD2_RETURN8            = 49,
		FS_QUESTS_SAD2_FINISH             = 50,
		FS_MEDIC_PUZZLE_QUEST_01          = 51,
		FS_MEDIC_PUZZLE_QUEST_02          = 52,
		FS_MEDIC_PUZZLE_QUEST_03          = 53,
		FS_PHASE_2_CRAFT_DEFENSES_02      = 54,
		FS_PHASE_3_CRAFT_SHIELDS_02       = 55,
		FS_REFLEX_RESCUE_QUEST_00         = 56,
		FS_REFLEX_RESCUE_QUEST_01         = 57,
		FS_REFLEX_RESCUE_QUEST_02         = 58,
		FS_REFLEX_RESCUE_QUEST_03         = 59,
		FS_REFLEX_RESCUE_QUEST_04         = 60,
		FS_REFLEX_RESCUE_QUEST_05         = 61,
		FS_REFLEX_RESCUE_QUEST_06         = 62,
		FS_REFLEX_FETCH_QUEST_00          = 63,
		FS_REFLEX_FETCH_QUEST_01          = 64,
		FS_REFLEX_FETCH_QUEST_02          = 65,
		FS_REFLEX_FETCH_QUEST_03          = 66,
		FS_REFLEX_FETCH_QUEST_04          = 67,
		FS_REFLEX_FETCH_QUEST_05          = 68,
		FS_REFLEX_FETCH_QUEST_06          = 69,
		FS_CRAFT_PUZZLE_QUEST_00          = 70,
		FS_CRAFT_PUZZLE_QUEST_01          = 71,
		FS_CRAFT_PUZZLE_QUEST_02          = 72,
		FS_CRAFT_PUZZLE_QUEST_03          = 73,
		OLD_MAN_INITIAL                   = 74,
		FS_THEATER_CAMP                   = 75,
		DO_NOT_USE_BAD_SLOT               = 76,
		FS_GOTO_DATH                      = 77,
		FS_VILLAGE_ELDER                  = 78,
		OLD_MAN_FORCE_CRYSTAL             = 79,
		FS_DATH_wOMAN                     = 80,
		FS_PATROL_QUEST_1                 = 81,
		FS_PATROL_QUEST_2                 = 82,
		FS_PATROL_QUEST_3                 = 83,
		FS_PATROL_QUEST_4                 = 84,
		FS_PATROL_QUEST_5                 = 85,
		FS_PATROL_QUEST_6                 = 86,
		FS_PATROL_QUEST_7                 = 87,
		FS_PATROL_QUEST_8                 = 88,
		FS_PATROL_QUEST_9                 = 89,
		FS_PATROL_QUEST_10                = 90,
		FS_PATROL_QUEST_11                = 91,
		FS_PATROL_QUEST_12                = 92,
		FS_PATROL_QUEST_13                = 93,
		FS_PATROL_QUEST_14                = 94,
		FS_PATROL_QUEST_15                = 95,
		FS_PATROL_QUEST_16                = 96,
		FS_PATROL_QUEST_17                = 97,
		FS_PATROL_QUEST_18                = 98,
		FS_PATROL_QUEST_19                = 99,
		FS_PATROL_QUEST_20                = 100,
		FS_COMBAT_HEALING_1               = 101,
		FS_COMBAT_HEALING_2               = 102,
		FS_DEFEND_SET_FACTION             = 103,
		FS_DEFEND_01                      = 104,
		FS_DEFEND_02                      = 105,
		FS_DEFEND_REwARD_01               = 106,
		FS_DEFEND_03                      = 107,
		FS_DEFEND_04                      = 108,
		FS_CS_INTRO                       = 109,
		FS_CS_KILL5_GUARDS                = 110,
		FS_CS_ENSURE_CAPTURE              = 111,
		FS_CS_LAST_CHANCE                 = 112,
		FS_CS_ESCORT_COMMANDER_PRI        = 113,
		FS_CS_ESCORT_COMMANDER_SEC        = 114,
		FS_CS_QUEST_DONE                  = 115,
		FS_THEATER_FINAL                  = 116,
		OLD_MAN_FINAL                     = 117,
		FS_CRAFTING4_QUEST_00             = 118,
		FS_CRAFTING4_QUEST_01             = 119,
		FS_CRAFTING4_QUEST_02             = 120,
		FS_CRAFTING4_QUEST_03             = 121,
		FS_CRAFTING4_QUEST_04             = 122,
		FS_CRAFTING4_QUEST_05             = 123,
		FS_CRAFTING4_QUEST_06             = 124,
		FS_CRAFTING4_QUEST_07             = 125,
		TwO_MILITARY                      = 126,
		FS_DEFEND_REwARD_02               = 127,
		FS_DEFEND_REwARD_03               = 128,
		SURVEY_PHASE2_MAIN                = 129,
		SURVEY_PHASE2_01                  = 130,
		SURVEY_PHASE2_02                  = 131,
		SURVEY_PHASE2_03                  = 132,
		SURVEY_PHASE2_04                  = 133,
		SURVEY_PHASE2_05                  = 134,
		SURVEY_PHASE2_06                  = 135,
		SURVEY_PHASE2_07                  = 136,
		SURVEY_PHASE2_08                  = 137,
		SURVEY_PHASE3_MAIN                = 138,
		SURVEY_PHASE3_01                  = 139,
		SURVEY_PHASE3_02                  = 140,
		SURVEY_PHASE3_03                  = 141,
		SURVEY_PHASE3_04                  = 142,
		SURVEY_PHASE3_05                  = 143,
		SURVEY_PHASE3_06                  = 144,
		SURVEY_PHASE3_07                  = 145,
		SURVEY_PHASE3_08                  = 146,
		FS_SURVEY_SPECIAL_RESOURCE_01     = 147,
		FS_SURVEY_SPECIAL_RESOURCE_02     = 148,
		FS_SURVEY_SPECIAL_RESOURCE_03     = 159,
		FS_SURVEY_SPECIAL_RESOURCE_04     = 160,
		FS_SURVEY_SPECIAL_RESOURCE_05     = 161,
		FS_SURVEY_SPECIAL_RESOURCE_06     = 162,
		FS_SURVEY_SPECIAL_RESOURCE_07     = 163,
		FS_SURVEY_SPECIAL_RESOURCE_08     = 164,
		FS_SURVEY_SPECIAL_RESOURCE_09     = 165,
		FS_SURVEY_SPECIAL_RESOURCE_10     = 166,
		FS_SURVEY_SPECIAL_RESOURCE_11     = 167,
		FS_SURVEY_SPECIAL_RESOURCE_12     = 168,
		FS_SURVEY_SPECIAL_RESOURCE_13     = 169,
		FS_SURVEY_SPECIAL_RESOURCE_14     = 170,
		FS_SURVEY_SPECIAL_RESOURCE_15     = 171,
		FS_SURVEY_SPECIAL_RESOURCE_16     = 172,
		FS_DATH_wOMAN_TALK                = 173,
		FS_PATROL_QUEST_START             = 174,
		FS_REFLEX_RESCUE_QUEST_07         = 175,
		FS_SURVEY_PHASE2_REwARD           = 176,
		FS_SURVEY_PHASE3_REwARD           = 177,
		FS_DEFEND_SET_FACTION_02          = 178,
		LOOT_DATAPAD_1                    = 179,
		GOT_DATAPAD                       = 180,
		FS_PHASE_2_CRAFT_DEFENSES_01      = 181,
		FS_PHASE_3_CRAFT_SHIELDS_01       = 182,
		FS_PHASE_2_CRAFT_DEFENSES_MAIN    = 183,
		FS_PHASE_3_CRAFT_SHIELDS_MAIN     = 184,
		LOOT_DATAPAD_2                    = 185,
		GOT_DATAPAD_2                     = 186,
		FS_CS_QUEST_FAILED_ESCORT         = 187,
		FS_PATROL_QUEST_FINISH            = 188,
		FS_MEDIC_PUZZLE_QUEST_FINISH      = 189,
		FS_COMBAT_HEALING_FINISH          = 190,
		FS_COMBAT_REwARD_PHASE2           = 191,
		FS_REFLEX_REwARD_PHASE3           = 192,
		FS_DEFEND_wAIT_01                 = 193,
		FS_DEFEND_wAIT_02                 = 194,
		FS_CRAFTING4_QUEST_FINISH         = 195,
		FS_CRAFT_PUZZLE_QUEST_04          = 196	
	};

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
