local ObjectManager = require("managers.object.object_manager")

local QuestManager = {}

local QUEST_ACTIVE = 1
local QUEST_COMPLETED = 1

-- Activate the quest for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param quest the index number for the quest to activate.
function QuestManager.activateQuest(pCreatureObject, quest)
	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:setActiveQuestsBit(quest, QUEST_ACTIVE)
	end)
end

-- Checks if the player has a quest active.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param quest the index number for the quest to check if it is active.
function QuestManager.hasActiveQuest(pCreatureObject, quest)
	return ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:hasActiveQuestBitSet(quest)
	end) == true
end

-- Complete the quest for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param quest the index number for the quest to complete.
function QuestManager.completeQuest(pCreatureObject, quest)
	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:clearActiveQuestsBit(quest)
		playerObject:setCompletedQuestsBit(quest, QUEST_ACTIVE)
	end)
end

-- Checks if the player has a quest completed.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param quest the index number for the quest to check if it is completed.
function QuestManager.hasCompletedQuest(pCreatureObject, quest)
	return ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		return playerObject:hasCompletedQuestsBitSet(quest)
	end) == true
end

-- Reset the quest for the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param quest the index number for the quest to reset.
function QuestManager.resetQuest(pCreatureObject, quest)
	ObjectManager.withCreaturePlayerObject(pCreatureObject, function(playerObject)
		playerObject:clearActiveQuestsBit(quest)
		playerObject:clearCompletedQuestsBit(quest)
	end)
end

QuestManager.quests = {}

