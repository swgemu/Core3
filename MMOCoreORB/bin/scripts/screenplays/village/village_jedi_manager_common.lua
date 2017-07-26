local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

VillageJediManagerCommon = ScreenPlay:new {
	forceSensitiveBranches = {
		"force_sensitive_combat_prowess_ranged_accuracy",
		"force_sensitive_combat_prowess_ranged_speed",
		"force_sensitive_combat_prowess_melee_accuracy",
		"force_sensitive_combat_prowess_melee_speed",
		"force_sensitive_enhanced_reflexes_ranged_defense",
		"force_sensitive_enhanced_reflexes_melee_defense",
		"force_sensitive_enhanced_reflexes_vehicle_control",
		"force_sensitive_enhanced_reflexes_survival",
		"force_sensitive_crafting_mastery_experimentation",
		"force_sensitive_crafting_mastery_assembly",
		"force_sensitive_crafting_mastery_repair",
		"force_sensitive_crafting_mastery_technique",
		"force_sensitive_heightened_senses_healing",
		"force_sensitive_heightened_senses_surveying",
		"force_sensitive_heightened_senses_persuasion",
		"force_sensitive_heightened_senses_luck"
	}
}

VILLAGE_PHASE1_SARGUILLO = 1
VILLAGE_PHASE1_QUHAREK = 2
VILLAGE_PHASE1_SIVARRA = 3
VILLAGE_PHASE1_WHIP = 4
VILLAGE_PHASE2_DAGEERIN = 5
VILLAGE_PHASE2_QUHAREK = 6
VILLAGE_PHASE2_WHIP = 7
VILLAGE_PHASE2_SURVEYOR = 8
VILLAGE_PHASE3_DAGEERIN = 9
VILLAGE_PHASE3_QUHAREK = 10
VILLAGE_PHASE3_SARGUILLO = 11
VILLAGE_PHASE3_SURVEYOR = 12
VILLAGE_PHASE4_ENGINEER = 13
VILLAGE_PHASE4_SARGUILLO_CP = 14
VILLAGE_PHASE4_SARGUILLO_ER = 15
VILLAGE_PHASE4_SIVARRA = 16

VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING = "VillageJediProgression"
VILLAGE_JEDI_PROGRESSION_GLOWING = 1
VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL = 2
VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS = 4
VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE = 8
VILLAGE_JEDI_PROGRESSION_ACCEPTED_MELLICHAE = 16
VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE = 32
VILLAGE_JEDI_PROGRESSION_COMPLETED_PADAWAN_TRIALS = 64

-- Set the jedi progression screen play state on the player.
-- @param pPlayer pointer to the creature object of the player.
-- @param state the state to set.
function VillageJediManagerCommon.setJediProgressionScreenPlayState(pPlayer, state)
	if (pPlayer == nil) then
		return
	end

	CreatureObject(pPlayer):setScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
end

function VillageJediManagerCommon.isVillageEligible(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS) and QuestManager.hasCompletedQuest(pPlayer, QuestManager.quests.FS_VILLAGE_ELDER)
end

-- Check if the player has the jedi progression screen play state.
-- @param pPlayer pointer to the creature object of the player.
-- @param state the state to check if the player has.
-- @return true if the player has the state.
function VillageJediManagerCommon.hasJediProgressionScreenPlayState(pPlayer, state)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
end

function VillageJediManagerCommon.unlockBranch(pPlayer, branch)
	if (pPlayer == nil) then
		return false
	end

	local questStatusTemp = CreatureObject(pPlayer):getScreenPlayState("VillageUnlockScreenPlay:" .. branch)
	if (questStatusTemp == 0) then
		CreatureObject(pPlayer):setScreenPlayState(2, "VillageUnlockScreenPlay:" .. branch)
	end

	local stringTO = "@quest/force_sensitive/utils:" .. branch

	local messageString = LuaStringIdChatParameter("@quest/force_sensitive/utils:branch_selected_unlock")
	messageString:setTO(stringTO)
	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

function VillageJediManagerCommon.hasUnlockedBranch(pPlayer, branch)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasScreenPlayState(2, "VillageUnlockScreenPlay:" .. branch)
end

function VillageJediManagerCommon.getUnlockedBranchCount(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local count = 0

	for i = 1, #VillageJediManagerCommon.forceSensitiveBranches, 1 do
		if VillageJediManagerCommon.hasUnlockedBranch(pPlayer, VillageJediManagerCommon.forceSensitiveBranches[i]) then
			count = count + 1
		end
	end

	return count
end

function VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	if (VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)) then
		return false
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local lastActiveQuest = tonumber(getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastActiveQuest"))

	return phaseID == lastActiveQuest
end

function VillageJediManagerCommon.setActiveQuestThisPhase(pPlayer, questId)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	VillageJediManagerCommon.addToActiveQuestList(pPlayer)
	setQuestStatus(playerID .. ":village:lastActiveQuest", phaseID)

	if (questId ~= nil and questId ~= "") then
		setQuestStatus(playerID .. ":village:activeQuestName", questId)
	end

	CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/utils:quest_accepted")
end

function VillageJediManagerCommon.getActiveQuestIdThisPhase(pPlayer)
	if (pPlayer == nil) then
		return -1
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local questId = getQuestStatus(playerID .. ":village:activeQuestName")

	if (not VillageJediManagerCommon.hasActiveQuestThisPhase(pPlayer)) then
		removeQuestStatus(playerID .. ":village:activeQuestName")
		return -1
	end

	if (questId == "") then
		printLuaError("VillageJediManagerCommon.getActiveQuestIdThisPhase unable to grab active questid for player")
		return -1
	end

	return tonumber(questId)
end

function VillageJediManagerCommon.hasCompletedQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local lastCompletedQuest = tonumber(getQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastCompletedQuest"))

	return phaseID == lastCompletedQuest
end

function VillageJediManagerCommon.setCompletedQuestThisPhase(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	VillageJediManagerCommon.removeFromActiveQuestList(pPlayer)
	removeQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:activeQuestName")
	setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":village:lastCompletedQuest", phaseID)
end

function VillageJediManagerCommon.createNewActiveQuestList()
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	return createQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.removeActiveQuestList(phaseID)
	removeQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.getActiveQuestList(phaseID)
	return getQuestVectorMap("VillageActiveQuestsPhaseID" .. phaseID)
end

function VillageJediManagerCommon.addToActiveQuestList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()
	local pMap = VillageJediManagerCommon.getActiveQuestList(phaseID)

	if (pMap == nil) then
		pMap = VillageJediManagerCommon.createNewActiveQuestList()
	end

	local questMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (not questMap:hasMapRow(playerID)) then
		questMap:addMapRow(playerID, tostring(os.time()))
	else
		printLuaError("VillageJediManagerCommon.addToActiveQuestList, attempting to add existing player " .. SceneObject(pPlayer):getCustomObjectName() .. " to active quest list.")
	end
end

function VillageJediManagerCommon.removeFromActiveQuestList(pPlayer)
	local phaseID = VillageJediManagerTownship:getCurrentPhaseID()

	local pMap = VillageJediManagerCommon.getActiveQuestList(phaseID)

	if (pMap == nil) then
		return
	end

	local questMap = LuaQuestVectorMap(pMap)
	local playerID = tostring(SceneObject(pPlayer):getObjectID())

	if (questMap:hasMapRow(playerID)) then
		questMap:deleteMapRow(playerID)
	end
end

function VillageJediManagerCommon.getLearnedForceSensitiveBranches(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local branchesLearned = 0

	for i = 1, #VillageJediManagerCommon.forceSensitiveBranches, 1 do
		if (CreatureObject(pPlayer):hasSkill(VillageJediManagerCommon.forceSensitiveBranches[i] .. "_04")) then
			branchesLearned = branchesLearned + 1
		end
	end

	return branchesLearned
end

return VillageJediManagerCommon