QuestManager.quests.TEST_SIMPLE 					= 0
QuestManager.quests.TEST_GOTO_01 					= 1
QuestManager.quests.TEST_GOTO_02 					= 2
QuestManager.quests.TEST_GOTO_03 					= 3
QuestManager.quests.TEST_FIND_01 					= 4
QuestManager.quests.TEST_ENCOUNTER_01 				= 5
QuestManager.quests.TEST_DESTROY_01 				= 6
QuestManager.quests.TEST_ESCORT_01 					= 7
QuestManager.quests.TEST_ESCORT_LOCATION 			= 8
QuestManager.quests.TEST_RANDOM 					= 9
QuestManager.quests.TEST_GIVE 						= 10
QuestManager.quests.SCT1 							= 11
QuestManager.quests.SCT2 							= 12
QuestManager.quests.SCT3 							= 13
QuestManager.quests.SCT4 							= 14
QuestManager.quests.FS_QUESTS_SAD_TASKS 			= 15
QuestManager.quests.FS_QUESTS_SAD_TASK1 			= 16
QuestManager.quests.FS_QUESTS_SAD_RETURN1 			= 17
QuestManager.quests.FS_QUESTS_SAD_TASK2 			= 18
QuestManager.quests.FS_QUESTS_SAD_RETURN2 			= 19
QuestManager.quests.FS_QUESTS_SAD_TASK3 			= 20
QuestManager.quests.FS_QUESTS_SAD_RETURN3 			= 21
QuestManager.quests.FS_QUESTS_SAD_TASK4 			= 22
QuestManager.quests.FS_QUESTS_SAD_RETURN4 			= 23
QuestManager.quests.FS_QUESTS_SAD_TASK5 			= 24
QuestManager.quests.FS_QUESTS_SAD_RETURN5 			= 25
QuestManager.quests.FS_QUESTS_SAD_TASK6 			= 26
QuestManager.quests.FS_QUESTS_SAD_RETURN6 			= 27
QuestManager.quests.FS_QUESTS_SAD_TASK7 			= 28
QuestManager.quests.FS_QUESTS_SAD_RETURN7 			= 29
QuestManager.quests.FS_QUESTS_SAD_TASK8 			= 30
QuestManager.quests.FS_QUESTS_SAD_RETURN8 			= 31
QuestManager.quests.FS_QUESTS_SAD_FINISH 			= 32
QuestManager.quests.FS_QUESTS_SAD2_TASKS 			= 33
QuestManager.quests.FS_QUESTS_SAD2_TASK1			= 34
QuestManager.quests.FS_QUESTS_SAD2_RETURN1 			= 35
QuestManager.quests.FS_QUESTS_SAD2_TASK2 			= 36
QuestManager.quests.FS_QUESTS_SAD2_RETURN2 			= 37
QuestManager.quests.FS_QUESTS_SAD2_TASK3 			= 38
QuestManager.quests.FS_QUESTS_SAD2_RETURN3 			= 39
QuestManager.quests.FS_QUESTS_SAD2_TASK4 			= 40
QuestManager.quests.FS_QUESTS_SAD2_RETURN4 			= 41
QuestManager.quests.FS_QUESTS_SAD2_TASK5 			= 42
QuestManager.quests.FS_QUESTS_SAD2_RETURN5 			= 43
QuestManager.quests.FS_QUESTS_SAD2_TASK6 			= 44
QuestManager.quests.FS_QUESTS_SAD2_RETURN6 			= 45
QuestManager.quests.FS_QUESTS_SAD2_TASK7 			= 46
QuestManager.quests.FS_QUESTS_SAD2_RETURN7 			= 47
QuestManager.quests.FS_QUESTS_SAD2_TASK8 			= 48
QuestManager.quests.FS_QUESTS_SAD2_RETURN8 			= 49
QuestManager.quests.FS_QUESTS_SAD2_FINISH 			= 50
QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_01 		= 51
QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_02 		= 52
QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_03 		= 53
QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_02 	= 54
QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_02 	= 55
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_00 		= 56
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_01 		= 57
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02 		= 58
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03 		= 59
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04 		= 60
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_05 		= 61
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_06 		= 62
QuestManager.quests.FS_REFLEX_FETCH_QUEST_00 		= 63
QuestManager.quests.FS_REFLEX_FETCH_QUEST_01 		= 64
QuestManager.quests.FS_REFLEX_FETCH_QUEST_02 		= 65
QuestManager.quests.FS_REFLEX_FETCH_QUEST_03 		= 66
QuestManager.quests.FS_REFLEX_FETCH_QUEST_04 		= 67
QuestManager.quests.FS_REFLEX_FETCH_QUEST_05 		= 68
QuestManager.quests.FS_REFLEX_FETCH_QUEST_06 		= 69
QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_00 		= 70
QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_01 		= 71
QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_02 		= 72
QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_03 		= 73
QuestManager.quests.OLD_MAN_INITIAL 				= 74
QuestManager.quests.FS_THEATER_CAMP 				= 75
QuestManager.quests.DO_NOT_USE_BAD_SLOT 			= 76
QuestManager.quests.FS_GOTO_DATH 					= 77
QuestManager.quests.FS_VILLAGE_ELDER 				= 78
QuestManager.quests.OLD_MAN_FORCE_CRYSTAL 			= 79
QuestManager.quests.FS_DATH_wOMAN 					= 80
QuestManager.quests.FS_PATROL_QUEST_1 				= 81
QuestManager.quests.FS_PATROL_QUEST_2 				= 82
QuestManager.quests.FS_PATROL_QUEST_3 				= 83
QuestManager.quests.FS_PATROL_QUEST_4 				= 84
QuestManager.quests.FS_PATROL_QUEST_5 				= 85
QuestManager.quests.FS_PATROL_QUEST_6 				= 86
QuestManager.quests.FS_PATROL_QUEST_7 				= 87
QuestManager.quests.FS_PATROL_QUEST_8 				= 88
QuestManager.quests.FS_PATROL_QUEST_9 				= 89
QuestManager.quests.FS_PATROL_QUEST_10 				= 90
QuestManager.quests.FS_PATROL_QUEST_11 				= 91
QuestManager.quests.FS_PATROL_QUEST_12 				= 92
QuestManager.quests.FS_PATROL_QUEST_13 				= 93
QuestManager.quests.FS_PATROL_QUEST_14 				= 94
QuestManager.quests.FS_PATROL_QUEST_15 				= 95
QuestManager.quests.FS_PATROL_QUEST_16 				= 96
QuestManager.quests.FS_PATROL_QUEST_17 				= 97
QuestManager.quests.FS_PATROL_QUEST_18 				= 98
QuestManager.quests.FS_PATROL_QUEST_19 				= 99
QuestManager.quests.FS_PATROL_QUEST_20 				= 100
QuestManager.quests.FS_COMBAT_HEALING_1 			= 101
QuestManager.quests.FS_COMBAT_HEALING_2 			= 102
QuestManager.quests.FS_DEFEND_SET_FACTION 			= 103
QuestManager.quests.FS_DEFEND_01 					= 104
QuestManager.quests.FS_DEFEND_02 					= 105
QuestManager.quests.FS_DEFEND_REwARD_01 			= 106
QuestManager.quests.FS_DEFEND_03 					= 107
QuestManager.quests.FS_DEFEND_04 					= 108
QuestManager.quests.FS_CS_INTRO 					= 109
QuestManager.quests.FS_CS_KILL5_GUARDS 				= 110
QuestManager.quests.FS_CS_ENSURE_CAPTURE 			= 111
QuestManager.quests.FS_CS_LAST_CHANCE 				= 112
QuestManager.quests.FS_CS_ESCORT_COMMANDER_PRI 		= 113
QuestManager.quests.FS_CS_ESCORT_COMMANDER_SEC 		= 114
QuestManager.quests.FS_CS_QUEST_DONE 				= 115
QuestManager.quests.FS_THEATER_FINAL 				= 116
QuestManager.quests.OLD_MAN_FINAL 					= 117
QuestManager.quests.FS_CRAFTING4_QUEST_00 			= 118
QuestManager.quests.FS_CRAFTING4_QUEST_01 			= 119
QuestManager.quests.FS_CRAFTING4_QUEST_02 			= 120
QuestManager.quests.FS_CRAFTING4_QUEST_03 			= 121
QuestManager.quests.FS_CRAFTING4_QUEST_04 			= 122
QuestManager.quests.FS_CRAFTING4_QUEST_05 			= 123
QuestManager.quests.FS_CRAFTING4_QUEST_06 			= 124
QuestManager.quests.FS_CRAFTING4_QUEST_07 			= 125
QuestManager.quests.TwO_MILITARY 					= 126
QuestManager.quests.FS_DEFEND_REwARD_02 			= 127
QuestManager.quests.FS_DEFEND_REwARD_03 			= 128
QuestManager.quests.SURVEY_PHASE2_MAIN 				= 129
QuestManager.quests.SURVEY_PHASE2_01 				= 130
QuestManager.quests.SURVEY_PHASE2_02 				= 131
QuestManager.quests.SURVEY_PHASE2_03 				= 132
QuestManager.quests.SURVEY_PHASE2_04 				= 133
QuestManager.quests.SURVEY_PHASE2_05 				= 134
QuestManager.quests.SURVEY_PHASE2_06 				= 135
QuestManager.quests.SURVEY_PHASE2_07 				= 136
QuestManager.quests.SURVEY_PHASE2_08 				= 137
QuestManager.quests.SURVEY_PHASE3_MAIN 				= 138
QuestManager.quests.SURVEY_PHASE3_01 				= 139
QuestManager.quests.SURVEY_PHASE3_02 				= 140
QuestManager.quests.SURVEY_PHASE3_03 				= 141
QuestManager.quests.SURVEY_PHASE3_04 				= 142
QuestManager.quests.SURVEY_PHASE3_05 				= 143
QuestManager.quests.SURVEY_PHASE3_06 				= 144
QuestManager.quests.SURVEY_PHASE3_07 				= 145
QuestManager.quests.SURVEY_PHASE3_08 				= 146
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_01 	= 147
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_02 	= 148
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_03 	= 149
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_04 	= 150
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_05 	= 151
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_06 	= 152
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_07 	= 153
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_08 	= 154
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_09 	= 155
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_10 	= 156
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_11 	= 157
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_12 	= 158
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_13 	= 159
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_14 	= 160
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_15 	= 161
QuestManager.quests.FS_SURVEY_SPECIAL_RESOURCE_16 	= 162
QuestManager.quests.FS_DATH_wOMAN_TALK 				= 163
QuestManager.quests.FS_PATROL_QUEST_START 			= 164
QuestManager.quests.FS_REFLEX_RESCUE_QUEST_07 		= 165
QuestManager.quests.FS_SURVEY_PHASE2_REwARD 		= 166
QuestManager.quests.FS_SURVEY_PHASE3_REwARD 		= 167
QuestManager.quests.FS_DEFEND_SET_FACTION_02 		= 168
QuestManager.quests.LOOT_DATAPAD_1 					= 169
QuestManager.quests.GOT_DATAPAD 					= 170
QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_01 	= 171
QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_01 	= 172
QuestManager.quests.FS_PHASE_2_CRAFT_DEFENSES_MAIN 	= 173
QuestManager.quests.FS_PHASE_3_CRAFT_SHIELDS_MAIN 	= 174
QuestManager.quests.LOOT_DATAPAD_2 					= 175
QuestManager.quests.GOT_DATAPAD_2 					= 176
QuestManager.quests.FS_CS_QUEST_FAILED_ESCORT 		= 177
QuestManager.quests.FS_PATROL_QUEST_FINISH 			= 178
QuestManager.quests.FS_MEDIC_PUZZLE_QUEST_FINISH 	= 179
QuestManager.quests.FS_COMBAT_HEALING_FINISH 		= 180
QuestManager.quests.FS_COMBAT_REwARD_PHASE2 		= 181
QuestManager.quests.FS_REFLEX_REwARD_PHASE3 		= 182
QuestManager.quests.FS_DEFEND_wAIT_01 				= 183
QuestManager.quests.FS_DEFEND_wAIT_02 				= 184
QuestManager.quests.FS_CRAFTING4_QUEST_FINISH 		= 185
QuestManager.quests.FS_CRAFT_PUZZLE_QUEST_04 		= 186
QuestManager.quests.FS_CS_QUEST_DONE_NOTIFYONLY 	= 187

return QuestManager
